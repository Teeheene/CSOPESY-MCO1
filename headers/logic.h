/*
 * tokenizes the input
 *
 * @param input - the string input of the user 
 * @returns vector<string> - dynamic array of tokens 
 * */
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

/*
 * Debugging tokens
 * */
void printTokens(std::vector<std::string> tokens) {
	std::cout << std::endl << "Testing tokens: " << std::endl; 
	for(auto i = 0u; i < tokens.size(); i++) {
		std::cout << tokens[i] << std::endl;
	}
	std::cout << std::endl;
}

