#pragma once
#include "AST.h"
#include "Var.h"
class Function : public AST 
{
public:
	std::string name;
	AST* parameter;
	AST* body;
	Function(std::string _name, AST* _parameter, AST* _body);
	~Function();
};

