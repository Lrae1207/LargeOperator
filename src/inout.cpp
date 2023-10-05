#include "inout.hpp"

//https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-the-output-of-the-command-within-c-using-po
std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

// Print n characters of buffer and fill any remaining space with ' 's
void printClamped(std::string buffer, int n, std::string color) {
    std::cout << color;
    for (int i = 0; i < n; ++i) {
        if (i < buffer.size()) {
            std::cout << buffer[i];
        } else {
            std::cout << ' ';
        }
    }
    std::cout << RESET;
}
