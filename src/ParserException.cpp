//
// Created by Paulo Roberto Almeida Filho on 3/30/19.
//

#include "ParserException.h"

const char *palmeidaprog::compiler::ParserException::what() const noexcept {
    return runtime_error::what();
}

palmeidaprog::compiler::ParserException::ParserException(const string &mensagem,
        shared_ptr<ScannerReturn> erro) noexcept :
        runtime_error(mensagem), erro(erro) {
}

palmeidaprog::compiler::ParserException::~ParserException() { }

const palmeidaprog::compiler::ScannerReturn
&palmeidaprog::compiler::ParserException::getErro() const noexcept {
    return *erro.get();
}
