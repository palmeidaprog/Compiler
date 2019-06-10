/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "SemanticReturn.h"

palmeidaprog::compiler::SemanticReturn::SemanticReturn(const
        palmeidaprog::compiler::ScannerReturn &scannerReturn, int escopo) :
        ScannerReturn(scannerReturn), escopo(escopo),
        tipoGenerico(selecionaTipoGenerico(getToken())) {
}



palmeidaprog::compiler::SemanticReturn::~SemanticReturn() {

}

Token palmeidaprog::compiler::SemanticReturn::selecionaTipoGenerico(
        Token tipo) {
    if(tipo == Token::VALOR_FLOAT || tipo == Token::FLOAT) {
        return Token::FLOAT;
    } else if(tipo == Token::VALOR_INTEIRO || tipo == Token::INTEIRO) {
        return Token::INTEIRO;
    } else if(tipo == Token::LETRA || tipo == Token::LETRA_VALOR) {
        return Token::LETRA;
    }
}

palmeidaprog::compiler::SemanticReturn::SemanticReturn(
        const palmeidaprog::compiler::ScannerReturn &scannerReturn,
        int escopo, Token tipoGenerico) : ScannerReturn(scannerReturn),
        escopo(escopo), tipoGenerico(selecionaTipoGenerico(tipoGenerico)) {

}
