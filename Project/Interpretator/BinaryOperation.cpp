#include "stdafx.h"
#include "BinaryOperation.h"


BinaryOperation::BinaryOperation(AST* _left, Token* _op, AST* _right)
{
	this->left = _left;
	this->op = _op;
	this->right = _right;
}

BinaryOperation::BinaryOperation()
{
}

BinaryOperation::~BinaryOperation()
{
}
