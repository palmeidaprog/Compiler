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
    scanner(ScannerFactory::getInstance(arquivo)), arquivo(arquivo){
}

palmeidaprog::compiler::Compilador::~Compilador() {

}

void palmeidaprog::compiler::Compilador::compilar() {
    debugScanner();
}

void palmeidaprog::compiler::Compilador::debugScanner() {
    Token token = Token::FIM_ARQUIVO;
    try {
        do {
            token = scanner->scanNext();
            cout << token << "(" << scanner->getLexema() << ")" << endl;
        } while(token != Token::FIM_ARQUIVO);
    } catch (const ScannerException &e) {
        cout << "[Linha:" << e.getLinha() << " Coluna:" << e.getColuna()
             << "] " <<  e.what() << endl;
    }
}

void palmeidaprog::compiler::Compilador::tokenToStr(
        palmeidaprog::compiler::Token token) {
}
