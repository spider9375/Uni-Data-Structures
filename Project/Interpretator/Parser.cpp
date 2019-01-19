#include "stdafx.h"
#include "Parser.h"

Parser::Parser(Lexer* _lexer)
{
	this->lexer = _lexer;
	this->currentToken = this->lexer->GetNextToken();
}


Parser::~Parser()
{
}

void Parser::Error()
{
	throw std::exception("Invalid syntax");
}

void Parser::Eat(std::string tokenType)
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

AST* Parser::Factor()
{
	Token* token = this->currentToken;

	if (token->type == INTEGER)
	{
		this->Eat(INTEGER);
		return new Number(token);
	}
	else if (token->type == LPAREN)
	{
		this->Eat(LPAREN);
		AST* node = this->Expression();
		this->Eat(RPAREN);
		return node;
	}
}

AST* Parser::Term()
{
	AST* node = this->Factor();

	while (this->currentToken->type == MUL || this->currentToken->type == DIV)
	{
		Token* token = this->currentToken;

		if (token->type == MUL)
		{
			this->Eat(MUL);
		}
		else if (token->type == DIV)
		{
			this->Eat(DIV);
		}

		node = new BinaryOperation(node, token, this->Factor());
	}

	return node;
}

AST* Parser::Expression()
{
	AST* node = this->Term();

	while (this->currentToken->type == PLUS || this->currentToken->type == MINUS)
	{
		Token* token = this->currentToken;
		if (token->type == PLUS)
		{
			this->Eat(PLUS);
		}
		else if (token->type == MINUS)
		{
			this->Eat(MINUS);
		}

		node = new BinaryOperation(node, token, this->Term());
	}

	return node;
}

AST* Parser::Parse()
{
	return this->Expression();
}
