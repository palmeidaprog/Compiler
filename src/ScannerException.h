/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

// Exceção do scanner

#ifndef COMPILER_SCANNEREXCEPTION_H
#define COMPILER_SCANNEREXCEPTION_H

#include <stdexcept>
#include <string>

using std::exception;
using std::string;

namespace palmeidaprog { namespace compilter {
    class ScannerException : public exception {
        const unsigned linha, coluna;
        const string mensagem;

    public:
        ScannerException(const string &mensagem, unsigned linha,
                unsigned coluna);
        virtual ~ScannerException();

        unsigned getLinha() const {
            return linha;
        }

        unsigned getColuna() const {
            return coluna;
        }

        const string &getMensagem() const {
            return mensagem;
        }
    };
}}


#endif //COMPILER_SCANNEREXCEPTION_H
