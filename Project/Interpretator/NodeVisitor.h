#pragma once
#include "AST.h"
class NodeVisitor
{
public:
	virtual unsigned long int visit(AST* node) = 0;
};

