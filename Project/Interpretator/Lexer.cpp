#include "stdafx.h"
#include "Lexer.h"


Lexer::Lexer(std::string _text)
{
	this->text = _text;
	this->pos = 0;
	this->currentChar = this->text[this->pos];
}


Lexer::~Lexer()
{
}

void Lexer::Error()
{
	throw std::exception("Invalid character");
}

void Lexer::Advance()
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

void Lexer::skipWhitespace()
{
	while (this->currentChar != NULL_CHAR &&  this->currentChar == ' ')
	{
		this->Advance();
	}
}

unsigned long int Lexer::Integer()
{
	std::string result = "";
	while (this->currentChar != NULL_CHAR && isdigit(this->currentChar))
	{
		result += this->currentChar;
		this->Advance();
	}

	return std::stoi(result);
}

Token* Lexer::GetNextToken()
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

		if (this->currentChar == '/')
		{
			this->Advance();
			return new Token(DIV, "/");
		}

		if (this->currentChar == '(')
		{
			this->Advance();
			return new Token(LPAREN, "(");
		}

		if (this->currentChar == ')')
		{
			this->Advance();
			return new Token(RPAREN, ")");
		}

		this->Error();
	}

	return new Token(EoF, EoF);
}
