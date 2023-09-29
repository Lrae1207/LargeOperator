#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ios>
#include <bitset>

char	*buffer = (char*)malloc(1);
size_t	bufferSize = 0;

void strop(std::vector<std::string> args) {

}

/*
	Return a number written in string format converted to a long long
*/
int parseValue(std::string str) {
	// TODO: add try catch to avoid crashing on invalid syntax/order
	if (str[0] == '0' && str[1] == 'x') {
		return std::stoll(str, 0, 16);
	}

	// Assume it's decimal
	return std::stoll(str);
}

// Perform a number logical operation
void numop(std::vector<std::string> args) {
	if (args.size() == 4) {
		long long op1 = parseValue(args[2]);
		long long op2 = parseValue(args[3]);
		
		if (args[1] == "and" || args[1] == "&") {
			std::cout << "0d" << std::dec << (op1 & op2) << "\n";
			std::cout << "0x" << std::hex << (op1 & op2) << "\n";
			std::cout << "0b" << std::bitset<64>(op1 & op2).to_string() << "\n";
		} else if (args[1] == "or" || args[1] == "|") {
			std::cout << "0d" << std::dec << (op1 | op2) << "\n";
			std::cout << "0x" << std::hex << (op1 | op2) << "\n";
			std::cout << "0b" << std::bitset<64>(op1 | op2).to_string() << "\n";
		} else if (args[1] == "xor" || args[1] == "^") {
			std::cout << "0d" << std::dec << (op1 ^ op2) << "\n";
			std::cout << "0x" << std::hex << (op1 ^ op2) << "\n";
			std::cout << "0b" << std::bitset<64>(op1 ^ op2).to_string() << "\n";
		} else {
			std::cout << "Invalid parameters.\n";
		}
	} else if (args.size() == 3) {
		if (args[1] == "not" || args[1] == "~" || args[1] == "!") {
			long long op1 = parseValue(args[2]);

			std::cout << "0d" << std::dec << (~op1) << "\n";
			std::cout << "0x" << std::hex << (~op1) << "\n";
			std::cout << "0b" << std::bitset<64>(!op1).to_string() << "\n";
		}
	}
}

/*
	Store the contents of a file for later use:

	1.Allocates a char for each character in the named file.
	2.Reads a char from the file and assigns a byte to that value.
	3.Prints the size of memory allocated

	The memory ranging from buffer to buffer+bufferSize should be a copy of the files content
*/
bool loadFile(std::string fileName) {
	std::ifstream readFile(fileName, std::ios::binary);
	if (readFile.is_open()) {
		readFile.seekg(0, std::ios::end);
		bufferSize = readFile.tellg();
		buffer = (char *)malloc(bufferSize);
		if (buffer != nullptr) {
			readFile.seekg(0,std::ios::beg);
			for (int i = 0; i < bufferSize; ++i) {
				buffer[i] = readFile.get();
			}
		}
		std::cout << "Loaded " << bufferSize << " bytes to memory. Use command \"printmem\" to view the content of the memory.\n";
		return true;
	}
	return false;
}

/*
	Splits a string str by any instance of the char splitBy not found in double quotes
*/
std::vector<std::string> split(std::string str, char splitBy) {
	std::vector<std::string> res = {};
	
	if (str.size() == 0) {
		return res;
	}

	bool inPath = false;

	std::string temp = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == splitBy && !inPath) {
			res.push_back(temp); 
			temp = "";
		} else if (str[i] == '\"') {  // So that it doesn't split spaces in a path name
			inPath = !inPath; // May not work with quotes within quotes
		} else {
			temp += str[i];
		}
	}

	// The last string may not have been added
	if (temp != "") {
		res.push_back(temp);
	}
	return res;
}

/* 
	Recursively get user input, split it by spaces and respond to the command typed.
	Recursion is stopped if "exit" is typed
*/
void prompt() {
	std::cout << "~$ ";
	
	std::string inputStr;
	std::getline(std::cin, inputStr);

	std::vector<std::string> args = split(inputStr, ' ');
	if (args.size() == 0) {
		std::cout << "\n";
		prompt();
	}

	if (args[0] == "exit") {
		std::cout << "\n";
		return;
	} else if (args[0] == "printmem") {
		for (int i = 0; i < bufferSize; ++i) {
			std::cout << buffer[i];
		}
		std::cout << "\n";
	} else if (args[0] == "load") {
		if (args.size() >= 2) {
			free(buffer);
			loadFile(args[1]) ? std::cout << "File " << args[1] << " loaded.\n" : std::cout << "File not found or failed to load.\n";
		}
	} else if (args[0] == "numop") {
		numop(args);
	} else if (args[0] == "strop") {
		strop(args);
	} else {
		std::cout << args[0] << " not recognized in this system.\n";
	}


	prompt();
}

int main() {
	system("cls"); // "clear" on linux

	prompt();

	free(buffer);
	return 0;
}
