/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */


#ifndef COMPILER_IPARSER_H
#define COMPILER_IPARSER_H

#include <memory>
#include <string>
#include <unordered_map>
#include "Simbolo.h"

using std::make_unique;
using std::unique_ptr;
using std::string;
using std::unordered_map;

namespace palmeidaprog { namespace compiler {
    class IParser {
    public:
        // virtual Tabela &getTabela() = 0
        //virtual ArvoreGramatica<Scanner>
        //virtual ~IParser() = 0;
        virtual void parse() = 0;
        virtual bool isFinalizado() const = 0;
        //virtual const Simbolo *getSimbolo(string identificador) const = 0;
        virtual void debugTabela() const noexcept = 0;
    };

}}

#endif //COMPILER_IPARSER_H
