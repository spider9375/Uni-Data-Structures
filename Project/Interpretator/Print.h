#pragma once
#include "AST.h"
#include "Var.h"
class Print : public AST
{
public:
	AST* node;
	Print(AST* _node);
	~Print();
};

