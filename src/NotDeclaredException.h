//
// Created by Paulo Roberto Almeida Filho on 26/05/19.
//

#ifndef COMPILER_NOTDECLAREDEXCEPTION_H
#define COMPILER_NOTDECLAREDEXCEPTION_H

#include <memory>
#include <stdexcept>
#include "SemanticReturn.h"

using std::shared_ptr;

namespace palmeidaprog { namespace compiler {
    class NotDeclaredException : public std::runtime_error  {
        const shared_ptr<SemanticReturn> erro;

    public: //TODO: use 2 semantic return and operator to define the operation
        NotDeclaredException(const string &mensagem,
        shared_ptr<SemanticReturn> erro) noexcept;
        virtual ~NotDeclaredException();

        const SemanticReturn &getErro() const noexcept;
        const char *what() const noexcept override;
    };
}}

#endif //COMPILER_NOTDECLAREDEXCEPTION_H
