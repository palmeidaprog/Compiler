/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */


#include "ParserFactory.h"

unique_ptr<palmeidaprog::compiler::IParser>
palmeidaprog::compiler::ParserFactory::getInstance(palmeidaprog::compiler::IScanner &scanner) {
    return make_unique<palmeidaprog::compiler::Parser>(scanner);
}
