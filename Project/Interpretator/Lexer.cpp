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

char Lexer::Peek()
{
	int peekPos = this->pos + 1;
	if (peekPos > this->text.size() - 1)
	{
		return NULL_CHAR;
	}
	
	return this->text[peekPos];
}

Token* Lexer::Func()
{
	while (this->currentChar != ']')
	{
		if (this->currentChar == NULL_CHAR)
		{
			throw std::exception("Bad syntax");
		}
		else
		{
			this->Advance();
		}
	}

	this->Advance();

	return new Token(KEYWORDS[FUNC]);
}

Token* Lexer::Id()
{
	std::string result = "";
	while (this->currentChar != NULL_CHAR && isalnum(this->currentChar))
	{
		result += this->currentChar;
		this->Advance();
	}

	if (this->currentChar == '[')
	{
		return this->Func();
	}

	if (KEYWORDS.count(result) > 0)
	{
		return new Token(KEYWORDS[result]);
	}

	return new Token(ID, result);
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

	unsigned long int value;
	try 
	{
		value = std::stoul(result);
	}
	catch (std::exception ex)
	{
		throw std::exception("Number is out of range");
	}

	return value;
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

		if (isalpha(this->currentChar))
		{
			return this->Id();
		}

		if (isdigit(this->currentChar))
		{
			return new Token(INTEGER, std::to_string(this->Integer()));
		}

		if (KEYWORDS.count(std::string(1,this->currentChar)) > 0)
		{
			char currentChar = this->currentChar;
			this->Advance();
			Token* token = new Token(KEYWORDS[std::string(1, currentChar)]);

			return token;
		}

		this->Error();
	}

	return new Token(EoF, EoF);
}
