/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#include <iostream>
#include "Token.h"

using std::ostream;
//using palmeidaprog::compiler::Token;

namespace palmeidaprog { namespace compiler {
    enum class Token {
        INTEIRO, VALOR_INTEIRO, // inteiro
        FLOAT, VALOR_FLOAT, // float
        LETRA, LETRA_VALOR, // char
        DO, FOR, WHILE, IF, ELSE, MAIN, // pal reservadas
        IDENTIFICADOR,
        SOMA, SUBSTRACAO, MULTIPLICACAO, DIVISAO, ATRIBUICAO, // oparitmetica
        MAIOR, MENOR, MAIOR_IGUAL, MENOR_IGUAL, IGUAL, DIFERENTE, // op. relac.
        // especiais
        ABRE_CHAVE, FECHA_CHAVE, ABRE_PARENTESES, FECHA_PARENTESES,
        VIRGULA, PONTO_VIRGULA, FIM_ARQUIVO,
        INVALIDO
    };

        ostream &operator<<(ostream &out, const Token &token) {
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
}}





#endif //COMPILER_TOKEN_H
