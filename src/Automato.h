//
// Created by Paulo Roberto Almeida Filho on 3/1/19.
//

#ifndef COMPILER_AUTOMATO_H
#define COMPILER_AUTOMATO_H

#include <string>
#include <vector>
#include <memory>
#include "IAutomato.h"
#include "IEstado.h"

using std::string;
using std::vector;
using std::unique_ptr;

namespace palmeidaprog { namespace compiler {
    // T = Valor que será o lexema da entrada para o automato
    // V = Qualquer retorno desejado pelo implementador, no caso do analisador
    //     léxico o retorno será o Token
    template <typename V, typename T = char>
    class Automato : public IAutomato<V, T>  {
        vector<unique_ptr<IEstado<T> > > estados;

    public:
        Automato(const vector<unique_ptr<IEstado <T> > > &estados, unique_ptr<) {
            Automato::estados.emplace(estados);
        }

        virtual ~Automato() { }

    };

}}


#endif //COMPILER_AUTOMATO_H
