/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

// Interface de Estado de Automato Genérico

#ifndef COMPILER_IESTADO_H
#define COMPILER_IESTADO_H

namespace palmeidaprog { namespace compiler {
    // T = entrada para mudança de estado
    template <typename T = char>
    class IEstado {

        virtual ~IEstado() { };
        virtual unsigned entrada(const T &dado) = 0;
        virtual void adicionaVertice(const T &dado, unsigned destino) = 0;
        virtual void removerVertice(const T &dado) = 0;

    };

}}


#endif //COMPILER_IESTADO_H
