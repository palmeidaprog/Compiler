/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */


#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <memory>
#include "IParser.h"
#include "IScanner.h"
#include "ScannerReturn.h"
#include "ScannerException.h"
#include "ParserException.h"

using std::unique_ptr;
using std::move;
using std::string;

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
        void atribuicao();
        void exprAritmetica();
        void termo();
        void fator();
        void exc(const string &msg);

        bool isTipo() const {
            return lookAhead->getToken() == Token::INTEIRO
                   || lookAhead->getToken() == Token::FLOAT
                   || lookAhead->getToken() == Token::LETRA
                   || lookAhead->getToken() == Token::INTEIRO;
        }
    };
}}



#endif //COMPILER_PARSER_H
