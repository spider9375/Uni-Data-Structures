#pragma once
#include "Parser.h"
//#include "NodeVisitor.h"

class Interpreter
{
	Parser* parser;
	Token* currentToken = nullptr;
	Number* returnNumber(AST* node);
	BinaryOperation* returnBinOp(AST* node);
public:
	Interpreter(Parser* _parser);
	~Interpreter();
	unsigned long int visit(AST* node);
	unsigned long int VisitNumber(Number* node);
	unsigned long int VisitBinOp(BinaryOperation* node);
	unsigned long int Interpret();
	//unsigned long int visit(Number* node) override;
	//unsigned long int visit(BinaryOperation* node) override;
};

