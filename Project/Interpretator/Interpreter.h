#pragma once
#include <iostream>
#include "Parser.h"

class Interpreter
{
	Token* currentToken = nullptr;
public:
	Parser* parser;
	Interpreter(Parser* _parser);
	~Interpreter();
	unsigned long int visit(AST* node);
	unsigned long int VisitNumber(Number* node);
	unsigned long int VisitBinOp(BinaryOperation* node);
	unsigned long int visitVar(Var* node);
	void visitAssign(Assign* node);
	void visitPrint(Print* node);
	void visitRead(Read* node);
	void saveFunc(Function* node);
	void Interpret();
};

