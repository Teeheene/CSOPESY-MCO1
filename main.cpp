#include <iostream>
#include <thread> //future use
						//ah
#include <vector>
#include <string>
#include <cctype>

void fetchDisplay();
void fetchHelpDisplay();
void printTokens(std::vector<std::string>);
std::vector<std::string> tokenizeInput(std::string);
std::string getInput();

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


