/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_TABELASIMBOLOS_H
#define COMPILER_TABELASIMBOLOS_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>
#include "Simbolo.h"

using std::make_unique;
using std::vector;
using std::unordered_map;
using std::string;
using std::unique_ptr;
using std::cout;
using std::endl;

namespace palmeidaprog { namespace compiler {
    class TabelaSimbolos {
        using hash = unordered_map<string, unique_ptr<Simbolo> >;
        vector< unique_ptr< hash > > tabela;

    public:
        TabelaSimbolos() noexcept;
        virtual ~TabelaSimbolos();

        const Simbolo *procura(const string &identificador, int escopo)
                const noexcept;
        void adiciona(Simbolo *identificador);
        void destroiEscopo(int escopo);
        void debug() const noexcept;
    };
}}



#endif //COMPILER_TABELASIMBOLOS_H
