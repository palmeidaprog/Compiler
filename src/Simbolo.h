//
// Created by Paulo Roberto Almeida Filho on 4/14/19.
//

#ifndef COMPILER_SIMBOLO_H
#define COMPILER_SIMBOLO_H

#include <string>
#include "Token.h"

using std::string;

namespace palmeidaprog { namespace compiler {
    class Simbolo {
        const string identificador;
        const Token tipo;

    public:
        Simbolo(const string &identificador, Token tipo);
        virtual ~Simbolo();

        const string &getIdentificador() const;
        const Token getTipo() const;

    };
}}


#endif //COMPILER_SIMBOLO_H
