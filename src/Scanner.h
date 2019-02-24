/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_SCANNER_H
#define COMPILER_SCANNER_H

#include "IScanner.h"
#include <fstream>

using std::string;
using std::ifstream;

namespace palmeidaprog { namespace compiler {
    class Scanner : public IScanner {
        string arquivo, valor;
        char ultimoLido;
        ifstream codigoFonte;

    public:
        Scanner(const string &arquivo);
        Scanner(char *arquivo);
        virtual ~Scanner();

        Token scanNext() override;
        string getValor() override;

    private:
        void abreArquivo();
        void fechaArquivo();
    };
}}


#endif //COMPILER_SCANNER_H
