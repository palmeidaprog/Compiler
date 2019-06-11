/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_COMPILER_H
#define COMPILER_COMPILER_H

#include <stdexcept>
#include <iostream>
#include <memory>
#include "Token.h"
#include "ScannerReturn.h"
#include "ScannerException.h"
#include "IScanner.h"
#include "ScannerFactory.h"
#include "IParser.h"
#include "ParserFactory.h"
#include "ParserException.h"

using std::make_unique;
using palmeidaprog::compiler::IScanner;
using std::string;
using std::unique_ptr;
using std::cout;
using std::cerr;
using std::endl;
using std::runtime_error;

namespace palmeidaprog { namespace compiler {
    class Compilador {
        unique_ptr<IScanner> scanner;
        unique_ptr<IParser> parser;
        string arquivo;

    public:
        Compilador(char *arquivo);
        Compilador(const string &arquivo);
        virtual ~Compilador();

        void compilar();
    private:
        //void debugScanner();
        void tokenToStr(Token token);
        //void debugTabela();
    };
}}


#endif //COMPILER_COMPILER_H
