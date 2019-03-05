/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "ScannerException.h"

palmeidaprog::compiler::ScannerException::ScannerException(
        const string &mensagem, unsigned linha, unsigned coluna) noexcept :
        runtime_error(mensagem), linha(linha), coluna(coluna) {

}

palmeidaprog::compiler::ScannerException::~ScannerException() {

}

/*string palmeidaprog::compiler::ScannerException::msg() const {
    stringstream s;
    s << "Scanner Linha: " << linha << " Coluna: " << coluna
               << " :" << this->what();
    return s.str();
}*/

palmeidaprog::compiler::ScannerException::ScannerException(const string &s)
        noexcept: runtime_error(s), linha(0), coluna(0) {

}

const char *palmeidaprog::compiler::ScannerException::what() const noexcept {
    return runtime_error::what();
}


