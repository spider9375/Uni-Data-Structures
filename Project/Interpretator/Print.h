#pragma once
#include "AST.h"
#include "Var.h"
class Print : public AST
{
public:
	Var* variable;
	Print(Var* _variable);
	~Print();
};

