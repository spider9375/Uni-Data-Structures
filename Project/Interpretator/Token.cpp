#include "stdafx.h"
#include "Token.h"

Token::Token(std::string _type, std::string _value)
{
	this->type = _type;
	this->value = _value;
}


Token::~Token()
{
}
