/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_SCANNERABSTRACT_H
#define COMPILER_SCANNERABSTRACT_H

#include <string>
#include <memory>
#include "ScannerReturn.h"

using std::string;
using std::unique_ptr;

namespace palmeidaprog { namespace compiler {
    class IScanner {
    public:
        virtual ~IScanner() { }
        virtual unique_ptr<ScannerReturn> scanNext() = 0;
        virtual string getLexema() = 0;
    };
}}

#endif //COMPILER_SCANNERABSTRACT_H
