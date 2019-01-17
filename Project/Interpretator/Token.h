#pragma once
#include "Globals.h"

class Token
{
public:
	std::string type;
	std::string value;

	Token(std::string _type, std::string _value);
	~Token();
};

