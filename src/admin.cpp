#include "admin.h"
#include "type.h"

static void add_food()
{
    Food new_food = {"", 0, "", false};
    if (!get_input("\nFood's name\n>", new_food.name, FOOD_NAME_MAX))
    {
        std::cout << "Name must be less than " << FOOD_NAME_MAX << " characters\n";
        wait_enter();
        return;
    }

    if (!get_input("\nPrice\n>", new_food.price))
    {
        std::cout << "Price must be a number\n";
        wait_enter();
        return;
    };

    if (!get_input("\nCategory\n>", new_food.category, CATEGORY_MAX))
    {
        std::cout << "Category must be less than " << CATEGORY_MAX << " characters\n";
        wait_enter();
        return;
    }

    new_food.available = get_input_confirm("\nAvailable\n>");

    food_list.add(new_food);
    wait_enter();
}

static void find_food()
{
    char food_name[FOOD_NAME_MAX];
    if (!get_input("Insert the food name you want to find\n>", food_name, FOOD_NAME_MAX))
    {
        std::cout << "\nName must be less than " << FOOD_NAME_MAX << " characters\n";
        wait_enter();
        return;
    }

    Food *food = food_list.find(food_name);
    if (food != nullptr)
    {
        std::cout << "\n" << food->name << "'s data found\n";
        print_detail_food(food);
    }
    else
    {
        std::cout << "\n" << food_name << "'s data not found";
    }
    wait_enter();
}

static void delete_food()
{
    char food_name[FOOD_NAME_MAX];
    if (!get_input("Insert the food name you want to find\n>", food_name, FOOD_NAME_MAX))
    {
        std::cout << "\nName must be less than " << FOOD_NAME_MAX << " characters\n";
        wait_enter();
        return;
    }

    DoublyLinkedList::Node *node = food_list.m_find(food_name);
    if (node != nullptr)
    {
        std::cout << "\n" << node->data.name << "'s data found\n";
        print_detail_food(&node->data);

        if (get_input_confirm("Are you sure you want to delete? (y/n)\n>"))
        {
            food_list.remove(node);
            std::cout << "\n" << food_name << "'s data has been deleted\n";
        }
        else
        {
            std::cout << "\nAborted\n";
        }
    }
    else
    {
        std::cout << food_name << "'s data not found";
    }
    wait_enter();
}

static void change_food()
{
    char food_name[FOOD_NAME_MAX];
    if (!get_input("Insert the food name you want to find\n>", food_name, FOOD_NAME_MAX))
    {
        std::cout << "\nName must be less than " << FOOD_NAME_MAX << " characters\n";
        wait_enter();
        return;
    }

    Food *food = food_list.find(food_name);
    if (food != nullptr)
    {
        std::cout << "\n- Changing " << food->name << "'s data\n";
        std::cout << "1. Change Price\n";
        std::cout << "2. Change Category\n";
        std::cout << "3. Change Availability\n";

        int choice;
        if (!get_input(">", choice, 1, 3))
        {
            return;
        }

        switch (choice)
        {
            case 1:
                if (!get_input("Insert the new price\n>", food->price))
                {
                    std::cout << "Price must be a number\n";
                    wait_enter();
                    return;
                }
                break;
            case 2:
                if (!get_input("Insert the new category\n>", food->category, CATEGORY_MAX))
                {
                    std::cout << "Category must be less than " << CATEGORY_MAX << " characters\n";
                    wait_enter();
                    return;
                }
                break;
            case 3:
                food->available = get_input_confirm("Insert the new availability\n>");
                break;
        }
        std::cout << "\n" << food->name << "'s data has been changed\n";
        print_detail_food(food);
    }
    else
    {
        std::cout << "\n" << food_name << "'s data not found";
    }
    wait_enter();
}

static void show_all_food()
{
    if (food_list.is_empty())
    {
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
        std::cout << "3. Exit\n";

        int choice;
        if (!get_input(">", choice, 1, 3))
        {
            return;
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
            break;
        }
        else
        {
            continue;
        }
    }
}

void admin()
{
    const int menu_count = 5;
    // clang-format off
    void (*const admin_menu[menu_count])() = {
        add_food, 
        find_food,
        delete_food,
        change_food,
        show_all_food,
    };
    // clang-format on

    while (1)
    {
        CLEAR_SCREEN
        std::cout << "======================================\n";
        std::cout << "          ADMIN'S DASHBOARD\n";
        std::cout << "======================================\n";
        std::cout << "|1. Add Food's Data\n";
        std::cout << "|2. Find Food's Data\n";
        std::cout << "|3. Delete Food's Data\n";
        std::cout << "|4. Change Food's Data\n";
        std::cout << "|5. See All Food's Data\n";
        std::cout << "|6. Exit\n";

        int choice;
        if (!get_input(">", choice, 1, menu_count + 1))
        {
            std::cout << "Invalid input\n";
            wait_enter();
            continue;
        }

        if (choice == 6)
        {
            break;
        }

        CLEAR_SCREEN
        admin_menu[choice - 1]();
    }
}
