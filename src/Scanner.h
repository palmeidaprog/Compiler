/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_SCANNER_H
#define COMPILER_SCANNER_H

#include "IScanner.h"

using std::string;

namespace palmeidaprog { namespace compiler {
    class Scanner : public IScanner {
        string arquivo, valor;
        char ultimoLido;

    public:
        Scanner(const string &arquivo);
        Scanner(char *arquivo);
        virtual ~Scanner();

        Token scanNext() override;
        string getValor() override;
    };
}}


#endif //COMPILER_SCANNER_H
