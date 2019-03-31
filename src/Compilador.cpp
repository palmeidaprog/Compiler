/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */


#include "Compilador.h"
#include "ParserFactory.h"

palmeidaprog::compiler::Compilador::Compilador(char *arquivo) :
    scanner(ScannerFactory::getInstance(arquivo)), arquivo(string(arquivo)),
    parser(ParserFactory::getInstance(*scanner.get())){

}

palmeidaprog::compiler::Compilador::Compilador(const string &arquivo) :
    scanner(ScannerFactory::getInstance(arquivo)), arquivo(arquivo){
}

palmeidaprog::compiler::Compilador::~Compilador() {

}

void palmeidaprog::compiler::Compilador::compilar() {
    try {

    } catch(const ScannerException &sExc) {
        cerr << "[Linha:" << sExc.getLinha() << " Coluna:" << sExc.getColuna()
             << "] " <<  sExc.what() << endl;
    } catch(const ParserException &pExc) {
        cerr << "[Linha:" << pExc.getErro().getLinha() << " Coluna:" << sExc.getColuna()
             << "] " <<  sExc.what() << endl;
    }
}

void palmeidaprog::compiler::Compilador::debugScanner() {
    unique_ptr<ScannerReturn> r;
    Token token = Token::FIM_ARQUIVO;
    try {
        do {
            r = scanner->scanNext();
            cout << r->getToken() << "(" << r->getLexema() << " c:" <<
                r->getColuna() << " l:" << r->getLinha() << ")" << endl;
        } while(r->getToken() != Token::FIM_ARQUIVO);
    } catch (const ScannerException &e) {
        cout << "[Linha:" << e.getLinha() << " Coluna:" << e.getColuna()
             << "] " <<  e.what() << endl;
    }
}

void palmeidaprog::compiler::Compilador::tokenToStr(
        palmeidaprog::compiler::Token token) {
}
