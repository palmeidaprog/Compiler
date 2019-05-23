/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "TabelaSimbolos.h"

palmeidaprog::compiler::TabelaSimbolos::TabelaSimbolos() noexcept {
    tabela.emplace_back(make_unique<hash>());
}

palmeidaprog::compiler::TabelaSimbolos::~TabelaSimbolos() {

}

const palmeidaprog::compiler::Simbolo
*palmeidaprog::compiler::TabelaSimbolos::procura(const string &identificador,
            int escopo)const noexcept {
    while(escopo >= 0) {
        auto it = tabela[escopo]->find(identificador);
        if(it != tabela[escopo].end()) {
            return it->second.get();
        }
        --escopo;
    }
    return nullptr;
}

void palmeidaprog::compiler::TabelaSimbolos::adiciona(
            Simbolo *identificador) {
    if(identificador->getEscopo() == tabela.size()) {
        tabela.emplace_back(make_unique<hash>());
    }
    tabela[identificador->getEscopo()]->emplace(
            identificador->getIdentificador(),
            make_unique<Simbolo>(identificador));
}

void palmeidaprog::compiler::TabelaSimbolos::destroiEscopo(int escopo) {
    if(tabela.size() > escopo) {
        tabela.pop_back();
    }
}
