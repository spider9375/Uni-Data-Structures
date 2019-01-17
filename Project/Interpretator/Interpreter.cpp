#include "stdafx.h"
#include "Interpreter.h"


Interpreter::Interpreter(Lexer* _lexer)
{
	this->lexer = _lexer;
	this->currentToken = this->lexer->GetNextToken();
}


Interpreter::~Interpreter()
{
}

void Interpreter::Error()
{
	this->lexer->Error();
}
void Interpreter::Eat(std::string tokenType)
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
unsigned long int Interpreter::Factor()
{
	Token* token = this->currentToken;
	if (token->type == INTEGER)
	{
		this->Eat(INTEGER);
		return std::stoi(token->value);
	}
	else if (token->type == LPAREN)
	{
		this->Eat(LPAREN);
		unsigned long int result = this->Expression();
		this->Eat(RPAREN);
		return result;
	}
}
unsigned long int Interpreter::Term()
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

unsigned long int Interpreter::Expression()
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
