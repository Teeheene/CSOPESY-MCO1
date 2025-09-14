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


