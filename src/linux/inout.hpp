#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#define BLACK     "\x1b[30m"
#define RED       "\x1b[31m"
#define GREEN     "\x1b[32m"
#define YELLOW    "\x1b[33m"
#define BLUE      "\x1b[34m"
#define MAGENTA   "\x1b[35m"
#define CYAN      "\x1b[36m"
#define RESET     "\x1b[37m"

std::string exec(const char* cmd);
void printClamped(std::string buffer, int n, std::string color);
int parseValue(std::string str);
bool fileExists(const std::string& filename);
