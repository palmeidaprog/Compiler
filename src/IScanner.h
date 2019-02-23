/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_SCANNERABSTRACT_H
#define COMPILER_SCANNERABSTRACT_H

#include <string>
#include "Token.h"

using std::string;

namespace palmeidaprog { namespace compiler {
    class IScanner {
    public:
        virtual ~IScanner() { }
        virtual Token scanNext() = 0;
        virtual std::string getValor() = 0;
    };
}}

#endif //COMPILER_SCANNERABSTRACT_H
