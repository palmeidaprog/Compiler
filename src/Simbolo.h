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
        const int escopo;

    public:
        Simbolo(const string &identificador, Token tipo, int escopo) noexcept;
        virtual ~Simbolo();

        const string &getIdentificador() const noexcept {
            return identificador;
        }
        const Token getTipo() const noexcept {
            return tipo;
        }

        int getEscopo() const noexcept {
            return escopo;
        }
    };
}}


#endif //COMPILER_SIMBOLO_H
