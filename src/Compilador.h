/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_COMPILER_H
#define COMPILER_COMPILER_H

#include <iostream>
#include <memory>
#include "Token.h"
#include "ScannerReturn.h"
#include "ScannerException.h"
#include "IScanner.h"
#include "ScannerFactory.h"

using std::make_unique;
using palmeidaprog::compiler::IScanner;
using std::string;
using std::unique_ptr;
using std::cout;
using std::endl;

namespace palmeidaprog { namespace compiler {
    class Compilador {
        unique_ptr<IScanner> scanner;
        string arquivo;

    public:
        Compilador(char *arquivo);
        Compilador(const string &arquivo);
        virtual ~Compilador();

        void compilar();
    private:
        void debugScanner();
        void tokenToStr(Token token);
    };
}}


#endif //COMPILER_COMPILER_H
