#pragma once
#include "Lexer.h"
#include "BinaryOperation.h"
#include "Number.h"

class Parser
{
	Lexer* lexer;
	Token* currentToken;
public:
	Parser(Lexer* _lexer);
	~Parser();
	void Error();
	void Eat(std::string tokenType);
	AST* Factor();
	AST* Term();
	AST* Expression();
	AST* Parse();
};

