#include "stdafx.h"
#include "Interpreter.h"
#include <typeinfo>

Interpreter::Interpreter(Parser* _parser)
{
	this->parser = _parser;
}


Interpreter::~Interpreter()
{
}

unsigned long int Interpreter::VisitNumber(Number* node)
{
	return node->value;
}

unsigned long int Interpreter::visit(AST* node)
{
	Number* number = dynamic_cast<Number*>(node);
	BinaryOperation* binOp = dynamic_cast<BinaryOperation*>(node);
	Assign* assign = dynamic_cast<Assign*>(node);
	if (number)
	{
		return this->VisitNumber((Number*)node);
	}
	else if (binOp)
	{
		return this->VisitBinOp((BinaryOperation*)node);
	}
	else if (assign)
	{
		 this->visitAssign((Assign*)node);
	}
	else
	{
		return this->visitVar((Var*)node);
	}
}

unsigned long int Interpreter::visitVar(Var* node)
{
	if (VAR_TABLE.count(node->name) < 0)
	{
		throw std::exception("No variable exists");
	}
		
	return VAR_TABLE[node->name];
}

unsigned long int Interpreter::VisitBinOp(BinaryOperation* node)
{
	if (node->op->type == PLUS)
	{
		return this->visit(node->left) + this->visit(node->right);
	}

	else if (node->op->type == MINUS)
	{
		return this->visit(node->left) - this->visit(node->right);
	}

	else if (node->op->type == MUL)
	{
		return this->visit(node->left) * this->visit(node->right);
	}

	else if(node->op->type == DIV)
	{
		return this->visit(node->left) / this->visit(node->right);
	}

	else
	{
		return this->visit(node->left) % this->visit(node->right);
	}
}

void Interpreter::visitAssign(Assign* node)
{
	std::string varName = node->left->name;
	Var* variable = dynamic_cast<Var*>(node->right);
	if (variable)
	{
		VAR_TABLE[varName] = VAR_TABLE[variable->name];
	}
	else
	{
		VAR_TABLE[varName] = this->visit(node->right);
	}
}

void Interpreter::visitPrint(Print* node)
{
	unsigned long int result = VAR_TABLE[node->variable->name];

	if (result >= 0)
	{
		std::cout << result << std::endl;
	}
}

void Interpreter::Interpret()
{
	AST* node = this->parser->Parse();
	Assign* assign = dynamic_cast<Assign*>(node);
	Print* print = dynamic_cast<Print*>(node);
	if (assign)
	{
		this->visitAssign((Assign*)node);
	}
	else if (print)
	{
		this->visitPrint((Print*)node);
	}
}