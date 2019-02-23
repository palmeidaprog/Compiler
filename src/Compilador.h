/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_COMPILER_H
#define COMPILER_COMPILER_H

#include <memory>
#include "IScanner.h"
#include "ScannerFactory.h"
#include "Scanner.h"

using std::make_unique;
using palmeidaprog::compiler::IScanner;
using std::string;
using std::unique_ptr;

namespace palmeidaprog { namespace compiler {
    class Compilador {
        unique_ptr<IScanner> scanner;
        string arquivo;

    public:
        Compilador(char *arquivo);
        Compilador(const string &arquivo);
        virtual ~Compilador();
    };
}}


#endif //COMPILER_COMPILER_H
