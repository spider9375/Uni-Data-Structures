#include "stdafx.h"
#include "Function.h"


Function::Function(std::string _name, AST* _parameter, AST* _body)
{
	this->name = _name;
	this->parameter = _parameter;
	this->body = _body;
}


Function::~Function()
{
}
