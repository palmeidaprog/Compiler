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
#include "ScannerReturn.h"
#include "IScanner.h"
#include "ScannerException.h"

using std::string;
using std::ifstream;
using std::unique_ptr;
using std::make_unique;
using std::move;

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

        unique_ptr<ScannerReturn> scanNext() override; // retorno do scanner
        string getLexema() override;

    private:
        Token scan(); // identificação dos tokens
        void abreArquivo(); // abre arquivo para leitura
        void fechaArquivo();  // fecha arquivo, quando o scanner termina
        char nextChar(); // le o proximo char do arquivo
        void proximo(); // atualiza lookAhead e lexema
        void leNumeros(); // loop de digitos
        void primeiraLeitura(); // proximo() + atualiza coluna do lexema
        Token identifica(); // identifica se palavra reservada ou identif.
        void comentarios(); // loop dos comentários
        void novaLinha(); // atualiza linha e coluna depois de \n
        void simboloInvalido(char simbolo); // simbolo invalido exceção
    };
}}


#endif //COMPILER_SCANNER_H
