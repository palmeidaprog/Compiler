/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_TOKEN_H
#define COMPILER_TOKEN_H

#include <iostream>

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
}}

using std::ostream;
using palmeidaprog::compiler::Token;
ostream &operator<<(ostream &out, const
palmeidaprog::compiler::Token &token);
#endif //COMPILER_TOKEN_H
