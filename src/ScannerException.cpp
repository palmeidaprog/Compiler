/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "ScannerException.h"

palmeidaprog::compiler::ScannerException::ScannerException(
        const string &mensagem, unsigned linha, unsigned coluna) :
        linha(linha), coluna(coluna), runtime_error(mensagem) {
}

palmeidaprog::compiler::ScannerException::~ScannerException() {

}

const string palmeidaprog::compiler::ScannerException::mensagem() const
        noexcept {
        stringstream s;
        s << "Scanner Linha: " << linha << " Coluna: " << coluna
                   << " :" << this->what();
        return s.str();
    }
}


