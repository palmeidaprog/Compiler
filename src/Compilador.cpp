/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */


#include "Compilador.h"

palmeidaprog::compiler::Compilador::Compilador(char *arquivo) :
    scanner(ScannerFactory::getInstance(arquivo)), arquivo(string(arquivo)) {

}

palmeidaprog::compiler::Compilador::Compilador(const string &arquivo) :
    scanner(ScannerFactory::getInstance(arquivo)){
}

palmeidaprog::compiler::Compilador::~Compilador() {

}
