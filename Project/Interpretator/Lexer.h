#pragma once
#include "Token.h"

class Lexer
{
	std::string text;
	int pos;
	char currentChar;

public:
	Lexer(std::string _text);
	~Lexer();
	void Error();
	void Advance();
	void skipWhitespace();
	unsigned long int Integer();
	Token* GetNextToken();

};

