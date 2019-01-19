#pragma once
#include <string>
class Token
{
public:
	std::string type;
	std::string value;

	Token(std::string _type, std::string _value);
	Token(const Token& _token);
	Token();
	~Token();
};

