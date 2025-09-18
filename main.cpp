#include <iostream>
#include <thread> 
#include <vector>
#include <string>
#include <cctype>
#include "ascii.h"
#include "display.h"
#include "logic.h"

bool isRunning = true;

void keyboardHandler() {
	while(isRunning) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

void marqueeLogic(int display_width) {
	while(isRunning) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

void displayHandler() {
	const int refreshRate = 50;
	while(isRunning) {
		std::this_thread::sleep_for(std::chrono::milliseconds(refreshRate));
	}
}

int main() 
{
	std::thread keyboard_handler_thread(keyboardHandler);
	std::thread marquee_logic_thread(marqueeLogic,50);
	std::thread display_handler_thread(displayHandler);
		
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

