/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#ifndef COMPILER_SCANNER_H
#define COMPILER_SCANNER_H


#include <fstream>
#include <cctype>
#include <memory>
#include "IScanner.h"
#include "ScannerException.h"

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
        void proximo();
        Token simbolosIsolados();
        void leNumeros();
        void primeiraLeitura();
        Token identifica();
        void comentarios();
        void novaLinha();
        void simboloInvalido(char simbolo);
    };
}}


#endif //COMPILER_SCANNER_H
