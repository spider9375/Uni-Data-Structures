#include "stdafx.h"
#include "Var.h"


Var::Var(Token* _token)
{
	this->token = _token;
	this->name = this->token->value;
}


Var::~Var()
{
}
