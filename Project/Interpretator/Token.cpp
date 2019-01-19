#include "stdafx.h"
#include "Token.h"

Token::Token(std::string _type, std::string _value)
{
	this->type = _type;
	this->value = _value;
}

Token::Token(const Token& _token)
{
	this->type = _token.type;
	this->value = _token.value;
}

Token::Token()
{
}

Token::~Token()
{
}
