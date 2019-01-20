#pragma once
#include "Lexer.h"
#include "BinaryOperation.h"
#include "Number.h"
#include "Var.h"
#include "Assign.h"
#include "NoOp.h"
#include "Print.h"
#include "Read.h"
#include "Function.h"
#include <cstring>
#include <algorithm>

class Parser
{
	Token* currentToken;
public:
	Lexer* lexer;
	Parser(Lexer* _lexer);
	~Parser();
	void Error();
	void Eat(std::string tokenType);
	std::string GetFuncNameForPrint();
	AST* GetFuncPrintVariable();
	AST* Factor();
	AST* Term();
	AST* Expression();
	AST* Parse();
	AST* FuncStatement();
	AST* AssignStatement();
	AST* ReadStatement();
	AST* PrintStatement();
	Var* Variable();
	AST* Statement();
	AST* Empty();
};

