#pragma once
#include "Globals.h"
class Lexer
{
	int pos;
	char currentChar;

public:
	std::string text;
	Lexer(std::string _text);
	~Lexer();
	Token* Id();
	void Error();
	void Advance();
	void skipWhitespace();
	unsigned long int Integer();
	char Peek();
	Token* GetNextToken();

};

