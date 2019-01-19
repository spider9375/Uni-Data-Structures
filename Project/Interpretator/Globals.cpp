#include "stdafx.h"
#include "Globals.h"

std::string INTEGER = "INTEGER";
std::string PLUS = "PLUS";
std::string MINUS = "MINUS";
std::string MUL = "MUL";
std::string DIV = "DIV";
std::string EoF = "EOF";
std::string LPAREN = "(";
std::string RPAREN = ")";
std::string ID = "ID";
std::string ASSIGN = "ASSIGN";
std::string PRINT = "PRINT";
std::string READ = "READ";
std::map<std::string, unsigned long int> VAR_TABLE;
std::map<std::string, Token*> KEYWORDS = { {"print", new Token("PRINT","print")}, {"read", new Token("READ", "read")} };
char NULL_CHAR = '\0';
