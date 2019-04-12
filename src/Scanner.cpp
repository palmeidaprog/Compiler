/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "Scanner.h"

std::unique_ptr<palmeidaprog::compiler::ScannerReturn>
        palmeidaprog::compiler::Scanner::scanNext() {
    return make_unique<ScannerReturn>(scan(), lexema, colunaLexema, linha);
}

string palmeidaprog::compiler::Scanner::getLexema() {
    return lexema;
}



palmeidaprog::compiler::Scanner::Scanner(const string &arquivo) :
    linha(1), coluna(0), arquivo(arquivo), ultimoLido(' ') {
}

palmeidaprog::compiler::Scanner::Scanner(char *arquivo) :
    linha(1), coluna(0), arquivo(string(arquivo)), ultimoLido(' ') {
    abreArquivo();
}

palmeidaprog::compiler::Scanner::~Scanner() {
    fechaArquivo();
}

void palmeidaprog::compiler::Scanner::abreArquivo() {
    codigoFonte = make_unique<ifstream>(arquivo);
}

char palmeidaprog::compiler::Scanner::nextChar() {
    if(codigoFonte->good()) {
        ++coluna;
        char c;
        codigoFonte->get(c);
        return c;
    }
    return EOF;
}

void palmeidaprog::compiler::Scanner::fechaArquivo() {
    if(codigoFonte->is_open()) {
        codigoFonte->close();
    }
}

void palmeidaprog::compiler::Scanner::proximo() {
    lexema += ultimoLido;
    ultimoLido = nextChar();
}

// 59 a 62 > < = ;
// 40 a 45  ( ) * + , -

void palmeidaprog::compiler::Scanner::leNumeros() {
    while(isdigit(ultimoLido)) {
        proximo();
    }
}

void palmeidaprog::compiler::Scanner::primeiraLeitura() {
    colunaLexema = coluna;
    proximo();
}

palmeidaprog::compiler::Token palmeidaprog::compiler::Scanner::identifica() {
    if(lexema == "if") {
        return Token::IF;
    } else if(lexema == "do") {
        return Token::DO;
    } else if(lexema == "for") {
        return Token::FOR;
    } else if(lexema == "while") {
        return Token::WHILE;
    } else if(lexema == "else") {
        return Token::ELSE;
    } else if(lexema == "main") {
        return Token::MAIN;
    } else if(lexema == "int") {
        return Token::INTEIRO;
    } else if(lexema == "float") {
        return Token::FLOAT;
    } else if(lexema == "char") {
        return Token::LETRA;
    } else {
        return Token::IDENTIFICADOR;
    }
}

void palmeidaprog::compiler::Scanner::comentarios() {
    char temp;
    bool stop = false;
    while(!stop && ultimoLido != EOF) {
        temp = nextChar();
        if(temp == '\n') {
            novaLinha();
        }
        if(ultimoLido == '*' && temp == '/') {
            stop = true;
        }
        ultimoLido = temp;
    }
    if(ultimoLido == EOF) {
        throw ScannerException("Comentário multi-linha não terminado", linha,
                               coluna + 1, "");
    }
    ultimoLido = ' ';
    lexema = " ";
}

void palmeidaprog::compiler::Scanner::novaLinha() {
    ++linha;
    coluna = 0;
}

void palmeidaprog::compiler::Scanner::simboloInvalido(char simbolo) {
    stringstream s;
    s << "Simbolo \'" << simbolo << "\' não está "
      << "incluso na linguagem.";
    throw ScannerException(s.str(), linha, colunaLexema, string(1, simbolo));
}

Token palmeidaprog::compiler::Scanner::scan() {
    lexema = "";

    while(isspace(ultimoLido)) {
        if(ultimoLido == '\n') {
            novaLinha();
        }
        ultimoLido = nextChar();
    }

    //inteiro
    if(isdigit(ultimoLido)) {
        primeiraLeitura();
        leNumeros(); // loop que le digitos

        if(ultimoLido == '.') { // testa se é float
            proximo();
            leNumeros();
            return Token::VALOR_FLOAT;
        } else { // inteiro
            return Token::VALOR_INTEIRO;
        }
    }

    // float que começam com pontos
    if(ultimoLido == '.') {
        primeiraLeitura();
        leNumeros();
        if(lexema == ".") {
            throw ScannerException(string("Valor float malformado. \".\" ")
                .append("sozinho é um simbolo invalido"),linha, colunaLexema,
                lexema);
        }
        return Token::VALOR_FLOAT;
    }

    // char
    if(ultimoLido == '\'') {
        primeiraLeitura();
        if(!isalnum(ultimoLido)) {
            throw ScannerException(string("Valor char malformado. ")
                 .append("Só pode ser digito ou letra"),
                linha, colunaLexema + 1, string(lexema + ultimoLido));
        }
        proximo();
        if(ultimoLido == '\'') {
            proximo();
            return Token::LETRA_VALOR;
        } else {
            string v(lexema + ultimoLido);
            unsigned tam = v.length() - 1;
            if(v[tam] == '\n') {
                v.erase(v.begin()+tam);
            }
            throw ScannerException(string("Valor char malformado. "), linha,
                    colunaLexema + 1, v);
        }
    }

    // identificador
    if(isalpha(ultimoLido)) {
        primeiraLeitura();
        while(isalpha(ultimoLido) || isdigit(ultimoLido)
              || ultimoLido == '_') {
            proximo();
        }
        return identifica();
    }

    // simbolos isolados
    Token retorno = Token::INVALIDO;
    if(ultimoLido == '+') {
        retorno = Token::SOMA;
    } else if(ultimoLido == '-') {
        retorno = Token::SUBSTRACAO;
    } else if(ultimoLido == '*') {
        retorno = Token::MULTIPLICACAO;
    } else if(ultimoLido == '/') {
        primeiraLeitura();
        if(ultimoLido == '/') { // comentario simples
            while (ultimoLido != '\n' && ultimoLido != EOF) {
                ultimoLido = nextChar();
                novaLinha();
            }
            return scan();
        } else if(ultimoLido == '*') {
            comentarios();
            return scan();
        } else {
            return Token::DIVISAO;
        }
    } else if(ultimoLido == ')') {
        retorno = Token::FECHA_PARENTESES;
    } else if(ultimoLido == '(') {
        retorno = Token::ABRE_PARENTESES;
    } else if(ultimoLido == '{') {
        retorno = Token::ABRE_CHAVE;
    } else if(ultimoLido == '}') {
        retorno = Token::FECHA_CHAVE;
    } else if(ultimoLido == ',') {
        retorno = Token::VIRGULA;
    } else if(ultimoLido == ';') {
        retorno = Token::PONTO_VIRGULA;
    } else if(ultimoLido == EOF) {
        return Token::FIM_ARQUIVO;
    } else if(ultimoLido == '\n') {
        proximo();
        ++linha;
        coluna = 0;
        return scan();
    }

    // retorno do simbolo isolado
    if(retorno != Token::INVALIDO) {
        primeiraLeitura();
        return retorno;
    }

    // Atribuicão e operadores relacionais (= == > >= < <= !=)
    if(ultimoLido == '=') {
        primeiraLeitura();
        if(ultimoLido == '=') {
            proximo();
            return Token::IGUAL;
        } else {
            return Token::ATRIBUICAO;
        }
    } else if(ultimoLido == '>') {
        primeiraLeitura();
        if(ultimoLido == '=') {
            proximo();
            return Token::MAIOR_IGUAL;
        } else {
            return Token::MAIOR;
        }
    } else if(ultimoLido == '<') {
        primeiraLeitura();
        if(ultimoLido == '=') {
            proximo();
            return Token::MENOR_IGUAL;
        } else {
            return Token::MENOR;
        }
    } else if(ultimoLido == '!') {
        primeiraLeitura();
        if(ultimoLido == '=') {
            proximo();
            return Token::DIFERENTE;
        } else {
            simboloInvalido('!');
        }
    } else {
        simboloInvalido(ultimoLido);
    }
    return Token::INVALIDO; // inalcancavel, apenas para evitar warning
}



