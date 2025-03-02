#pragma once

#include <climits>
#include <iostream>

#if defined(_WIN32) // Windows
SetConsoleOutputCP(CP_UTF8);
#define CLEAR_SCREEN system("cls");
#elif defined(__linux__) || defined(__unix__) // Linux
#define CLEAR_SCREEN std::cout << "\x1B[2J\x1B[H";
#endif


void get_input(const std::string &message, std::string &output);
bool get_input(const std::string &message, int &output, int min = 0, int max = INT_MAX);
bool get_input(const std::string &message, bool &output);
void wait_enter();

bool is_out_of_range(int input, int min, int max);
bool is_number(const std::string &input);
