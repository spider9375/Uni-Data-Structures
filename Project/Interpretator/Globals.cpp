#include "stdafx.h"
#include "Globals.h"

std::string INTEGER = "INTEGER";
std::string MOD = "MOD";
std::string PLUS = "PLUS";
std::string MINUS = "MINUS";
std::string MUL = "MUL";
std::string DIV = "DIV";
std::string EoF = "EOF";
std::string LPAREN = "LPAREN";
std::string RPAREN = "RPAREN";
std::string ID = "ID";
std::string ASSIGN = "ASSIGN";
std::string PRINT = "PRINT";
std::string READ = "READ";
std::map<std::string, unsigned long int> VAR_TABLE;
std::map<std::string, Token> KEYWORDS = { 
	{"print", Token("PRINT","print")},
	{"read", Token("READ", "read")},
	{ "+", Token("PLUS", "+") },
	{ "-", Token("MINUS", "-") },
	{ "*", Token("MUL", "*") },
	{ "/", Token("DIV", "/") },
	{ "%", Token("MOD", "%") },
	{ "EOF", Token("EOF", "EOF") },
	{ "(", Token("LPAREN", "(") },
	{ ")", Token("RPAREN", ")") },
	{ "=", Token("ASSIGN", "=") }
};
std::vector<char> OPERATORS = { '+', '-', '/', '*', '%' };
char NULL_CHAR = '\0';
