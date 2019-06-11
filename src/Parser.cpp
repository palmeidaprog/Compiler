/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */

#include "Parser.h"
#include "IncompatibleTypesException.h"

palmeidaprog::compiler::Parser::Parser(palmeidaprog::compiler::IScanner
    &scanner) : scanner(scanner), finalizado(false),
    tabela(make_unique<TabelaSimbolos>()), escopo(0), tmpCont(1),
    labelCont(1) {
}

palmeidaprog::compiler::Parser::~Parser() {

}

void palmeidaprog::compiler::Parser::programa() {
    lookAhead = scanner.scanNext();
    if(lookAhead->getToken() == Token::INTEIRO) {
        proximoToken();
        if(lookAhead->getToken() == Token::MAIN) {
            proximoToken();
            if(lookAhead->getToken() == Token::ABRE_PARENTESES) {
                proximoToken();
                if(lookAhead->getToken() == Token::FECHA_PARENTESES) {
                    proximoToken();
                    bloco();
                    return;
                } else {
                    exc("Parenteses não fechados");
                }
            } else {
                exc("Esperado parenteses apos main");
            }
        } else {
            exc("O nome da funcao precisa ser main");
        }
    } else {
        exc("Programa tem que começar com o tipo do retorno int na função main");
    }
}

void palmeidaprog::compiler::Parser::bloco() {
    if(lookAhead->getToken() == Token::ABRE_CHAVE) {
        proximoToken(); // lida chaves
        ++escopo;
    } else {
        exc("Bloco de código necessita de abre chaves");
    }

    while(isTipo()) {
        declaracaoVar();
    }

    while(lookAhead->getToken() != Token::FECHA_CHAVE) {
        if(isTipo()) {
            exc(string("Variáveis só podem ser declaradas no começo do ")
                .append("escopo. Impossível declarar após utilização de ")
                .append("comandos"));
        }

        if(lookAhead->getToken() == Token::FIM_ARQUIVO) {
            exc("Fim de arquivo encontrado com chaves não fechada.");
        }
        comando();
    }
    proximoToken();
    tabela->destroiEscopo(escopo--); // destroi variaveis do escopo
}

void palmeidaprog::compiler::Parser::comando() {
    if(lookAhead->getToken() == Token::DO ||
        lookAhead->getToken() == Token::WHILE) {
        iteracao();
    } else if(lookAhead->getToken() == Token::IF) {
        condicionalIf();
    } else {
        comandoBasico();
    }
}

void palmeidaprog::compiler::Parser::comandoBasico() {
    // TODO: solve the wrong message on some cases (Invalid command)
    if(lookAhead->getToken() == Token::IDENTIFICADOR) {
        atribuicao();
    } else {
        bloco();
    }
}

// declaracao de variaveis;
void palmeidaprog::compiler::Parser::declaracaoVar() {
    tipoVar = lookAhead->getToken();
    proximoToken(); // passa o tipo
    idVar();
}


const string palmeidaprog::compiler::Parser::condicionalWhile() {
    if (lookAhead->getToken() == Token::ABRE_PARENTESES) {
        proximoToken();
        string expressao = exprRelacional();
        if (lookAhead->getToken() == Token::FECHA_PARENTESES) {
            proximoToken();
            return expressao;
        } else {
            exc("Parenteses não fechado na condicional do while");
        }
    } else {
        exc("Esperado parenteses com condicional após while");
    }
}

void palmeidaprog::compiler::Parser::iteracao() {
    if(lookAhead->getToken() == Token::DO) {
        stringstream s;
        string l = getProxLabel();
        s << "\nEscopoDO_" << l << ":";
        geradorCodigo(s.str());
        proximoToken();
        comando();
        if(lookAhead->getToken() == Token::WHILE) {
            proximoToken();
            s.str(string());
            s << "if " << condicionalWhile() << " goto " << "EscopoDO_" << l
                << endl;
            if(lookAhead->getToken() != Token::PONTO_VIRGULA) {
                exc("Esperado \";\" após a condicional de um do-while");
            } else {
                geradorCodigo(s.str());
                proximoToken();
            }
        } else {
            exc("\"while\" esperado apos fechamento do bloco apos \"do\"");
        }
    } else if(lookAhead->getToken() == Token::WHILE) {
        proximoToken();
        stringstream s;
        string l = getProxLabel();
        s << "\nTesteWHILE_" << l << ":" << endl;
        s << "if " << condicionalWhile() << " goto EscopoWHILE_" << l << endl
            << "goto SaidaWHILE_" << l << endl << "EscopoWHILE_" << l << ":";
        geradorCodigo(s.str());
        comando();
        s.str(string());
        s << "goto TesteWHILE_" << l << endl
            << "SaidaWHILE_" << l << ":\n";
        geradorCodigo(s.str());
    }
}

const string palmeidaprog::compiler::Parser::exprRelacional() {
    stringstream s;
    auto exp1 = exprAritmetica();
    s << exp1->getLexema() << " ";

    if(operadorRelacional()) {
        auto op = make_unique<SemanticReturn>(*lookAhead, escopo);
        s << op->getLexema();
        proximoToken();
        auto exp2 = exprAritmetica();
        validaRelacional(*exp1, *exp2);
        s << " " << exp2->getLexema();
    } else {
        exc("Esperado operador relacional (<,>,>=.<=,==,!=) após expressão");
    }
    return s.str();
}

void palmeidaprog::compiler::Parser::atribuicao() {
    auto simbolo = tabela->procura(lookAhead->getLexema(), escopo);
    if(simbolo == nullptr) {
        stringstream s;
        s << "Variavel não foi declarada";
        throw NotDeclaredException(s.str(),
                make_unique<SemanticReturn>(*lookAhead, escopo));
    }
    auto lhs = make_unique<SemanticReturn>(*lookAhead, escopo,
            simbolo->getTipo());
    proximoToken();
    if(lookAhead->getToken() == Token::ATRIBUICAO) {
        proximoToken();
        auto rhs = exprAritmetica();
        if(lookAhead->getToken() == Token::PONTO_VIRGULA) {
            validaAtribuicao(*lhs, *rhs);
            stringstream s;
            s << lhs->getLexema() << " = " << rhs->getLexema();
            geradorCodigo(s.str());
            proximoToken();
        } else {
            exc("Esperado ; apos atribuição");
        }
    } else {
        exc("Esperado =, atribuicao necessita do igual apos o identificador");
    }
}


void palmeidaprog::compiler::Parser::validaAtribuicao(
        const palmeidaprog::compiler::SemanticReturn &lhs,
        const palmeidaprog::compiler::SemanticReturn &rhs) {
    if((lhs.getTipoGenerico() == Token::LETRA &&
            rhs.getTipoGenerico() != Token::LETRA)
        || (lhs.getTipoGenerico() == Token::INTEIRO &&
            rhs.getTipoGenerico() != Token::INTEIRO)
        || (lhs.getTipoGenerico() == Token::FLOAT &&
            rhs.getTipoGenerico() == Token::LETRA)) {
        throw IncompatibleTypesException(msgValidaAtribuicao(
                nomeTipo(lhs.getTipoGenerico()),
                nomeTipo(rhs.getTipoGenerico())), lhs, rhs);
    }
}

unique_ptr<palmeidaprog::compiler::SemanticReturn>
        palmeidaprog::compiler::Parser::exprAritmetica() {
    auto semanticoTermo = termo();
    if(lookAhead->getToken() == Token::SOMA
        || lookAhead->getToken() == Token::SUBSTRACAO) {
        auto op = move(lookAhead);
        proximoToken();
        auto semanticoExpr = exprAritmetica();
        stringstream s;
        string t = getProxTmp();
        s << t << " = " << semanticoTermo->getLexema() << " "
          << op->getLexema() << " ";
        s << semanticoExpr->getLexema();
        Token tipo = comparaOperacao(*semanticoTermo, *semanticoExpr, *op);
        geradorCodigo(s.str());
        return make_unique<SemanticReturn>(*semanticoTermo, escopo, t, tipo);
    }
    return move(semanticoTermo);
}

unique_ptr<palmeidaprog::compiler::SemanticReturn>
        palmeidaprog::compiler::Parser::termo() {
    auto semanticoFator = fator();

    while(lookAhead->getToken() == Token::MULTIPLICACAO
        || lookAhead->getToken() == Token::DIVISAO) {
        stringstream s, f;

        auto op = move(lookAhead);
        proximoToken();
        auto semanticoTermo = fator();
        Token tipo;
        if(op->getToken() == Token::DIVISAO) {
            tipo = comparaDivisao(*semanticoFator, *semanticoTermo);
        } else {
            tipo = comparaOperacao(*semanticoFator, *semanticoTermo, *op);
        }
        string t = getProxTmp();
        s << t << " = " << semanticoFator->getLexema() << " " <<
          op->getLexema() << " ";
        s << semanticoTermo->getLexema();
        semanticoFator = make_unique<SemanticReturn>(*lookAhead, escopo, t,
                tipo);
        geradorCodigo(s.str());
    }
    return move(semanticoFator);
}

unique_ptr<palmeidaprog::compiler::SemanticReturn>
        palmeidaprog::compiler::Parser::fator() {
    if(isValor() || lookAhead->getToken() == Token::IDENTIFICADOR) {
        unique_ptr<SemanticReturn> semantico;
        if(lookAhead->getToken() == Token::IDENTIFICADOR) {
            unique_ptr<Simbolo> simb = tabela->procura(lookAhead->getLexema(), escopo);
            if(simb == nullptr) {
                stringstream s;
                s << "Variável " << lookAhead->getLexema() << "não foi " <<
                        "declarada";
                semantico = make_unique<SemanticReturn>(*lookAhead, escopo);
                throw NotDeclaredException(s.str(), move(semantico));
            } else {
                semantico = make_unique<SemanticReturn>(*lookAhead, escopo,
                        simb->getTipo());
            }
        } else {
            semantico = make_unique<SemanticReturn>(*lookAhead, escopo);
        }
        proximoToken();
        return move(semantico);
    } else if(lookAhead->getToken() == Token::ABRE_PARENTESES) {
        proximoToken();
        auto semantico = exprAritmetica();
        if(lookAhead->getToken() == Token::FECHA_PARENTESES) {
            proximoToken();
            return move(semantico);
        } else {
            exc("Parenteses malformado na expressão aritmética");
        }
    } else {
        exc("Esperado valor constante ou variavel");
    }
}

void palmeidaprog::compiler::Parser::parse() {
    programa();
    finalizado = true;
    if(lookAhead->getToken() != Token::FIM_ARQUIVO) {
        exc("Código encontrado fora da função main");
    }
}

void palmeidaprog::compiler::Parser::proximoToken() {
    lookAhead = scanner.scanNext();
}

void palmeidaprog::compiler::Parser::exc(const string &msg) {
    throw ParserException(msg, move(lookAhead));
}

// pega os identifcadores das variaveis
void palmeidaprog::compiler::Parser::idVar() {
    if(lookAhead->getToken() == Token::IDENTIFICADOR) {
        // TODO: verify if tipoVar is really correct or to switch to getTipo()
        tabela->adiciona(new Simbolo(lookAhead->getLexema(), tipoVar,
                escopo));
        /* TODO: remove this
        tabela.emplace(lookAhead->getLexema(),
                make_unique<Simbolo>(lookAhead->getLexema(), tipoVar));*/
        proximoToken();
        if(lookAhead->getToken() == Token::PONTO_VIRGULA) {
            proximoToken();
            return;
        } else if(lookAhead->getToken() == Token::VIRGULA) {
            proximoToken();
            idVar();
        } else {
            exc("Esperado ; ou , na declaracao de variável(is).");
        }
    } else {
        exc("Identificador da variavel esperado.");
    }
}

void palmeidaprog::compiler::Parser::condicionalIf() {
    if(lookAhead->getToken() == Token::IF) {
        proximoToken();
        if(lookAhead->getToken() == Token::ABRE_PARENTESES) {
            proximoToken();
            stringstream s;
            string l = getProxLabel();

            s << "\nif " << exprRelacional() << " goto EscopoIF_" << l << endl <<
                "goto EscopoELSE_" << l << endl << "EscopoIF_" << l << ":";
            if(lookAhead->getToken() == Token::FECHA_PARENTESES) {
                proximoToken();
                geradorCodigo(s.str());
                s.str(string());
                comando();
                s << "goto SAIDA_" << l << endl << "EscopoELSE_" << l << ":";
                geradorCodigo(s.str());
                s.str(string());
                if(lookAhead->getToken() == Token::ELSE) {
                    proximoToken();
                    comando();
                }
                s << "Saida_" << l << ":\n";
                geradorCodigo(s.str());
            } else {
                exc(string("Parenteses malformado, fecha parenteses esperado")
                            .append(" após condicional do if"));
            }
        } else {
            exc("() Abre parenteses com condicional esperada após um if");
        }
    }
}

void palmeidaprog::compiler::Parser::debugTabela() const noexcept {
    tabela->debug();
}

unique_ptr<palmeidaprog::compiler::SemanticReturn>
        palmeidaprog::compiler::Parser::checaTipos(
            unique_ptr<palmeidaprog::compiler::SemanticReturn> id1,
            unique_ptr<palmeidaprog::compiler::SemanticReturn> id2,
            Token operacao) {
    if(combinacaoTipos(*id1.get(), *id2.get(), Token::LETRA, Token::LETRA)) {
        return move(id1);
    } else if(combinacaoTipos(*id1.get(), *id2.get(), Token::LETRA, Token::FLOAT)) {
        //TODO: Concluir chegacagem de tipos (Combinacao ou arranjo)
    }
}

bool palmeidaprog::compiler::Parser::combinacaoTipos(
        palmeidaprog::compiler::SemanticReturn &id1,
        palmeidaprog::compiler::SemanticReturn &id2, Token tipo1,
        Token tipo2) {
    return (id1.getTipoGenerico() == tipo1 && id2.getTipoGenerico() == tipo2)
        || (id1.getTipoGenerico() == tipo2 && id2.getTipoGenerico() == tipo1);
}

void palmeidaprog::compiler::Parser::geradorCodigo(const string &codigoGerado)
        noexcept {
    cout << codigoGerado << endl;
}

Token palmeidaprog::compiler::Parser::comparaOperacao(
        const palmeidaprog::compiler::SemanticReturn &obj1,
        const palmeidaprog::compiler::SemanticReturn &obj2,
        ScannerReturn &operacao) {
    if(obj1.getTipoGenerico() == obj2.getTipoGenerico()) {
        return obj1.getTipoGenerico();
    } else if(obj1.getTipoGenerico() == Token::LETRA ||
            obj2.getTipoGenerico() == Token::LETRA) {
        stringstream s;
        s << "Tipo char só pode ";
        if(operacao.getToken() == Token::SOMA) {
            s << "somar ";
        } else if(operacao.getToken() == Token::SUBSTRACAO) {
            s << "subtrair ";
        } else {
            s << "multiplicar ";
        }
        s << "com outro" << " char";
        throw IncompatibleTypesException(s.str(), obj1, obj2);
    } else if(obj1.getTipoGenerico() == Token::FLOAT ||
        obj2.getTipoGenerico() == Token::FLOAT) {
        return Token::FLOAT;
    } else {
        return Token::INTEIRO;
    }
}

Token palmeidaprog::compiler::Parser::comparaDivisao(
        const palmeidaprog::compiler::SemanticReturn &obj1,
        const palmeidaprog::compiler::SemanticReturn &obj2) {
    if(obj1.getTipoGenerico() == Token::LETRA &&
        obj2.getTipoGenerico() == Token::LETRA) {
        return Token::LETRA;
    } else if(obj1.getTipoGenerico() == Token::LETRA ||
              obj2.getTipoGenerico() == Token::LETRA) {
        stringstream s;
        s << "Tipo char só pode dividir com outro tipo char";
        throw IncompatibleTypesException(s.str(), obj1, obj2);
    } else {
        return Token::FLOAT;
    }
}

const string palmeidaprog::compiler::Parser::getProxTmp() noexcept {
    stringstream s;
    s << "t" << tmpCont++;
    return s.str();
}

const string palmeidaprog::compiler::Parser::getProxLabel() noexcept {
    stringstream s;
    s << labelCont++;
    return s.str();
}

const string palmeidaprog::compiler::Parser::nomeTipo(Token tipo) const {
    switch(tipo) {
        case Token::LETRA:
            return "char";
        case Token::FLOAT:
            return "float";
        case Token::INTEIRO:
            return "inteiro";
        default:
            return ""; // logicamente inalcançavel
    }
}

const string palmeidaprog::compiler::Parser::msgValidaAtribuicao(
        const string &tipo1, const string &tipo2) {
    stringstream s;
    s << "Variavel " << tipo1 << " não pode receber valor " <<
        tipo2;
    return s.str();
}

void palmeidaprog::compiler::Parser::validaRelacional(
        const palmeidaprog::compiler::SemanticReturn &exp1,
        const palmeidaprog::compiler::SemanticReturn &exp2) {
    if((exp1.getTipoGenerico() == Token::LETRA &&
        exp2.getTipoGenerico() != Token::LETRA) ||
        (exp1.getTipoGenerico() != Token::LETRA &&
        exp2.getTipoGenerico() == Token::LETRA)) {
        throw IncompatibleTypesException(
                string("Char só pode ser comparado com char"), exp1, exp2);
    }
}








