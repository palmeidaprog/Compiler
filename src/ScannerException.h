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
#include <sstream>

using std::runtime_error;
using std::string;
using std::stringstream;

namespace palmeidaprog { namespace compiler {
    class ScannerException : public runtime_error {
        const unsigned linha, coluna;
        const string lexema;

    public:
        explicit ScannerException(const string &s) noexcept;
        ScannerException(const string &mensagem, unsigned linha,
                unsigned coluna, const string &lexema) noexcept;
        virtual ~ScannerException();

        unsigned getLinha() const noexcept {
            return linha;
        }

        unsigned getColuna() const noexcept {
            return coluna;
        }

        const string &getLexema() const noexcept {
            return lexema;
        }

        string msg() const;

        const char *what() const noexcept override;
    };
}}


#endif //COMPILER_SCANNEREXCEPTION_H
