// Interpretator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <locale>

std::string INTEGER = "INTEGER";
std::string PLUS = "PLUS";
std::string MINUS = "MINUS";
char NULL_CHAR = '\0';
std::string EoF = "EOF";
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
	Token* currentToken = nullptr;
	char currentChar;

	Interpreter(std::string _text)
	{
		this->text = _text;
		this->pos = 0;
		this->currentToken = nullptr;
		this->currentChar = this->text[this->pos];
	}

	void Error()
	{
		throw std::exception("Error");
	}

	void Advance()
	{
		this->pos++;
		if (this->pos > this->text.size() - 1)
		{
			this->currentChar = NULL_CHAR;
		}
		else
		{
			this->currentChar = this->text[this->pos];
		}
	}

	void skipWhitespace()
	{
		while (this->currentChar != NULL_CHAR &&  this->currentChar == ' ')
		{
			this->Advance();
		}
	}

	int Integer()
	{
		std::string result = "";
		while (this->currentChar != NULL_CHAR && isdigit(this->currentChar))
		{
			result += this->currentChar;
			this->Advance();
		}

		return std::stoi(result);
	}

	Token* GetNextToken()
	{
		while (this->currentChar != NULL_CHAR)
		{
			if (this->currentChar == ' ')
			{
				this->skipWhitespace();
				continue;
			}
			
			if (isdigit(this->currentChar))
			{
				return new Token(INTEGER, std::to_string(this->Integer()));
			}

			if (this->currentChar == '+')
			{
				this->Advance();
				return new Token(PLUS, "+");
			}

			if (this->currentChar == '-')
			{
				this->Advance();
				return new Token(MINUS, "-");
			}

			this->Error();
		}

		return new Token(EoF, EoF);
	}

	void Eat(std::string tokenType)
	{
		if (this->currentToken->type == tokenType)
		{
			this->currentToken = this->GetNextToken();
		}
		else
		{
			this->Error();
		}
	}

	unsigned long int Expression()
	{
		this->currentToken = this->GetNextToken();
		Token* left = this->currentToken;
		this->Eat(INTEGER);

		Token* op = this->currentToken;
		if (op->type == PLUS)
		{
			this->Eat(PLUS);
		}
		else
		{
			this->Eat(MINUS);
		}

		Token* right = this->currentToken;
		this->Eat(INTEGER);
		unsigned int result;

		if (op->type == PLUS)
		{
			result = std::stoi(left->value) + std::stoi(right->value);
		}
		else
		{
			result = std::stoi(left->value) - std::stoi(right->value);
		}

		return result;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::string input;

	while (std::getline(std::cin, input))
	{
		if (input != "")
		{
			Interpreter* interpreter = new Interpreter(input);
			unsigned long int result = interpreter->Expression();

			std::cout << result << std::endl;
		}

	}
	return 0;
}

