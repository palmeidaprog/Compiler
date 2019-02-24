/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "Scanner.h"

palmeidaprog::compiler::Token palmeidaprog::compiler::Scanner::scanNext() {
    return Token::ABRE_CHAVE;
}

string palmeidaprog::compiler::Scanner::getValor() {
    return valor;
}

palmeidaprog::compiler::Scanner::Scanner(const string &arquivo) :
    arquivo(arquivo) {
}

palmeidaprog::compiler::Scanner::Scanner(char *arquivo) :
    arquivo(string(arquivo)) {
    abreArquivo();
}

palmeidaprog::compiler::Scanner::~Scanner() {

}

void palmeidaprog::compiler::Scanner::abreArquivo() {

}

