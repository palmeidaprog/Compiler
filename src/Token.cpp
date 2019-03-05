//
// Created by Paulo Roberto Almeida Filho on 3/5/19.
//

#include "Token.h"


ostream &operator<<(ostream &out, const
palmeidaprog::compiler::Token &token) {
    switch(token) {
        case Token::INTEIRO:
            out << "INTEIRO";
            break;
        case Token::VALOR_INTEIRO:
            out << "VALOR_INTEIRO";
            break;
        case Token::FLOAT:
            out << "FLOAT";
            break;
        case Token::VALOR_FLOAT:
            out << "VALOR_FLOAT";
            break;
        case Token::LETRA:
            out << "LETRA";
            break;
        case Token::LETRA_VALOR:
            out << "LETRA_VALOR";
            break;
        case Token::DO:
            out << "DO";
            break;
        case Token::FOR:
            out << "FOR";
            break;
        case Token::WHILE:
            out << "WHILE";
            break;
        case Token::IF:
            out << "IF";
            break;
        case Token::ELSE:
            out << "ELSE";
            break;
        case Token::MAIN:
            out << "MAIN";
            break;
        case Token::IDENTIFICADOR:
            out << "IDENTIFICADOR";
            break;
        case Token::SOMA:
            out << "SOMA";
            break;
        case Token::SUBSTRACAO:
            out << "SUBSTRACAO";
            break;
        case Token::MULTIPLICACAO:
            out << "MULTIPLICACAO";
            break;
        case Token::DIVISAO:
            out << "DIVISAO";
            break;
        case Token::ATRIBUICAO:
            out << "ATRIBUICAO";
            break;
        case Token::MAIOR:
            out << "MAIOR";
            break;
        case Token::MENOR:
            out << "MENOR";
            break;
        case Token::MAIOR_IGUAL:
            out << "MAIOR_IGUAL";
            break;
        case Token::MENOR_IGUAL:
            out << "MENOR_IGUAL";
            break;
        case Token::IGUAL:
            out << "IGUAL";
            break;
        case Token::DIFERENTE:
            out << "DIFERENTE";
            break;
        case Token::ABRE_CHAVE:
            out << "ABRE_CHAVE";
            break;
        case Token::FECHA_CHAVE:
            out << "FECHA_CHAVE";
            break;
        case Token::ABRE_PARENTESES:
            out << "ABRE_PARENTESES";
            break;
        case Token::FECHA_PARENTESES:
            out << "FECHA_PARENTESES";
            break;
        case Token::VIRGULA:
            out << "VIRGULA";
            break;
        case Token::PONTO_VIRGULA:
            out << "PONTO_VIRGULA";
            break;
        default:
            break;
    }
    return out;
}
