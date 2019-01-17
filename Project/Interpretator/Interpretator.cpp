// Interpretator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <locale>

#define INTEGER ("INTEGER")
#define PLUS ("PLUS")
#define EOF ("EOF")
std::string::size_type sz;

struct Token
{
	std::string type;
	std::string value;

	Token(std::string _type, std::string _value)
	{
		this->type = _type;
		this->value = _value;
	}
};

struct Variable
{
	std::string name;
	unsigned long int value;

	Variable(std::string _name, unsigned long int _value)
	{
		this->name = _name;
		this->value = _value;
	}
};

struct Interpreter
{
	std::string text;
	int pos = 0;
	std::string currentToken = nullptr;
	char* currentChar = &text[this->pos];

	void Advance()
	{
		this->pos++;
		if (this->pos > this->text.size() - 1)
		{
			this->currentChar = nullptr;
		}
		else
		{
			this->currentChar = &this->text[this->pos];
		}
	}

	void skipWhitespace()
	{
		while (this->currentChar != nullptr &&  this->currentChar != " ")
		{
			this->Advance();
		}
	}

	int Integer()
	{
		std::string result = "";
		while (this->currentChar != nullptr && isdigit(std::stoi(this->currentChar)))
		{
			result += this->currentChar;
			this->Advance();
		}

		return std::stoi(result);
	}

};

int _tmain(int argc, _TCHAR* argv[])
{
	std::string input;
	std::vector<Variable*> variables;

	while (std::getline(std::cin, input))
	{
		if (input == "")
		{
			return 0;
		}
		int equalIndex = input.find_first_of('=');
		std::string name = input.substr(0, equalIndex);
		int value = std::stoi(input.substr(equalIndex + 1, input.size()), &sz);
		Variable *temp = new Variable(name, value);
		variables.push_back(temp);

		std::cout << "name: " << temp->name << std::endl;
		std::cout << "value: " << temp->value << std::endl;
	}
	return 0;
}

