/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "Scanner.h"

palmeidaprog::compiler::Token palmeidaprog::compiler::Scanner::scanNext() {
    int colunaLexema;

    while(isspace(ultimoLido)) {
        ultimoLido = nextChar();
    }

    //inteiro
    if(isnumber(ultimoLido)) {
        primeiraLeitura();
        leNumeros(); // loop que le digitos

        if(ultimoLido == '.') { // testa se é float
            proximo();
            leNumeros();
        } else { // inteiro
            return Token::VALOR_INTEIRO;
        }
    }

    // float que começam com pontos
    if(ultimoLido == '.') {
        primeiraLeitura();
        leNumeros();
        return Token::VALOR_FLOAT;
    }

    // char
    if(ultimoLido == '\'') {
        primeiraLeitura();
        proximo();
        if(ultimoLido == '\'') {
            proximo();
            return Token::LETRA_VALOR;
        } else {
            throw 
        }
    }


    // identificador
    if(isalpha(ultimoLido)) {
        primeiraLeitura();
        while(isalpha(ultimoLido) || isnumber(ultimoLido) || ) {
            proximo();
        }
    }
}

string palmeidaprog::compiler::Scanner::getLexema() {
    return valor;
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

char palmeidaprog::compiler::Scanner::proximo() {
    valor += ultimoLido;
    ultimoLido = nextChar();
}

// 59 a 62 > < = ;
// 40 a 45  ( ) * + , -
bool palmeidaprog::compiler::Scanner::simboloIsolado() {
    return isspace(ultimoLido) || (ultimoLido >= 59 && ultimoLido <= 62) ||
           ultimoLido == '!' || (ultimoLido >= 40 && ultimoLido <= 45) ||
           ultimoLido == '/' || ultimoLido == '{' || ultimoLido == '}';
}

bool palmeidaprog::compiler::Scanner::finalizaNumero() {
    return simboloIsolado() || isalpha(ultimoLido) || ultimoLido == '_';
}

bool palmeidaprog::compiler::Scanner::verificaFloat() {
    while(isnumber(ultimoLido)) {
        proximo();
    }
    return finalizaNumero();
}

void palmeidaprog::compiler::Scanner::leNumeros() {
    while(isnumber(ultimoLido)) {
        proximo();
    }
}

void palmeidaprog::compiler::Scanner::primeiraLeitura() {
    colunaLexema = coluna;
    proximo();
}



