/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_SEMANTICEXCEPTION_H
#define COMPILER_SEMANTICEXCEPTION_H

#include <memory>
#include <stdexcept>
#include "SemanticReturn.h"

using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;

namespace palmeidaprog { namespace compiler {
    class IncompatibleTypesException : public std::runtime_error  {
        const shared_ptr<SemanticReturn> var1, var2;

    public:
        IncompatibleTypesException(const string &mensagem,
                                   shared_ptr<SemanticReturn> var1,
                                   shared_ptr<SemanticReturn> var2) noexcept;
        IncompatibleTypesException(const string &mensagem,
               const SemanticReturn &var1,
               const SemanticReturn &var2) noexcept;
        virtual ~IncompatibleTypesException();

        const SemanticReturn &getVar1() const noexcept;
        const SemanticReturn &getVar2() const noexcept;
        const char *what() const noexcept override;
    };
}}

#endif //COMPILER_SEMANTICEXCEPTION_H
