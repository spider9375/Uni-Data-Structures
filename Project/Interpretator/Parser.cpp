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
	else
	{
		AST* node = this->Variable();
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

AST* Parser::AssignStatement()
{
	Var* left = this->Variable();
	Token* token = this->currentToken;
	this->Eat(ASSIGN);
	AST* right = this->Expression();

	AST* node = new Assign(left, token, right);

	return node;
}

Var* Parser::Variable()
{
	Var* node = new Var(this->currentToken);
	this->Eat(ID);
	return node;
}

AST* Parser::Parse()
{
	AST* node = this->Statement();

	return node;
}

AST* Parser::PrintStatement()
{
	this->Eat(PRINT);
	Var* variable = this->Variable();

	return new Print(variable);
}

AST* Parser::Statement()
{
	AST* node;
	if (this->currentToken->type == ID)
	{
		node = this->AssignStatement();
	}
	else if (this->currentToken->type == PRINT)
	{
		node = this->PrintStatement();
	}
	else 
	{
		node = this->Empty();
	}

	return node;
}

AST* Parser::Empty()
{
	return new NoOp();
}
