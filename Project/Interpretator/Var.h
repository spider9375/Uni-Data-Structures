#pragma once
#include "AST.h"
#include "Token.h"
class Var : public AST
{
public:
	Token* token;
	std::string name;
	Var(Token* _token);
	~Var();
};

