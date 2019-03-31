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

using std::unique_ptr;

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
        void iteracao();
        void exprRelacional();
        void atribuicao();
        void exprAritmetica();
        void termo();
        void fator();
    };
}}



#endif //COMPILER_PARSER_H
