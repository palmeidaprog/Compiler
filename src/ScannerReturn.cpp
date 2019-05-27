/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "ScannerReturn.h"


palmeidaprog::compiler::ScannerReturn::ScannerReturn(Token token,
        const string &lexema, int coluna, int linha) : token(token),
        lexema(lexema), coluna(coluna), linha(linha) {

}

palmeidaprog::compiler::ScannerReturn::~ScannerReturn() {

}

palmeidaprog::compiler::ScannerReturn::ScannerReturn(const
        palmeidaprog::compiler::ScannerReturn &toCopy) : token(toCopy.token),
        lexema(toCopy.lexema), coluna(toCopy.coluna), linha(toCopy.linha) {

}
