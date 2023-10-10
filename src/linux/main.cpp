#include <string>
#include <vector>
#include <fstream>
#include <ios>
#include <bitset>

#include "inout.hpp"
#include "memop.hpp"

char* buffer = (char*)malloc(1);
size_t	bufferSize = 0;

void memop(std::vector<std::string> args) {
	if (args.size() == 2) {
		std::string res = "";
		if (args[1] == "and" || args[1] == "&") {
			res = andStrEx(memToStr(buffer, bufferSize), memToStr(buffer, bufferSize));
		} else if (args[1] == "or" || args[1] == "|") {
			res = orStrEx(memToStr(buffer, bufferSize), memToStr(buffer, bufferSize));
		} else if (args[1] == "xor" || args[1] == "^") {
			res = xorStrEx(memToStr(buffer, bufferSize), memToStr(buffer, bufferSize));
		} else {
			std::cout << "Invalid operation.\n";
			return;
		}

		std::cout << "\"" << res << "\"\n";

		for (int i = 0; i < res.size(); ++i) {
			buffer[i] = res[i];
		}
	} else {
		std::cout << "Invalid parameters.\n";
	}
}

void strop(std::vector<std::string> args) {
	if (args.size() >= 4) {
		std::string op1 = args[2];
		std::string op2 = args[3];
		
		std::string res = "";

		if (args[1] == "and" || args[1] == "&") {
			res = andStrEx(op1, op2);
		} else if (args[1] == "or" || args[1] == "|") {
			res = orStrEx(op1, op2);
		} else if (args[1] == "xor" || args[1] == "^") {
			res = xorStrEx(op1, op2);
		} else {
			std::cout << "Invalid operation.\n";
			return;
		}

		std::cout << "\"" << res << "\"" << "\n";

		std::ofstream output("result.str");
		output << res;
		output.close();
		std::cout << "Results saved to result.str\n";
	} else {
		std::cout << "Invalid parameters.\n";
	}
}


// Perform a number logical operation
void numop(std::vector<std::string> args) {
	if (args.size() >= 4) {
		unsigned long long op1 = parseValue(args[2]);
		unsigned long long op2 = parseValue(args[3]);

		unsigned long long res = 0;

		if (args[1] == "and" || args[1] == "&") {
			std::cout << "0d" << std::dec << (op1 & op2) << "\n";
			std::cout << "0x" << std::hex << (op1 & op2) << "\n";
			std::cout << "0b" << std::bitset<64>(op1 & op2).to_string() << "\n";
			res = (op1 & op2);
		} else if (args[1] == "or" || args[1] == "|") {
			std::cout << "0d" << std::dec << (op1 | op2) << "\n";
			std::cout << "0x" << std::hex << (op1 | op2) << "\n";
			std::cout << "0b" << std::bitset<64>(op1 | op2).to_string() << "\n";
			res = (op1 | op2);
		} else if (args[1] == "xor" || args[1] == "^") {
			std::cout << "0d" << (op1 ^ op2) << "\n";
			std::cout << "0x" << std::hex << (op1 ^ op2) << "\n";
			std::cout << "0b" << std::bitset<64>(op1 ^ op2).to_string() << "\n";
			res = (op1 ^ op2);
		} else if (args[1] == "shl" || args[1] == "<<") {
			std::cout << "0d" << std::dec << (op1 << op2) << "\n";
			std::cout << "0x" << std::hex << (op1 << op2) << "\n";
			std::cout << "0b" << std::bitset<64>(op1 << op2).to_string() << "\n";
			res = (op1 << op2);
		} else if (args[1] == "shr" || args[1] == ">>") {
			std::cout << "0d" << std::dec << (op1 >> op2) << "\n";
			std::cout << "0x" << std::hex << (op1 >> op2) << "\n";
			std::cout << "0b" << std::bitset<64>(op1 >> op2).to_string() << "\n";
			res = (op1 >> op2);
		} else {
			std::cout << "Invalid operation.\n";
			return;
		}

		std::ofstream output("result.str");
		std::ofstream outputNum("result.int");

		output << std::to_string(res);
		output.close();

		outputNum << res;
		outputNum.close();
		 
		std::cout << "Results saved to result.str and result.int\n";
	} else if (args.size() == 3) {
		unsigned long long res = 0;
		if (args[1] == "not" || args[1] == "~" || args[1] == "!") {
			unsigned long long op1 = parseValue(args[2]);

			std::cout << "0d" << std::dec << (~op1) << "\n";
			std::cout << "0x" << std::hex << (~op1) << "\n";
			std::cout << "0b" << std::bitset<64>(~op1).to_string() << "\n";

			res = (~op1);
		} else {
			std::cout << "Invalid parameters.\n";
			return;
		}

		std::ofstream output("result.str");
		std::ofstream outputNum("result.int");

		output << std::to_string(res);
		output.close();

		outputNum << res;
		outputNum.close();
		std::cout << "Results saved to result.str and result.int\n";
	} else {
		std::cout << "Invalid parameters.\n";
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
	if (!fileExists(fileName)) { return false; }
	std::ifstream readFile(fileName, std::ios::binary);
	if (readFile.is_open()) {
		readFile.seekg(0, std::ios::end);
		bufferSize = readFile.tellg();
		buffer = (char*)malloc(bufferSize);
		if (buffer != nullptr) {
			readFile.seekg(0, std::ios::beg);
			for (int i = 0; i < bufferSize; ++i) {
				buffer[i] = readFile.get();
			}
		}
		std::cout << "Loaded " << bufferSize << " bytes to memory. Use command \"printmem\" to view the content of the memory.\n";
		readFile.close();
		return true;
	}
	readFile.close();
	return false;
}

bool saveMem(std::string fileName) {
	if (fileExists(fileName)) {
		std::cout << "File " << fileName << " already exists in the current directory. Replace it?";
		std::string input;
		std::cin >> input;
		if (input != "y" && input != "Y") {
			return false;
		}
	}
	std::ofstream targFile(fileName);
	if (targFile.is_open()) {
		std::string str = "";
		for (int i = 0; i < bufferSize; ++i) {
			str += buffer[i];
		}
		targFile << str;
	}
	targFile.close();
	return true;
}

bool copyFile(std::string targName, std::string srcName) {
	if (fileExists(srcName)) {
		std::cout << "File " << srcName << " already exists in the current directory. Replace it?";
		std::string input;
		std::cin >> input;
		if (input != "y" && input != "Y") {
			return false;
		}
	}
	std::ofstream targFile(srcName);
	std::ifstream srcFile(targName);
	if (targFile.is_open() && srcFile.is_open()) {
		while (srcFile) {
			char c = srcFile.get();
			targFile << c;
		}
		srcFile.close();
		targFile.close();
		return true;
	}
	srcFile.close();
	targFile.close();
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
		return;
	} else if (args[0] == "printmem") {
		if (args.size() == 2 && args[1] == "-n") {
			for (int i = 0; i < bufferSize; ++i) {
				std::cout << "0x" << std::hex << std::to_string(int(buffer[i])) << " ";
			}
		} else {
			for (int i = 0; i < bufferSize; ++i) {
				std::cout << buffer[i];
			}
		}
		std::cout << "\n";
	} else if (args[0] == "load") {
		if (args.size() >= 2) {
			free(buffer);
			loadFile(args[1]) ? std::cout << "File " << args[1] << " loaded.\n" : std::cout << "File not found or failed to load.\n" << exec("dir"); // replace "dir" with the search and list shell script
		} else {
			std::cout << "Invalid number of arguments.\n" << exec("dir"); // replace "dir" with the search and list shell script
		}
	} else if (args[0] == "copy") {
		if (args[0].size() >= 3) {
			copyFile(args[2], args[1]) ? std::cout << "Copied contents of " << args[1] << " to " << args[2] << "\n" : std::cout << "Failed to copy contents\n";
		} else {
			std::cout << "Invalid number of arguments.\n";
		}
	} else if (args[0] == "savemem") {
		if (args.size() >= 2) {
			loadFile(args[1]) ? std::cout << "Memory of size " << bufferSize << " bytes loaded to " << args[1] << "\n" : std::cout << "Failed to load memory.\n";
		} else {
			std::cout << "Invalid number of arguments.\n";
		}
	} else if (args[0] == "numop") {
		numop(args);
	} else if (args[0] == "strop") {
		strop(args);
	} else if (args[0] == "memop") {
		memop(args);
	} else {
		std::cout << args[0] << " not recognized in this system.\n";
	}


	prompt();
}

int main() {
	system("clear");

	prompt();

	return 0;
}
