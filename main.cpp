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
		std::string command = tokens[0];
		
		if(command == "neofetch") {
			printLetters("opesy");
			fetchDisplay();
		}
		else if(command == "help") {
			printLetters("help");
			fetchHelpDisplay();
		}
		else if(command == "exit") {
			std::cout << "Terminating interpreter..." << std::endl;
			running = false;
		}
	}

	return 0;
}

