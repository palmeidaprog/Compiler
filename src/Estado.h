/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

/*
 * Implementacao de IEstado - Estado do Automato
 * */

#ifndef COMPILER_ESTADO_H
#define COMPILER_ESTADO_H

#include <string>
#include <unordered_map>
#include "IEstado.h"

using std::string;
using std::unordered_map;

namespace palmeidaprog { namespace compiler {
    template <typename T>
    class Estado : public IEstado<T> {
        unsigned estadoNumero;
        string estadoLabel;
        unordered_map<T, unsigned> output;



    };
}}


#endif //COMPILER_ESTADO_H
