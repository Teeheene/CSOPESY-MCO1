std::string getInput() {
	std::cout << "Command> ";

	std::string text;
	std::getline(std::cin, text);
	return text;
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

