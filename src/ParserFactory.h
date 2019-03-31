//
// Created by Paulo Roberto Almeida Filho on 3/30/19.
//

#ifndef COMPILER_PARSERFACTORY_H
#define COMPILER_PARSERFACTORY_H

#include <memory>
#include "IScanner.h"
#include "IParser.h"
#include "Parser.h"

using std::unique_ptr;

namespace palmeidaprog { namespace compiler {
    class ParserFactory {
    public:
        static unique_ptr<IParser> getInstance(IScanner &scanner);
    };
}}


#endif //COMPILER_PARSERFACTORY_H
