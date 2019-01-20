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
std::string LBRACKET = "LBRACKET";
std::string RBRACKET = "RBRACKET";
std::string FUNC = "FUNC";
std::map<std::string, unsigned long int> VAR_TABLE;
std::map<std::string, Token> KEYWORDS = { 
	{"print", Token(PRINT,"print")},
	{"read", Token(READ, "read")},
	{ "+", Token(PLUS, "+") },
	{ "-", Token(MINUS, "-") },
	{ "*", Token(MUL, "*") },
	{ "/", Token(DIV, "/") },
	{ "%", Token(MOD, "%") },
	{ "EOF", Token(EoF, "EOF") },
	{ "(", Token(LPAREN, "(") },
	{ ")", Token(RPAREN, ")") },
	{ "=", Token(ASSIGN, "=") },
	{ "FUNC", Token(FUNC, FUNC) },
	{ "[", Token(LBRACKET, "[") },
	{ "]", Token(RBRACKET, "]") }
};
std::map<std::string, Function*> FUNC_TABLE;
std::vector<char> OPERATORS = { '+', '-', '/', '*', '%' };
char NULL_CHAR = '\0';
