#include "user.h"
#include "queue.h"
#include "utils.h"
#include <cstring>

static unsigned int get_alphabet_order(char input)
{
    if (input >= 'a' && input <= 'z')
    {
        return input - 'a' + 1;
    }
    else if (input >= 'A' && input <= 'Z')
    {
        return input - 'A' + 1;
    }
    else
    {
        return 0;
    }
}

// true = continue, and vice versa
static bool order(Food *food, SharedQueue &queue)
{
    if (!food->available)
    {
        std::cout << "\nSorry, this menu is out of stock. Please choose a different one.\n";
        wait_enter();
        return true;
    }
    Order new_order = {"", "", "", 0, 0, ""};

    if (!get_input("\nInput your name\n>", new_order.name, USER_NAME_MAX))
    {
        std::cout << "Name must be less than " << USER_NAME_MAX << " characters\n";
        wait_enter();
        return true;
    }

    if (!get_input("\nInput amount\n>", new_order.amount))
    {
        std::cout << "Amount must be a number\n";
        wait_enter();
        return true;
    }

    if (!get_input("\nInput note (skip if none)\n>", new_order.note, NOTE_MAX))
    {
        std::cout << "Note must be less than " << NOTE_MAX << " characters\n";
        wait_enter();
        return true;
    }

    std::strcpy(new_order.food_name, food->name);

    new_order.total_price = food->price * new_order.amount;

    unsigned int first_segment, second_segment, third_segment;
    first_segment = get_alphabet_order(new_order.name[0]);
    second_segment = get_alphabet_order(new_order.food_name[0]);
    third_segment = get_alphabet_order(new_order.food_name[1]);

    std::snprintf(
        new_order.id,
        sizeof(new_order.id),
        "%02d%02d%02d%01d%01d", // 2 digit, 2 digit, 2 digit, 1 digit, 1 digit
        first_segment,
        second_segment,
        third_segment,
        new_order.amount,
        (std::strlen(new_order.note) != 0)
    );

    std::cout << "\nThe order has been sent. Please wait a moment!\n";
    print_detail_order(&new_order);

    queue.enqueue(new_order);

    return get_input_confirm("Would you like to order again? (y/n)");
}

void user()
{
    if (food_list.is_empty())
    {
        CLEAR_SCREEN
        std::cout << "Food list is empty\n";
        wait_enter();
        return;
    }
    DoublyLinkedList::Iterator food = food_list.begin();
    while (1)
    {
        CLEAR_SCREEN
        print_detail_food(*food);
        std::cout << "1. Next\n";
        std::cout << "2. Previous\n";
        std::cout << "3. Order\n";
        std::cout << "4. Exit\n";

        int choice;
        if (!get_input(">", choice, 1, 4))
        {
            continue;
        }
        if (choice == 1)
        {
            ++food;
        }
        else if (choice == 2)
        {
            --food;
        }
        else if (choice == 3)
        {
            if (order(*food, queue))
            {
                continue;
            }
            else
            {
                break;
            }
        }
        else if (choice == 4)
        {
            break;
        }
        else
        {
            continue;
        }
    }
}
