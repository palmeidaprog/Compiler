//
// Created by Paulo Roberto Almeida Filho on 2/23/19.
//

#ifndef COMPILER_SCANNERFACTORY_H
#define COMPILER_SCANNERFACTORY_H

#include <memory>
#include "IScanner.h"
#include "Scanner.h"

using std::unique_ptr;
using std::make_unique;

namespace palmeidaprog { namespace compiler {
    class ScannerFactory {
    public:
        static unique_ptr<IScanner> getInstance(char *arquivo);
        static unique_ptr<IScanner> getInstance(const std::string &arquivo);
    };
}}

#endif //COMPILER_SCANNERFACTORY_H
