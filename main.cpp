#include <iostream>
#include <thread> //future use
#include <vector>
#include <string>
#include <cctype>

void fetchDisplay();
void fetchHelpDisplay();
void printTokens(std::vector<std::string>);
std::vector<std::string> tokenizeInput(std::string);
std::string getInput();

void printLetter(std::string letter[36][8], char c){
	int val = int(c);
	val = val-97;
	for(int i=0; i<8; i++) {
		std::cout << letter[val][i] << std::endl;
	}
}

void printLetters(std::string letter[36][8], std::string s){
	int vals[s.length()];
	std::string word[8];
	
	//char		ascii		index
	//SPACE		32			0
	//0-9		48-57		1-10
	//A-Z		65-90		11-36
	//a-z		97-122		11-36
	
	for(int i=0; i<s.length(); i++) {
		if(s[i] == 32) {
			vals[i] = s[i] - 32;
		}
		if(s[i] >= 48 && s[i] <= 57) {
			vals[i] = s[i] - 48 + 1;
		}
		if(s[i] >= 65 && s[i] <= 90) {
			vals[i] = s[i] - 65 + 1 + 10;
		}
		if(s[i] >= 97 && s[i] <= 122) {
			vals[i] = s[i] - 97 + 1 + 10;
		}
	}
	
	for(int i=0; i<8; i++) {
		for(int j=0; j<s.length(); j++) {
			word[i].append(letter[vals[j]][i]);
			word[i].append(" ");
		}
	}
	
	for(int i=0; i<8; i++) {
		std::cout << word[i] << std::endl;
	}
}


int main() 
{
	bool running = true;

	fetchDisplay();
	while(running) {
		std::vector<std::string> tokens = tokenizeInput( getInput() );

		if(tokens[0] == "help") {
			fetchHelpDisplay();
		}
		if(tokens[0] == "exit") {
			std::cout << "Terminating interpreter..." << std::endl;
			running = false;
		}
	}

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
	
	std::cout << "Allowed characters: A-Z (automatically converted to uppercase), 0-9, spacebar" << std::endl;
	printLetters(letter,"01234 abcd 56789");

	return 0;
}

void fetchDisplay() {
	std::cout << "Welcome to CSOPESY!" << std::endl << std::endl 
		<< "Group developer:" << std::endl
		<< "Diane Panganiban" << std::endl
		<< "Gian Carlos" << std::endl
		<< "Kenzo De Vera" << std::endl
		<< "Yesha Joes" << std::endl << std::endl
		<< "Version date:" << std::endl << std::endl;
}

void fetchHelpDisplay() {
	std::cout << "List of commands the user can use:" << std::endl
		<< "\"help\" - displays the commands and its description" << std::endl
		<< "\"start_marquee\" - starts the marquee \"animation\"" << std::endl 
		<< "\"stop_marquee\" - stops the marquee \"animation\"" << std::endl
		<< "\"set_text\" - accepts a text input and displays it as a marquee" << std::endl
		<< "\"set speed\" - sets the marquee animation refresh in milliseconds" << std::endl
		<< "\"exit\" - terminates the console" << std::endl << std::endl;
}

std::vector<std::string> tokenizeInput(std::string input) {
	std::vector<std::string> tokens;
	std::string token{ "" };
	
	if(input.empty())
		return {}; 

	for(char ch : input) {
		//if its not a space
		if(!std::isspace(static_cast<unsigned char>(ch))) {
			token += ch;
		} else {
			tokens.push_back(token);
			token = "";
		}
	}
	tokens.push_back(token);

	return tokens;
}

//debugging
void printTokens(std::vector<std::string> tokens) {
	std::cout << std::endl << "Testing tokens: " << std::endl; 
	for(int i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i] << std::endl;
	}
	std::cout << std::endl;
}

std::string getInput() {
	std::cout << "Command> ";

	std::string text;
	std::getline(std::cin, text);
	return text;
}


