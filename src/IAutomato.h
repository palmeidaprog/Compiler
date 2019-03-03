/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

// Interface de Automato Genérico

#ifndef COMPILER_IAUTOMATO_H
#define COMPILER_IAUTOMATO_H

#include <string>
#include <memory>
#include "IRetorno.h"

using std::string;
using std::unique_ptr;

namespace palmeidaprog { namespace compiler {
    // T = Valor que será o valor da entrada para o automato
    // V = Qualquer retorno desejado pelo implementador, no caso do analisador
    //     léxico o retorno será o Token
    template <typename V, typename T = char>
    class IAutomato {
        unique_ptr<IRetorno> retorno;

    public:
        virtual ~IAutomato() { }
        const V &getRetorno() {
            return retorno->getRetorno();
        }

        virtual const bool entrada(const T &entrada) = 0;
    };
}}


#endif //COMPILER_IAUTOMATO_H
