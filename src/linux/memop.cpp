#include "memop.hpp"

std::string memToStr(char *c, size_t n) {
    std::string res = "";
    for (int i = 0; i < n; ++i) {
        res += c[i];
    }
    return res;
}

std::string xorStrEx(std::string op1, std::string op2) {
    std::string result = "";
    size_t size1 = op1.size();
    size_t size2 = op2.size();

    if (size1 > size2) {
        for (size_t i = 0; i < op1.size(); ++i) {
            char c = op1[i] ^ op2[i%size2];
            if (c > 31) {
                result += c;
            } else {
                result += "\\" + std::to_string((int)c);
            }
        }
        return op1;
    }
    for (size_t i = 0; i < op2.size(); ++i) {
        char c = op2[i] ^ op1[i%size1];
        if (c > 31) {
            result += c;
        } else {
            result += "\\" + std::to_string((int)c);
        }
    }
    return result;
}

std::string orStrEx(std::string op1, std::string op2) {
    std::string result = "";
    size_t size1 = op1.size();
    size_t size2 = op2.size();

    if (size1 > size2) {
        for (size_t i = 0; i < op1.size(); ++i) {
            char c = op1[i] | op2[i%size2];
            if (c > 31) {
                result += c;
            } else {
                result += "\\" + std::to_string((int)c);
            }
        }
        return op1;
    }
    for (size_t i = 0; i < op2.size(); ++i) {
        char c = op2[i] | op1[i%size1];
        if (c > 31) {
            result += c;
        } else {
            result += "\\" + std::to_string((int)c);
        }
    }
    return result;
}

std::string andStrEx(std::string op1, std::string op2) {
    std::string result = "";
    size_t size1 = op1.size();
    size_t size2 = op2.size();

    if (size1 > size2) {
        for (size_t i = 0; i < op1.size(); ++i) {
            char c = op1[i] & op2[i%size2];
            if (c > 31) {
                result += c;
            } else {
                result += "\\" + std::to_string((int)c);
            }
        }
        return op1;
    }
    for (size_t i = 0; i < op2.size(); ++i) {
        char c = op2[i] & op1[i%size1];
        if (c > 31) {
            result += c;
        } else {
            result += "\\" + std::to_string((int)c);
        }
    }
    return result;
}
