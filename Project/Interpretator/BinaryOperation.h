#pragma once
#include "Token.h"
#include "Number.h"
class BinaryOperation : public AST
{
public:
	AST* left;
	Token* op;
	AST* right;
	BinaryOperation(AST* _left, Token* _op, AST* _right);
	BinaryOperation();
	~BinaryOperation();
};

