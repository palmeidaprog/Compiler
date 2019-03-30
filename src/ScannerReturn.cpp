//
// Created by Paulo Roberto Almeida Filho on 3/29/19.
//

#include "ScannerReturn.h"


palmeidaprog::compiler::ScannerReturn::ScannerReturn(Token token,
        const string &lexema, int coluna, int linha) : token(token),
        lexema(lexema), coluna(coluna), linha(linha) {

}

palmeidaprog::compiler::ScannerReturn::~ScannerReturn() {

}
