//
// Created by Paulo Roberto Almeida Filho on 24/05/19.
//

#include "SemanticReturn.h"

palmeidaprog::compiler::SemanticReturn::SemanticReturn(const
        palmeidaprog::compiler::ScannerReturn &scannerReturn, int escopo) :
        ScannerReturn(scannerReturn), escopo(escopo) {
}

palmeidaprog::compiler::SemanticReturn::~SemanticReturn() {

}
