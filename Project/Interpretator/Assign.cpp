#include "stdafx.h"
#include "Assign.h"


Assign::Assign(Var* _left, Token* _op, AST* _right)
{
	this->left = _left;
	this->op = _op;
	this->right = _right;
}


Assign::~Assign()
{
}
