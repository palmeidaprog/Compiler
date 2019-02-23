/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include <iostream>
#include "Compilador.h"

using std::cerr;
using std::endl;

using palmeidaprog::compiler::Compilador;

int main(int argc, char *argv[]) {
    if(argc == 2) {
        Compilador compilador(argv[1]);
    } else if(argc == 1) {
        cerr << "Você precisa especificar o arquivo fonte a ser compilado"
            << endl
            << "Uso: compiler nome_do_arquivo.cmp" << endl;
    } else {
        cerr << "Muitos argumentos" << endl
            << "Uso: compiler nome_do_arquivo.cmp" << endl;
    }
}