#include "miscellaneous.hpp"
#include <iostream>

void warning(const char* text) {
    std::cerr << "Warning: " << text << std::endl;
}

void error(const char* text) {
    std::cerr << "Error: " << text << std::endl;
    exit(-1);
}

void test(const char* file, int line) {
    std::cout << "Test from file " << file << " on line " << line << std::endl;
}