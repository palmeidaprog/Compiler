/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "Parser.h"

palmeidaprog::compiler::Parser::Parser(palmeidaprog::compiler::IScanner
    &scanner) : scanner(scanner), finalizado(false),
    tabela(make_unique<TabelaSimbolos>()), escopo(0) {
}

palmeidaprog::compiler::Parser::~Parser() {

}

void palmeidaprog::compiler::Parser::programa() {
    lookAhead = scanner.scanNext();
    if(lookAhead->getToken() == Token::INTEIRO) {
        proximoToken();
        if(lookAhead->getToken() == Token::MAIN) {
            proximoToken();
            if(lookAhead->getToken() == Token::ABRE_PARENTESES) {
                proximoToken();
                if(lookAhead->getToken() == Token::FECHA_PARENTESES) {
                    proximoToken();
                    bloco();
                    return;
                } else {
                    exc("Parenteses não fechados");
                }
            } else {
                exc("Esperado parenteses apos main");
            }
        } else {
            exc("O nome da funcao precisa ser main");
        }
    } else {
        exc("Programa tem que começar com o tipo do retorno int na função main");
    }
}

void palmeidaprog::compiler::Parser::bloco() {
    if(lookAhead->getToken() == Token::ABRE_CHAVE) {
        proximoToken(); // lida chaves
        ++escopo;
    } else {
        exc("Bloco de código necessita de abre chaves");
    }

    while(isTipo()) {
        declaracaoVar();
    }

    while(lookAhead->getToken() != Token::FECHA_CHAVE) {
        if(isTipo()) {
            exc(string("Variáveis só podem ser declaradas no começo do ")
                .append("escopo. Impossível declarar após utilização de ")
                .append("comandos"));
        }

        if(lookAhead->getToken() == Token::FIM_ARQUIVO) {
            exc("Fim de arquivo encontrado com chaves não fechada.");
        }
        comando();
    }
    proximoToken();
    tabela->destroiEscopo(escopo--); // destroi variaveis do escopo
}

void palmeidaprog::compiler::Parser::comando() {
    if(lookAhead->getToken() == Token::DO ||
        lookAhead->getToken() == Token::WHILE) {
        iteracao();
    } else if(lookAhead->getToken() == Token::IF) {
        condicionalIf();
    } else {
        comandoBasico();
    }
}

void palmeidaprog::compiler::Parser::comandoBasico() {
    // TODO: solve the wrong message on some cases (Invalid command)
    if(lookAhead->getToken() == Token::IDENTIFICADOR) {
        atribuicao();
    } else {
        bloco();
    }
}

// declaracao de variaveis;
void palmeidaprog::compiler::Parser::declaracaoVar() {
    tipoVar = lookAhead->getToken();
    proximoToken(); // passa o tipo
    idVar();
}


void palmeidaprog::compiler::Parser::condicionalWhile() {
    if (lookAhead->getToken() == Token::ABRE_PARENTESES) {
        proximoToken();
        exprRelacional();
        if (lookAhead->getToken() == Token::FECHA_PARENTESES) {
            proximoToken();
        } else {
            exc("Parenteses não fechado na condicional do while");
        }
    } else {
        exc("Esperado parenteses com condicional após while");
    }
}

void palmeidaprog::compiler::Parser::iteracao() {
    if(lookAhead->getToken() == Token::DO) {
        proximoToken();
        comando();
        if(lookAhead->getToken() == Token::WHILE) {
            proximoToken();
            condicionalWhile();
            if(lookAhead->getToken() != Token::PONTO_VIRGULA) {
                exc("Esperado \";\" após a condicional de um do-while");
            } else {
                proximoToken();
            }
        } else {
            exc("\"while\" esperado apos fechamento do bloco apos \"do\"");
        }
    } else if(lookAhead->getToken() == Token::WHILE) {
        proximoToken();
        condicionalWhile();
        comando();
    }
}

unique_ptr<palmeidaprog::compiler::SemanticReturn> palmeidaprog::compiler::Parser::exprRelacional() {
    exprAritmetica();
    if(operadorRelacional()) {
        proximoToken();
        exprAritmetica();
    } else {
        exc("Esperado operador relacional (<,>,>=.<=,==,!=) após expressão");
    }

}

void palmeidaprog::compiler::Parser::atribuicao() {
    proximoToken();
    if(lookAhead->getToken() == Token::ATRIBUICAO) {
        proximoToken();
        exprAritmetica();
        if(lookAhead->getToken() == Token::PONTO_VIRGULA) {
            proximoToken();
        } else {
            exc("Esperado ; apos atribuição");
        }
    } else {
        exc("Esperado =, atribuicao necessita do igual apos o identificador");
    }
}

unique_ptr<palmeidaprog::compiler::SemanticReturn> palmeidaprog::compiler::Parser::exprAritmetica() {
    termo();
    if(lookAhead->getToken() == Token::SOMA
        || lookAhead->getToken() == Token::SUBSTRACAO) {
        proximoToken();
        exprAritmetica();
    }
}

unique_ptr<palmeidaprog::compiler::SemanticReturn>
        palmeidaprog::compiler::Parser::termo() {
    auto semanticoFator = fator();
    if(lookAhead->getToken() == Token::MULTIPLICACAO
        || lookAhead->getToken() == Token::DIVISAO) {
        Token operacao = lookAhead->getToken();
        proximoToken();
        auto semanticoTermo = termo();
        
    }
    return semanticoFator;
}

unique_ptr<palmeidaprog::compiler::SemanticReturn>
        palmeidaprog::compiler::Parser::fator() {
    if(isValor() || lookAhead->getToken() == Token::IDENTIFICADOR) {
        auto semantico = make_unique<SemanticReturn>(lookAhead, escopo);
        proximoToken();
        return semantico;
    } else if(lookAhead->getToken() == Token::ABRE_PARENTESES) {
        proximoToken();
        auto semantico = exprAritmetica();
        if(lookAhead->getToken() == Token::FECHA_PARENTESES) {
            proximoToken();
            return semantico;
        } else {
            exc("Parenteses malformado na expressão aritmética");
        }
    } else {
        exc("Esperado valor constante ou variavel");
    }
}

void palmeidaprog::compiler::Parser::parse() {
    programa();
    finalizado = true;
    if(lookAhead->getToken() != Token::FIM_ARQUIVO) {
        exc("Código encontrado fora da função main");
    }
}

void palmeidaprog::compiler::Parser::proximoToken() {
    lookAhead = scanner.scanNext();
}

void palmeidaprog::compiler::Parser::exc(const string &msg) {
    throw ParserException(msg, move(lookAhead));
}

// pega os identifcadores das variaveis
void palmeidaprog::compiler::Parser::idVar() {
    if(lookAhead->getToken() == Token::IDENTIFICADOR) {
        // TODO: verify if tipoVar is really correct or to switch to getTipo()
        tabela->adiciona(new Simbolo(lookAhead->getLexema(), tipoVar,
                escopo));
        /* TODO: remove this
        tabela.emplace(lookAhead->getLexema(),
                make_unique<Simbolo>(lookAhead->getLexema(), tipoVar));*/
        proximoToken();
        if(lookAhead->getToken() == Token::PONTO_VIRGULA) {
            proximoToken();
            return;
        } else if(lookAhead->getToken() == Token::VIRGULA) {
            proximoToken();
            idVar();
        } else {
            exc("Esperado ; ou , na declaracao de variável(is).");
        }
    } else {
        exc("Identificador da variavel esperado.");
    }
}

void palmeidaprog::compiler::Parser::condicionalIf() {
    if(lookAhead->getToken() == Token::IF) {
        proximoToken();
        if(lookAhead->getToken() == Token::ABRE_PARENTESES) {
            proximoToken();
            exprRelacional();
            if(lookAhead->getToken() == Token::FECHA_PARENTESES) {
                proximoToken();
                comando();
                if(lookAhead->getToken() == Token::ELSE) {
                    proximoToken();
                    comando();
                }
            } else {
                exc(string("Parenteses malformado, fecha parenteses esperado")
                            .append(" após condicional do if"));
            }
        } else {
            exc("() Abre parenteses com condicional esperada após um if");
        }
    }
}

void palmeidaprog::compiler::Parser::debugTabela() const noexcept {
    tabela->debug();
}

unique_ptr<palmeidaprog::compiler::SemanticReturn>
        palmeidaprog::compiler::Parser::checaTipos(
            unique_ptr<palmeidaprog::compiler::SemanticReturn> id1,
            unique_ptr<palmeidaprog::compiler::SemanticReturn> id2,
            Token operacao) {
    if(combinacaoTipos(*id1.get(), *id2.get(), Token::LETRA, Token::LETRA)) {
        return move(id1);
    } else if(combinacaoTipos(*id1.get(), *id2.get(), Token::LETRA, Token::FLOAT)) {
        //TODO: Concluir chegacagem de tipos (Combinacao ou arranjo)
    }
}

bool palmeidaprog::compiler::Parser::combinacaoTipos(
        palmeidaprog::compiler::SemanticReturn &id1,
        palmeidaprog::compiler::SemanticReturn &id2, Token tipo1,
        Token tipo2) {
    return (id1.getTipoGenerico() == tipo1 && id2.getTipoGenerico() == tipo2)
        || (id1.getTipoGenerico() == tipo2 && id2.getTipoGenerico() == tipo1);
}







