/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_SCANNER_H
#define COMPILER_SCANNER_H

#include "IScanner.h"
#include "ScannerException.h"
#include <fstream>
#include <cctype>
#include <memory>

using std::string;
using std::ifstream;
using std::unique_ptr;
using std::make_unique;

namespace palmeidaprog { namespace compiler {
    class Scanner : public IScanner {
        string arquivo, lexema;
        char ultimoLido;
        int linha, coluna, colunaLexema;
        unique_ptr<ifstream> codigoFonte;

    public:
        Scanner(const string &arquivo);
        Scanner(char *arquivo);
        virtual ~Scanner();

        int getLinha() const {
            return linha;
        }

        int getColuna() const {
            return colunaLexema;
        }

        Token scanNext() override;
        string getLexema() override;

    private:
        void abreArquivo();
        void fechaArquivo();
        char nextChar();
        char proximo();
        Token simbolosIsolados();
        void leNumeros();
        void primeiraLeitura();
        Token identifica();
    };
}}


#endif //COMPILER_SCANNER_H
