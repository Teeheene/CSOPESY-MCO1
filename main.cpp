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
	//9x8 width x height modified ascii to be monospace. 
	//Retrieved from https://patorjk.com/software/taag/ with Epic font
	std::string letter[36][8]= {
		{
			"         ",
			"         ",
			"         ",
			"         ",
			"         ",
			"         ",
			"         ",
			"         "
		},
		{
			" _______ ",
			"(  __   )",
			"| (  )  |",
			"| | /   |",
			"| (/ /) |",
			"|   / | |",
			"|  (__) |",
			"(_______)"
         	
		},
		{
			"  __     ",
			" /  \\    ",
			" \\/) )   ",
			"   | |   ",
			"   | |   ",
			"   | |   ",
			" __) (_  ",
			" \\____/  "
		},
		{
			" _______ ",
			"/ ___   )",
			"\\/   )  |",
			"    /   )",
			"  _/   / ",
			" /   _/  ",
			"(   (__/\\",
			"\\_______/",
         
		},
		{
			" ______  ",
			"/ ___  \\ ",
			"\\/   \\  \\",
			"   ___) /",
			"  (___ ( ",
			"     ) \\ ",
			"/\\___/  /",
			"\\______/ "
		},
		{
			"    ___  ",
			"   /   ) ", 
			"  / /) | ",
			" / (_) ( ",
			"(___    )",
			"    ) (  ",
			"    | |  ",
			"    (_)  ",
		},
		{
			" _______ ",
			"(  ____ \\",
			"| (    \\/",
			"| (____  ",
			"(_____ \\ ",
			"      ) )",
			"/\\____) )",
			"\\______/ "
		},
		{
			"  ______ ",
			" / ____ \\",
			"( (    \\/",
			"| (____  ",
			"|  ___ \\ ",
			"| (   ) )",
			"( (___) )",
			" \\_____/ "
		},
		{
			" ______  ",
			"/ ___  \\ ",
			"\\/   )  )",
			"    /  / ",
			"   /  /  ",
			"  /  /   ",
			" /  /    ",
			" \\_/     "
		},
		{
			"  _____  ",
			" / ___ \\ ",
			"( (___) )",
			" \\     / ",
			" / ___ \\ ",
			"( (   ) )",
			"( (___) )",
			" \\_____/ "
		},
		{
			"  _____  ",
			" / ___ \\ ",
			"( (   ) )",
			"( (___) |",
			" \\____  |",
			"      ) |",
			"/\\____) )",
			"\\______/ "
		},
		{
			" ______  ",
			"(  ___  )",
			"| (   ) |",
			"| (___) |",
			"|  ___  |",
			"| (   ) |",
			"| )   ( |",
			"|/     \\|"
		},
		{
			" ______  ",
			"(  ___ \\ ",
			"| (   ) )",
			"| (__/ / ",
			"|  __ (  ",
			"| (  \\ \\ ",
			"| )___) )",
			"|/ \\___/ "
		},
		{
			" _______ ",
			"(  ____ \\",
			"| (    \\/",
			"| |      ",
			"| |      ",
			"| |      ",
			"| (____/\\",
			"(_______/"
		},
		{
			" ______  ",
			"(  __  \\ ",
			"| (  \\  )",
			"| |   ) |",
			"| |   | |",
			"| |   ) |",
			"| (__/  )",
			"(______/ "
		}
		
	};
	//accept input for CLI window size? 
	//(ex. type "aaaaaaaaaaaa" until line break to determine ascii art maximum size)
	//idk about animation yet
	
	bool running = true;

	fetchDisplay();
	while(running) {
		std::vector<std::string> tokens = tokenizeInput( getInput() );
		
		if(tokens[0] == "neofetch") {
			printLetters(letter, "dab");
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

	std::cout << "Allowed characters: A-Z (automatically converted to uppercase), 0-9, spacebar" << std::endl;
	printLetters(letter,"01234 abcd 56789");

	return 0;
}

