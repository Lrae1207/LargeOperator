#include "inout.hpp"

//https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = _popen(cmd, "r"); // popen on linux
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    }
    catch (...) {
        _pclose(pipe); // pclose on linux
        throw;
    }
    _pclose(pipe); // pclose on linux
    return result;
}

// Print n characters of buffer and fill any remaining space with ' 's
void printClamped(std::string buffer, int n, std::string color) {
    std::cout << color;
    for (int i = 0; i < n; ++i) {
        if (i < buffer.size()) {
            std::cout << buffer[i];
        }
        else {
            std::cout << ' ';
        }
    }
    std::cout << RESET;
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

/*
    Does a file exist in the current directory?
*/
bool fileExists(const std::string& filename)
{
    struct stat buf;
    return stat(filename.c_str(), &buf) != -1;
}
