//
// Created by Paulo Roberto Almeida Filho on 3/30/19.
//

#include "ParserFactory.h"

unique_ptr<palmeidaprog::compiler::IParser>
palmeidaprog::compiler::ParserFactory::getInstance(palmeidaprog::compiler::IScanner &scanner) {
    return make_unique<palmeidaprog::compiler::IParser>(scanner);
}
