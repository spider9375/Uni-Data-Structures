#pragma once
#include "AST.h"
#include "Var.h"
class Assign : public AST
{
public:
	Var* left;
	Token* op;
	AST* right;
	Assign(Var* _left, Token* _op, AST* _right);
	~Assign();
};

