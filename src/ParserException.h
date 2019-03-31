//
// Created by Paulo Roberto Almeida Filho on 3/30/19.
//

#ifndef COMPILER_PARSEREXCEPTION_H
#define COMPILER_PARSEREXCEPTION_H

#include <memory>
#include <stdexcept>
#include "ScannerReturn.h"

using std::unique_ptr;
using std::move;
using std::runtime_error;

namespace palmeidaprog { namespace compiler {
    class ParserException : public runtime_error {
        const unique_ptr<ScannerReturn> erro;

    public:
        explicit ParserException(const string &mensagem,
                unique_ptr<ScannerReturn> erro) noexcept;
        virtual ~ParserException();

        const ScannerReturn &getErro() const noexcept;
        const char *what() const noexcept override;
    };
}}



#endif //COMPILER_PARSEREXCEPTION_H
