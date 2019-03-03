/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

// Interface do retorno do Automato.

#ifndef COMPILER_IRETORNO_H
#define COMPILER_IRETORNO_H

namespace palmeidaprog { namespace compiler {
    template<typename T>
    class IRetorno {
        virtual ~IRetorno() { }
        virtual const T &getRetorno() = 0;

    };
}}


#endif //COMPILER_IRETORNO_H
