#pragma once
#include "Lexer.h"

class Interpreter
{
	Lexer* lexer;
	Token* currentToken = nullptr;

public:
	Interpreter(Lexer* _lexer);
	~Interpreter();
	void Error();
	void Eat(std::string tokenType);
	unsigned long int Factor();
	unsigned long int Term();
	unsigned long int Expression();

};

