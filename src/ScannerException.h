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

using std::exception;
using std::string;
using std::stringstream;

namespace palmeidaprog { namespace compiler {
    class ScannerException : public std::runtime_error {
            const unsigned linha, coluna;

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

            const string mensagem() const noexcept;

        };
}}


#endif //COMPILER_SCANNEREXCEPTION_H
