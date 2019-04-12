/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */


#include "Compilador.h"


palmeidaprog::compiler::Compilador::Compilador(char *arquivo) :
    scanner(ScannerFactory::getInstance(arquivo)), arquivo(string(arquivo)),
    parser(ParserFactory::getInstance(*scanner.get())){

}

palmeidaprog::compiler::Compilador::Compilador(const string &arquivo) :
    scanner(ScannerFactory::getInstance(arquivo)), arquivo(arquivo),
    parser(ParserFactory::getInstance(*scanner.get())) {
}

palmeidaprog::compiler::Compilador::~Compilador() {

}

void palmeidaprog::compiler::Compilador::compilar() {
    unique_ptr<ScannerReturn> r;
    string s = "Fim de arquivo encontrado antes da finalização do programa. ";
    try {
        parser->parse();
    } catch(const ScannerException &sExc) {
        cout << "ERRO na linha " << sExc.getLinha() << ", coluna " <<
             sExc.getColuna() << ", Ultimo token lido: \"" << sExc.getLexema()
             << "\" Mensagem: " << sExc.what() << endl;
    } catch(const ParserException &pExc) {
        s = ""; // debug
        if(parser->isFinalizado()) {
            s = "";
        }
        cout << "ERRO na linha " << pExc.getErro().getLinha() << ", coluna " <<
            pExc.getErro().getColuna() << ", \"" << pExc.getErro().getLexema()
            << "\" " << s << pExc.what()
            << endl;
    } catch(const std::runtime_error &runt) {
        cout << runt.what() << endl;
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
        cout << "[Linha:" << e.getLinha() << " Coluna:" <<  e.getColuna()
             << "] " <<  e.what() << endl;
    }
}

void palmeidaprog::compiler::Compilador::tokenToStr(
        palmeidaprog::compiler::Token token) {
}
