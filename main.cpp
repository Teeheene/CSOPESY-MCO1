#include <iostream>
#include <thread> //future use
#include <vector>
#include <string>
#include <cctype>
#include "ascii.h"
#include "display.h"
#include "logic.h"

int main() 
{

	bool running = true;

	fetchDisplay();
	while(running) {
		std::vector<std::string> tokens = tokenizeInput( getInput() );
		
		if(tokens[0] == "neofetch") {
			printLetters("dab");
			fetchDisplay();
		}
		if(tokens[0] == "help") {
			fetchHelpDisplay();
		}
		if(tokens[0] == "exit") {
			std::cout << "Terminating interpreter..." << std::endl;
			running = false;
		}
	}

	/*
	std::cout << "Allowed characters: A-Z (automatically converted to uppercase), 0-9, spacebar" << std::endl;
	printLetters("01234 abcd 56789");
	*/

	return 0;
}

