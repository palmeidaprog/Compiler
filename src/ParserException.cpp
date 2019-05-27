/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "ParserException.h"

const char *palmeidaprog::compiler::ParserException::what() const noexcept {
    return runtime_error::what();
}

palmeidaprog::compiler::ParserException::ParserException(const string
        &mensagem, shared_ptr<ScannerReturn> erro) noexcept :
        runtime_error(mensagem), erro(erro) {
}

palmeidaprog::compiler::ParserException::~ParserException() { }

const palmeidaprog::compiler::ScannerReturn
&palmeidaprog::compiler::ParserException::getErro() const noexcept {
    return *erro.get();
}
