#pragma once
#include <limits>
#define TEST test(__FILE__, __LINE__)

void warning(const char* text);
void error(const char* text);
void test(const char* file_name, int line);

const int inf = std::numeric_limits<int>::max();
const long infl = std::numeric_limits<long>::max();

typedef int vertex;