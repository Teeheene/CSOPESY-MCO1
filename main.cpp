#include <iostream>
#include <thread> 
#include <vector>
#include <string>
#include <cctype>
#include "ascii.h"
#include "display.h"
#include "logic.h"

int main() 
{
	/*
	Template for threads
	
	std::thread marquee_logic_thread();
	std::thread display_handler_thread();
	std::thread keyboard_handler_thread();
	*/
		
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

