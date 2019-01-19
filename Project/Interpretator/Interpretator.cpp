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
	std::string input;
	while (std::getline(std::cin, input))
	{
		if (input != "")
		{
			Lexer* lexer = new Lexer(input);
			Parser* parser = new Parser(lexer);
			Interpreter* interpreter = new Interpreter(parser);
			unsigned long int result = interpreter->Interpret();

			std::cout << result << std::endl;
		}

	}
	return 0;
}

