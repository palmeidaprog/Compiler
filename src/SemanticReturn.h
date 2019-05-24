/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_SEMANTICRETURN_H
#define COMPILER_SEMANTICRETURN_H

#include "ScannerReturn.h"

namespace palmeidaprog { namespace compiler {
    class SemanticReturn : public ScannerReturn {
        const int escopo;

    public:
        SemanticReturn(const ScannerReturn &scannerReturn, int escopo);
        virtual ~SemanticReturn();
        int getEscopo() const noexcept {
            return escopo;
        }
    };
}}
#endif //COMPILER_SEMANTICRETURN_H



