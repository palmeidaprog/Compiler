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
            }
            proximoToken();
            bloco();
            return;
        } else {
            exc("O nome da funcao precisa ser main");
        }
    } else {
        exc("Programa tem que começar com o tipo do retorno int na função main");
    }
}

void palmeidaprog::compiler::Parser::bloco() {
    // sem chaves
    if(lookAhead->getToken() != Token::ABRE_CHAVE) {
        if(isTipo()) {
            declaracaoVar();
        } else {
            comando();
        }
        return;
    }

    //com chaves
    proximoToken(); // lida chaves
    while(lookAhead->getToken() != Token::FECHA_CHAVE) {
        if(isTipo()) {
            declaracaoVar();
        } else if(lookAhead->getToken() == Token::FIM_ARQUIVO) {
            exc("Fim de arquivo encontrado com parenteses malformado.");
        } else {
            comando();
        }
    }
}

void palmeidaprog::compiler::Parser::comando() {

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
    proximoToken();
    idVar();
}

void palmeidaprog::compiler::Parser::iteracao() {
    if(lookAhead->getToken() == Token::DO) {

    } else if(lookAhead->getToken() == Token::WHILE) {

    } else {

    }
}

void palmeidaprog::compiler::Parser::exprRelacional() {

}

void palmeidaprog::compiler::Parser::atribuicao() {

}

void palmeidaprog::compiler::Parser::exprAritmetica() {

}

void palmeidaprog::compiler::Parser::termo() {

}

void palmeidaprog::compiler::Parser::fator() {

}

void palmeidaprog::compiler::Parser::parse() {
    programa();
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

