/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */


#include "Parser.h"

palmeidaprog::compiler::Parser::Parser(palmeidaprog::compiler::IScanner
    &scanner) : scanner(scanner), lookAhead(scanner.scanNext()) {
}

palmeidaprog::compiler::Parser::~Parser() {

}

void palmeidaprog::compiler::Parser::programa() {

}

void palmeidaprog::compiler::Parser::bloco() {

}

void palmeidaprog::compiler::Parser::comando() {

}

void palmeidaprog::compiler::Parser::comandoBasico() {

}

void palmeidaprog::compiler::Parser::declaracaoVar() {

}

void palmeidaprog::compiler::Parser::iteracao() {

}

void palmeidaprog::compiler::Parser::exprRelacional() {

}

void palmeidaprog::compiler::Parser::atribuicao() {

}

void palmeidaprog::compiler::Parser::exprAritmetica() {

}

void palmeidaprog::compiler::Parser::termo() {

}

void palmeidaprog::compiler::Parser::fator() {

}

void palmeidaprog::compiler::Parser::parse() {

}

void palmeidaprog::compiler::Parser::proximoToken() {
    lookAhead = scanner.scanNext();
}
