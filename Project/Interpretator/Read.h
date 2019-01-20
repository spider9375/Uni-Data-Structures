#pragma once
#include "AST.h"
#include "Var.h"
class Read : public AST
{
public:
	Var* variable;
	Read(Var* _variable);
	~Read();
};

