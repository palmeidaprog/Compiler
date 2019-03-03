/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "ScannerException.h"

palmeidaprog::compilter::ScannerException::ScannerException(
        const string &mensagem, unsigned linha, unsigned coluna) :
        linha(linha), coluna(coluna), mensagem(mensagem) {

}

palmeidaprog::compilter::ScannerException::~ScannerException() {

}


