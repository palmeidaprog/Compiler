/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */


#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <iostream>
#include <memory>
#include "IParser.h"
#include "IScanner.h"
#include "ScannerReturn.h"
#include "ScannerException.h"
#include "ParserException.h"

using std::unique_ptr;
using std::move;
using std::string;
using std::cout;
using std::endl;

namespace palmeidaprog { namespace compiler {
    class Parser : public IParser {
        IScanner &scanner;
        unique_ptr<ScannerReturn> lookAhead;

    public:
        virtual ~Parser();
        Parser(IScanner &scanner);

        void parse() override;

    private:
        void proximoToken();
        void programa();
        void bloco();
        void comando();
        void comandoBasico();
        void declaracaoVar();
        void idVar();
        void iteracao();
        void exprRelacional();
        void condicionalWhile();
        void atribuicao();
        void exprAritmetica();
        void termo();
        void fator();
        void condicionalIf();
        void exc(const string &msg);

        bool isValor() {
            return lookAhead->getToken() == Token::VALOR_FLOAT
                    || lookAhead->getToken() == Token::VALOR_INTEIRO
                    || lookAhead->getToken() == Token::LETRA_VALOR;
        }

        bool operadorRelacional() const {
            return lookAhead->getToken() == Token::MAIOR_IGUAL
                || lookAhead->getToken() == Token::MAIOR
                || lookAhead->getToken() == Token::MENOR
                || lookAhead->getToken() == Token::MENOR_IGUAL
                || lookAhead->getToken() == Token::IGUAL
                || lookAhead->getToken() == Token::DIFERENTE;
        }

        bool isTipo() const {
            return lookAhead->getToken() == Token::INTEIRO
                   || lookAhead->getToken() == Token::FLOAT
                   || lookAhead->getToken() == Token::LETRA
                   || lookAhead->getToken() == Token::INTEIRO;
        }
    };
}}



#endif //COMPILER_PARSER_H
