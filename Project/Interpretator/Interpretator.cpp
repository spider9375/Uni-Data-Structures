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
std::string MUL = "MUL";
std::string DIV = "DIV";
std::string EoF = "EOF";
char NULL_CHAR = '\0';
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

struct Lexer
{
	std::string text;
	int pos;
	char currentChar;

	Lexer(std::string _text)
	{
		this->text = _text;
		this->pos = 0;
		this->currentChar = this->text[this->pos];
	}

	void Error()
	{
		throw std::exception("Invalid character");
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

	unsigned long int Integer()
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

			if (this->currentChar == '*')
			{
				this->Advance();
				return new Token(MUL, "*");
			}

			if (this->currentChar == '/');
			{
				this->Advance();
				return new Token(DIV, "/");
			}

			this->Error();
		}

		return new Token(EoF, EoF);
	}
};

struct Interpreter
{
	Lexer* lexer;
	Token* currentToken = nullptr;

	Interpreter(Lexer* _lexer)
	{
		this->lexer = _lexer;
		this->currentToken = this->lexer->GetNextToken();
	}

	void Error()
	{
		throw std::exception("Invalid character");
	}

	void Eat(std::string tokenType)
	{
		if (this->currentToken->type == tokenType)
		{
			this->currentToken = this->lexer->GetNextToken();
		}
		else
		{
			this->Error();
		}
	}

	unsigned long int Factor()
	{
		Token* token = this->currentToken;
		this->Eat(INTEGER);
		return std::stoi(token->value);
	}

	unsigned long int Term()
	{
		unsigned int result = this->Factor();

		while (this->currentToken->type == MUL || this->currentToken->type == DIV)
		{
			Token* token = this->currentToken;
			if (token->type == MUL)
			{
				this->Eat(MUL);
				result = result * this->Factor();
			}
			else if (token->type == DIV)
			{
				this->Eat(DIV);
				result = result / this->Factor();
			}
		}

		return result;
	}

	unsigned long int Expression()
	{

		unsigned long int result = this->Term();
		while (this->currentToken->type == PLUS || this->currentToken->type == MINUS)
		{
			Token* token = this->currentToken;
			if (token->type == PLUS)
			{
				this->Eat(PLUS);
				result = result + this->Term();
			}
			else if (token->type == MINUS)
			{
				this->Eat(MINUS);
				result = result - this->Term();
			}
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
			Lexer* lexer = new Lexer(input);
			Interpreter* interpreter = new Interpreter(lexer);
			unsigned long int result = interpreter->Expression();

			std::cout << result << std::endl;
		}

	}
	return 0;
}

