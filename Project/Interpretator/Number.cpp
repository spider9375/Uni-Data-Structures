#include "stdafx.h"
#include "Number.h"


Number::Number(Token* _token)
{
	this->token = _token;
	this->value = std::stoi(this->token->value);
}

Number::Number()
{
}

Number::~Number()
{
}
