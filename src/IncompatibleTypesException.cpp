/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "IncompatibleTypesException.h"

palmeidaprog::compiler::IncompatibleTypesException::
        IncompatibleTypesException(const string &mensagem,
                                   shared_ptr<SemanticReturn> var1,
                                   shared_ptr<SemanticReturn> var2) noexcept :
        runtime_error(mensagem), var1(var1), var2(var2){
}

palmeidaprog::compiler::IncompatibleTypesException::
        ~IncompatibleTypesException() {
}

const palmeidaprog::compiler::SemanticReturn &
        palmeidaprog::compiler::IncompatibleTypesException::getVar1() const
        noexcept {
    return *var1.get();
}

const palmeidaprog::compiler::SemanticReturn &
        palmeidaprog::compiler::IncompatibleTypesException::getVar2() const
        noexcept {
    return *var2.get();
}

const char *palmeidaprog::compiler::IncompatibleTypesException::what() const
        noexcept {
    return runtime_error::what();
}

palmeidaprog::compiler::IncompatibleTypesException::IncompatibleTypesException(
        const string &mensagem, const palmeidaprog::compiler::SemanticReturn &var1,
        const palmeidaprog::compiler::SemanticReturn &var2) noexcept :
        runtime_error(mensagem), var1(make_shared<SemanticReturn>(var1)),
        var2(make_shared<SemanticReturn>(var2)) {

}
