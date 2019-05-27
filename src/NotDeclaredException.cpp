/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "NotDeclaredException.h"


palmeidaprog::compiler::NotDeclaredException::
NotDeclaredException(const string &mensagem,
                           shared_ptr<palmeidaprog::compiler::SemanticReturn> erro,
                           shared_ptr<palmeidaprog::compiler::SemanticReturn> var2) noexcept :
        runtime_error(mensagem), erro(erro){
}

palmeidaprog::compiler::NotDeclaredException::
~NotDeclaredException() {
}

const palmeidaprog::compiler::SemanticReturn &
palmeidaprog::compiler::NotDeclaredException::getVar1() const
noexcept {
    return *erro.get();
}

const palmeidaprog::compiler::SemanticReturn &
palmeidaprog::compiler::NotDeclaredException::getVar2() const
noexcept {
    return *var2.get();
}

const char *palmeidaprog::compiler::NotDeclaredException::what() const
noexcept {
    return runtime_error::what();
}

// operacao impossivel
// atribuicao impossivel
// variavel nao declarada
//