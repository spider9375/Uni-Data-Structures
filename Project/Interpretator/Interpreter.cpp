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

unsigned long int Interpreter::visitFunc(Function* node)
{
	Number* number = dynamic_cast<Number*>(node->parameter);
	Var* var = dynamic_cast<Var*>(node->parameter);

	if (number)
	{
		return this->VisitNumber(number);
	}
}

unsigned long int Interpreter::visit(AST* node)
{
	Number* number = dynamic_cast<Number*>(node);
	BinaryOperation* binOp = dynamic_cast<BinaryOperation*>(node);
	Assign* assign = dynamic_cast<Assign*>(node);
	Function* func = dynamic_cast<Function*>(node);
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
	else if (func)
	{
		return this->visit(func->body);
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

void Interpreter::visitRead(Read* node)
{
	unsigned long int value;
	std::cin >> value;

	VAR_TABLE[node->variable->name] = value;
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
	Var* variable = dynamic_cast<Var*>(node->node);
	Function* func = dynamic_cast<Function*>(node->node);
	Number* number = dynamic_cast<Number*>(node->node);

	unsigned long int result;

	if (variable)
	{
		if (VAR_TABLE.count(variable->name) == 0)
		{
			throw std::exception("no variable");
		}

		result = VAR_TABLE[variable->name];
	}
	else if (func)
	{
		if (FUNC_TABLE.count(func->name) == 0)
		{
			throw std::exception("Function does not exist");
		}

		result = this->visit(FUNC_TABLE[func->name]);
	}
	else if (number)
	{
		result = this->VisitNumber(number);
	}
	
	if (result >= 0)
	{
		std::cout << result << std::endl;
	}

	delete[] node;
	delete[] variable;
	delete[] number;
	delete[] func;
}

void Interpreter::saveFunc(Function* node)
{
	FUNC_TABLE[node->name] = node;
}

void Interpreter::Interpret()
{
	AST* node = this->parser->Parse();
	Assign* assign = dynamic_cast<Assign*>(node);
	Print* print = dynamic_cast<Print*>(node);
	Read* read = dynamic_cast<Read*>(node);
	Function* func = dynamic_cast<Function*>(node);
	if (assign)
	{
		this->visitAssign((Assign*)node);
	}
	else if (print)
	{
		this->visitPrint((Print*)node);
	}
	else if (read)
	{
		this->visitRead((Read*)node);
	}
	else if (func)
	{
		this->saveFunc((Function*)node);
	}
}