#pragma once

#include "doubly_linked_list.h"
#include <climits>
#include <cstddef>
#include <iostream>
#include <limits>

#if defined(_WIN32) // Windows

#include <windows.h>
SetConsoleOutputCP(CP_UTF8);
#define CLEAR_SCREEN system("cls");

#elif defined(__linux__) || defined(__unix__) // Linux

#define CLEAR_SCREEN std::cout << "\x1B[2J\x1B[H";

#endif

void print_detail_food(const Food *food);
void print_detail_order(const Order *order);
bool get_input(const char *message, char *output, size_t length);
bool get_input(const char *message, int &output, int min = 0, int max = INT_MAX);
bool get_input(const char *message, bool &output);
bool get_input_confirm(const char *message);
void wait_enter();

bool clean_cin();
bool is_out_of_range(int input, int min, int max);
bool is_number(const char *input);
