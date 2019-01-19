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
	
	if (number)
	{
		return this->VisitNumber((Number*)node);
	}

	return this->VisitBinOp((BinaryOperation*)node);
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

	else //(node->op->type == DIV)
	{
		return this->visit(node->left) / this->visit(node->right);
	}
}

unsigned long int Interpreter::Interpret()
{
	AST* tree = this->parser->Parse();
	return this->visit(tree);
}