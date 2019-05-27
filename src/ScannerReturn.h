/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_SCANNERRETURN_H
#define COMPILER_SCANNERRETURN_H

#include "Token.h"
#include <string>

using std::string;

namespace palmeidaprog { namespace compiler {
    class ScannerReturn {
        const Token token;
        const string lexema;
        const int coluna, linha;

    public:
        ScannerReturn(Token token, const string &lexema, int coluna,
                int linha);
        ScannerReturn(const ScannerReturn &toCopy);
        virtual ~ScannerReturn();

        Token getToken() const noexcept {
            return token;
        }

        const string &getLexema() const {
            return lexema;
        }

        int getColuna() const {
            return coluna;
        }

        int getLinha() const {
            return linha;
        }
    };
}}


#endif //COMPILER_SCANNERRETURN_H
