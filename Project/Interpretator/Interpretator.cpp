// Interpretator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <locale>
#include "Interpreter.h"


int _tmain(int argc, _TCHAR* argv[])
{
	std::string input;
	while (std::getline(std::cin, input))
	{
		if (input != "")
		{
			Lexer* lexer = new Lexer(input);
			Interpreter* interpreter = new Interpreter(lexer);
			unsigned long int result = interpreter->Expression();

			std::cout << result << std::endl;
		}

	}
	return 0;
}

