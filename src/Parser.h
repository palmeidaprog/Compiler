/*
 * Compilador C++
 * Paulo R. Almeida Filho
 * <pauloalmeidaf@gmail.com>
 * Compiladores - Prof Silvio Bandeira
 * */


#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <iostream>
#include <sstream>
#include <memory>
#include "IParser.h"
#include "IScanner.h"
#include "ScannerReturn.h"
#include "ScannerException.h"
#include "ParserException.h"
#include "TabelaSimbolos.h"
#include "SemanticReturn.h"
#include "NotDeclaredException.h"
#include "IncompatibleTypesException.h"

using std::unique_ptr;
using std::make_unique;
using std::move;
using std::string;
using std::cout;
using std::stringstream;
using std::endl;

namespace palmeidaprog { namespace compiler {
    class Parser : public IParser {
        IScanner &scanner;
        unique_ptr<ScannerReturn> lookAhead;
        bool finalizado;
        Token tipoVar;
        unique_ptr<TabelaSimbolos> tabela;
        unsigned escopo, tmpCont, labelCont;

    public:
        virtual ~Parser();
        Parser(IScanner &scanner);
        bool isFinalizado() const override {
            return finalizado;
        }

        void parse() override;

        void debugTabela() const noexcept override;

    private:
        void proximoToken();
        void programa();
        void bloco();
        void comando();
        void comandoBasico();
        void declaracaoVar();
        void idVar();
        void iteracao();
        const string exprRelacional();
        const string condicionalWhile();
        void atribuicao();
        unique_ptr<SemanticReturn> exprAritmetica();
        unique_ptr<SemanticReturn> termo();
        unique_ptr<SemanticReturn> fator();
        void condicionalIf();
        void exc(const string &msg);
        void geradorCodigo(const string &codigoGerado) noexcept;
        Token comparaOperacao(const SemanticReturn &obj1, const
                SemanticReturn &obj2, ScannerReturn &operacao);
        Token comparaDivisao(const SemanticReturn &obj1,
                const SemanticReturn &obj2);
        void validaAtribuicao(const SemanticReturn &lhs,
                              const SemanticReturn &rhs);
        void validaRelacional(const SemanticReturn &exp1,
                              const SemanticReturn &exp2);
        const string getProxTmp() noexcept;
        const string getProxLabel() noexcept;
        const string nomeTipo(Token tipo) const;
        const string msgValidaAtribuicao(const string &tipo1,
                const string &tipo2);

        bool isValor() {
            return lookAhead->getToken() == Token::VALOR_FLOAT
                    || lookAhead->getToken() == Token::VALOR_INTEIRO
                    || lookAhead->getToken() == Token::LETRA_VALOR;
        }

        bool operadorRelacional() const {
            return lookAhead->getToken() == Token::MAIOR_IGUAL
                || lookAhead->getToken() == Token::MAIOR
                || lookAhead->getToken() == Token::MENOR
                || lookAhead->getToken() == Token::MENOR_IGUAL
                || lookAhead->getToken() == Token::IGUAL
                || lookAhead->getToken() == Token::DIFERENTE;
        }

        bool isTipo() const {
            return lookAhead->getToken() == Token::INTEIRO
                   || lookAhead->getToken() == Token::FLOAT
                   || lookAhead->getToken() == Token::LETRA
                   || lookAhead->getToken() == Token::INTEIRO;
        }

        // -- Checagem tipo Semantico ----------------------------------------
        unique_ptr<SemanticReturn> checaTipos(unique_ptr<SemanticReturn> id1,
                unique_ptr<SemanticReturn> id2, Token operacao);
        bool combinacaoTipos(SemanticReturn &id1, SemanticReturn &id2,
                Token tipo1, Token tipo2);
     };
}}



#endif //COMPILER_PARSER_H
