#include "utils.h"

void get_input(const std::string &message, std::string &output)
{
    std::cout << message << " ";
    getline(std::cin, output);
}

bool get_input(const std::string &message, int &output, int min, int max)
{
    std::string temp;
    get_input(message, temp);
    if (!is_number(temp))
    {
        return false;
    }

    int i_temp = std::stoi(temp);
    if (is_out_of_range(i_temp, min, max))
    {
        return false;
    }

    output = i_temp;

    return true;
}

bool get_input(const std::string &message, bool &output)
{
    int temp;
    return get_input(message, temp, 0, 1) && (output = temp == 1);
}

void wait_enter()
{
    std::string temp;
    std::cout << "\nPress Enter to Continue!!" << std::endl;
    getline(std::cin, temp);
}

bool is_out_of_range(int input, int min, int max)
{
    return input < min || input > max;
}

bool is_number(const std::string &input)
{
    for (char c : input)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}
