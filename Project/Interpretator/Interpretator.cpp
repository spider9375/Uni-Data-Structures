// Interpretator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
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
	/*std::ifstream file("Read.txt");
	
	while (std::getline(file, input))
	{
		if (input != "")
		{
			Lexer a = Lexer(input);
			Parser b = Parser(&a);
			Interpreter c = Interpreter(&b);
			try 
			{
				c.Interpret();
			}
			catch (std::exception ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
	}*/

	while (std::getline(std::cin, input))
	{
		if (input != "")
		{
			Lexer a = Lexer(input);
			Parser b = Parser(&a);
			Interpreter c = Interpreter(&b);

			try 
			{
				c.Interpret();
			}
			catch (std::exception ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}

	}
	return 0;
}

