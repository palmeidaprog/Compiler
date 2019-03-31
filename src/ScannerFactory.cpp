//
// Created by Paulo Roberto Almeida Filho on 2/23/19.
//

#include "ScannerFactory.h"

unique_ptr<palmeidaprog::compiler::IScanner>
palmeidaprog::compiler::ScannerFactory::getInstance(char *arquivo) {
    return make_unique<Scanner>(arquivo);
}

unique_ptr<palmeidaprog::compiler::IScanner>
palmeidaprog::compiler::ScannerFactory::getInstance(const std::string
        &arquivo) {
    return make_unique<Scanner>(arquivo);
}
