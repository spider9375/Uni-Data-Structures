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

	while (this->currentToken->type == MUL || this->currentToken->type == DIV || this->currentToken->type == MOD)
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
		else if (token->type == MOD)
		{
			this->Eat(MOD);
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
	AST* right;
	if (this->currentToken->type == ID)
	{
		if (std::find(OPERATORS.begin(), OPERATORS.end(), this->lexer->Peek()) != OPERATORS.end())
		{
			right = this->Expression();
		}
		else
		{
			right = this->Variable();
		}
	}
	else {

		right = this->Expression();
	}

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

std::string Parser::GetFuncNameForPrint()
{
	int LBRACKET_POS = this->lexer->text.find('[');
	int RBRACKET_POS = this->lexer->text.find(']');
	std::string print = "print";
	int PRINT_POS = this->lexer->text.find(print);
	int PRINT_END_POS = PRINT_POS + 5;
	std::string funcName = this->lexer->text.substr(PRINT_END_POS, LBRACKET_POS - PRINT_END_POS);
	funcName.erase(std::remove(funcName.begin(), funcName.end(), ' '), funcName.end());

	return funcName;
}

AST* Parser::GetFuncPrintVariable()
{
	int LBRACKET_POS = this->lexer->text.find('[');
	int RBRACKET_POS = this->lexer->text.find(']');
	std::string varName = this->lexer->text.substr(LBRACKET_POS + 1, RBRACKET_POS - LBRACKET_POS - 1);
	varName.erase(std::remove(varName.begin(), varName.end(), ' '), varName.end());
	unsigned long int number = std::stoul(varName);

	if (number)
	{
		return new Number(new Token(INTEGER, varName));
	}

	return new Var(new Token(ID, varName));
}

AST* Parser::PrintStatement()
{
	this->Eat(PRINT);
	AST* statement;

	if (this->currentToken->type == FUNC)
	{
		AST* var = this->GetFuncPrintVariable();
		std::string funcName = this->GetFuncNameForPrint();
		Function* func = FUNC_TABLE[funcName];
		//VAR_TABLE[func->parameter];
		statement = new Function(this->GetFuncNameForPrint(), var, nullptr);

	}
	else if (this->currentToken->type == ID)
	{
		statement = this->Variable();
	}
	else //if (this->currentToken->type == INTEGER)
	{
		statement = this->Expression();
	}

	return new Print(statement);
}

AST* Parser::ReadStatement()
{
	this->Eat(READ);
	Var* variable = this->Variable();

	return new Read(variable);
}

AST* Parser::FuncStatement()
{
	int LBRACKET_POS = this->lexer->text.find('[');
	int RBRACKET_POS = this->lexer->text.find(']');
	std::string funcName = this->lexer->text.substr(0, LBRACKET_POS);
	funcName.erase(std::remove(funcName.begin(), funcName.end(), ' '), funcName.end());
	std::string varName = this->lexer->text.substr(LBRACKET_POS + 1, RBRACKET_POS - LBRACKET_POS - 1);
	Token* token = new Token(ID, varName);
	Var* variable = new Var(token);
	this->Eat(FUNC);
	this->Eat(ASSIGN);
	AST* funcBody = this->Expression();
	Function* result = new Function(funcName, variable, funcBody);
	return result;
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
	else if (this->currentToken->type == READ)
	{
		node = this->ReadStatement();
	}
	else if (this->currentToken->type == FUNC)
	{
		node = this->FuncStatement();
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
