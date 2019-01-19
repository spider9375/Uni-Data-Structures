#pragma once
#include "Lexer.h"
#include "BinaryOperation.h"
#include "Number.h"
#include "Var.h"
#include "Assign.h"
#include "NoOp.h"
#include "Print.h"

class Parser
{
	Token* currentToken;
public:
	Lexer* lexer;
	Parser(Lexer* _lexer);
	~Parser();
	void Error();
	void Eat(std::string tokenType);
	AST* Factor();
	AST* Term();
	AST* Expression();
	AST* Parse();
	AST* AssignStatement();
	AST* PrintStatement();
	Var* Variable();
	AST* Statement();
	AST* Empty();
};

