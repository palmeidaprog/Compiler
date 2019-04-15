//
// Created by Paulo Roberto Almeida Filho on 4/14/19.
//

#include "Simbolo.h"

palmeidaprog::compiler::Simbolo::Simbolo(const string &identificador,
        Token tipo) : identificador(identificador), tipo(tipo) {

}

palmeidaprog::compiler::Simbolo::~Simbolo() {

}

const string &palmeidaprog::compiler::Simbolo::getIdentificador() const {
    return identificador;
}

const Token palmeidaprog::compiler::Simbolo::getTipo() const {
    return tipo;
}
