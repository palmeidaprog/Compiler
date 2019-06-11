/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_SIMBOLO_H
#define COMPILER_SIMBOLO_H

#include <string>
#include <ostream>
#include "Token.h"

using std::string;
using std::ostream;

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

    private:
        friend ostream& operator<<(ostream &out, const Simbolo &simbolo);
    };


//    ostream& operator<<(ostream &out, const Simbolo &simbolo) {
//        out << simbolo.escopo << "\t" << simbolo.identificador << "\t";
//        //out << simbolo.tipo; TODO: fix the overloading of operator in Token
//        return out;
//    }
}}



#endif //COMPILER_SIMBOLO_H

//ostream &operator<<(ostream &out, const Simbolo &simbolo) {
//    out << simbolo.escopo << "\t" << simbolo.identificador << "\t"
//        << simbolo.tipo << "\n";
//    return out;
//}