//
// Created by Paulo Roberto Almeida Filho on 4/14/19.
//

#include "Simbolo.h"

palmeidaprog::compiler::Simbolo::Simbolo(const string &identificador,
        Token tipo, int escopo) noexcept : identificador(identificador),
        tipo(tipo), escopo(escopo) {
}

palmeidaprog::compiler::Simbolo::~Simbolo() {
}

