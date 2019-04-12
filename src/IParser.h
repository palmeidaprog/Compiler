/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */


#ifndef COMPILER_IPARSER_H
#define COMPILER_IPARSER_H

#include <memory>

using std::make_unique;
using std::unique_ptr;

namespace palmeidaprog { namespace compiler {
    class IParser {
    public:
        // virtual Tabela &getTabela() = 0
        //virtual ArvoreGramatica<Scanner>
        virtual void parse() = 0;
        virtual bool isFinalizado() const = 0;
    };

}}

#endif //COMPILER_IPARSER_H
