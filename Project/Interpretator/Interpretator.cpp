// Interpretator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <locale>
#include "Interpreter.h"
#include "Parser.h"


int _tmain(int argc, _TCHAR* argv[])
{
	std::string input = "";
	
	while (std::getline(std::cin, input))
	{
		if (input != "")
		{
			Lexer a = Lexer(input);
			Parser b = Parser(&a);
			Interpreter c = Interpreter(&b);
			c.Interpret();
		}

	}
	return 0;
}

