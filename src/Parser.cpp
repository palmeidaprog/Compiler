/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "Parser.h"

palmeidaprog::compiler::Parser::Parser(palmeidaprog::compiler::IScanner
    &scanner) : scanner(scanner) {
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
    // sem chaves
    /*if(lookAhead->getToken() != Token::ABRE_CHAVE) {
        if(isTipo()) {
            declaracaoVar();
        } else {
            comando();
        }
        return;
    }*/

    //com chaves
    if(lookAhead->getToken() == Token::ABRE_CHAVE) {
        proximoToken(); // lida chaves
    } else {
        exc("Bloco de código necessita de abre chaves");
    }

    while(isTipo()) {
        declaracaoVar();
    }

    while(lookAhead->getToken() != Token::FECHA_CHAVE) {
        if(lookAhead->getToken() == Token::FIM_ARQUIVO) {
            exc("Fim de arquivo encontrado com parenteses malformado.");
        }
        comando();
    }
    proximoToken();
}

void palmeidaprog::compiler::Parser::comando() {
    iteracao(); // se nao for iteracao ele sai sem dar erro
    condicionalIf();
    comandoBasico();
}

void palmeidaprog::compiler::Parser::comandoBasico() {
    if(lookAhead->getToken() == Token::IDENTIFICADOR) {
        atribuicao();
    } else {
        bloco();
    }
}

// declaracao de variaveis;
void palmeidaprog::compiler::Parser::declaracaoVar() {
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
            exc("Parenteses malformado na condicional do while");
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

void palmeidaprog::compiler::Parser::exprRelacional() {
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

void palmeidaprog::compiler::Parser::exprAritmetica() {
    termo();
    if(lookAhead->getToken() == Token::SOMA
        || lookAhead->getToken() == Token::SUBSTRACAO) {
        proximoToken();
        exprAritmetica();
    }
}

void palmeidaprog::compiler::Parser::termo() {
    fator();
    if(lookAhead->getToken() == Token::MULTIPLICACAO
        || lookAhead->getToken() == Token::DIVISAO) {
        proximoToken();
        termo();
    }
}

void palmeidaprog::compiler::Parser::fator() {
    if(isValor() || lookAhead->getToken() == Token::IDENTIFICADOR) {
        proximoToken();
    } else if(lookAhead->getToken() == Token::ABRE_PARENTESES) {
        proximoToken();
        exprAritmetica();
        if(lookAhead->getToken() == Token::FECHA_PARENTESES) {
            proximoToken();
        } else {
            exc("Parenteses malformado na expressão aritmética");
        }
    } else {
        exc("Esperado valor constante ou variavel");
    }
}

void palmeidaprog::compiler::Parser::parse() {
    programa();
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
            } else {
                exc(string("Parenteses malformado, fecha parenteses esperado")
                           .append(" após condicional do if"));
                comando();
                if(lookAhead->getToken() == Token::ELSE) {
                    proximoToken();
                    comando();
                }
            }
        } else {
            exc("() Abre parenteses com condicional esperada após um if");
        }
    }

}



