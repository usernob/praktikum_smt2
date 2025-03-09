#include "utils.h"

bool clean_cin()
{
    std::cin.clear();
    if (std::cin.peek() != EOF && std::cin.peek() == '\n')
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return true;
}

void print_detail_food(const Food *food)
{
    std::cout << "--------------------------------------\n";
    std::cout << "| Food \t\t: " << food->name << "\n";
    std::cout << "| Price \t: Rp " << food->price << "\n";
    std::cout << "| Category \t: " << food->category << "\n";
    std::cout << "| Available \t: " << (food->available ? "Yes" : "No") << "\n";
    std::cout << "--------------------------------------\n";
}

void print_detail_order(const Order *order)
{
    std::cout << "--------------------------------------\n";
    std::cout << "| ID\t\t: " << order->id << "\n";
    std::cout << "| Name\t\t: " << order->name << "\n";
    std::cout << "| Food\t\t: " << order->food_name << "\n";
    std::cout << "| Amount\t: " << order->amount << "\n";
    std::cout << "| Total\t\t: " << order->total_price << "\n";
    std::cout << "| Note\t\t: " << order->note << "\n";
    std::cout << "--------------------------------------\n";
}

bool get_input(const char *message, char *output, size_t length)
{
    std::cout << message << " ";
    std::cin.getline(output, length);
    return !std::cin.fail();
}

bool get_input(const char *message, int &output, int min, int max)
{
    char temp[20];
    if (get_input(message, temp, 20))
    {
        if (is_number(temp))
        {
            output = std::atoi(temp);
            return !is_out_of_range(output, min, max);
        }
    }
    return false;
}

bool get_input(const char *message, bool &output)
{
    int temp;
    return get_input(message, temp, 0, 1) && (output = temp);
}

bool get_input_confirm(const char *message)
{
    std::cout << message << " ";
    char choice;
    std::cin >> choice;
    clean_cin();
    return !std::cin.fail() && (choice == 'y' || choice == 'Y');
}

void wait_enter()
{
    std::cout << "\nPress Enter to Continue!!" << std::endl;
    clean_cin();
}

bool is_out_of_range(int input, int min, int max)
{
    return input < min || input > max;
}

bool is_number(const char *input)
{
    size_t i = 0;
    while (input[i] != '\0')
    {
        char c = input[i];
        if (!isdigit(c))
        {
            return false;
        }
        i++;
    }
    return true;
}
