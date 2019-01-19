#pragma once
#include "Token.h"
#include "AST.h"
class Number : public AST
{
public:
	Token* token;
	unsigned long int value;
	Number(Token* _token);
	Number();
	~Number();
};

