/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "NotDeclaredException.h"


palmeidaprog::compiler::NotDeclaredException::
NotDeclaredException(const string &mensagem,
                     shared_ptr<SemanticReturn> erro) noexcept :
        runtime_error(mensagem), erro(erro){
}

palmeidaprog::compiler::NotDeclaredException::
~NotDeclaredException() {
}

const palmeidaprog::compiler::SemanticReturn &
palmeidaprog::compiler::NotDeclaredException::getErro() const
noexcept {
    return *erro.get();
}

const char *palmeidaprog::compiler::NotDeclaredException::what() const
noexcept {
    return runtime_error::what();
}

// operacao impossivel
// atribuicao impossivel
// variavel nao declarada
//