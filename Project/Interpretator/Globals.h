#pragma once
#include <string>
#include <map>
#include <vector>
#include "Token.h"
#include "Function.h"
#include "AST.h"
extern std::string INTEGER;
extern std::string PLUS;
extern std::string MINUS;
extern std::string MUL;
extern std::string DIV;
extern std::string MOD;
extern std::string EoF;
extern std::string LPAREN;
extern std::string RPAREN;
extern std::string ID;
extern std::string PRINT;
extern std::string READ;
extern std::string FUNC;
extern std::string LBRACKET;
extern std::string RBRACKET;
extern std::string::size_type sz;
extern std::map<std::string, Token> KEYWORDS;
extern std::map<std::string, unsigned long int> VAR_TABLE;
extern std::map<std::string, Function*> FUNC_TABLE;
extern std::vector<char> OPERATORS;
extern std::string ASSIGN;
extern char NULL_CHAR;