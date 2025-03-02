#include "doubly_linked_list.h"
#include "utils.h"
#include "fileio.h"

static BinaryFileHanlder food_db("database.bin");
static DoublyLinkedList food_list;

static void print_detail_food(const Food *food)
{
    std::cout << "--------------------------------------\n";
    std::cout << "| Food \t\t: " << food->name << "\n";
    std::cout << "| Price \t: Rp " << food->price << "\n";
    std::cout << "| Category \t: " << food->category << "\n";
    std::cout << "| Available \t: " << (food->available ? "Yes" : "No") << "\n";
    std::cout << "--------------------------------------\n";
}

static void add_food()
{
    Food new_food;
    get_input("\nFood's name\n>", new_food.name);

    if (!get_input("\nPrice\n>", new_food.price))
    {
        std::cout << "Price must be a number\n";
        wait_enter();
        return;
    };

    get_input("\nCategory\n>", new_food.category);

    if (!get_input("\nAvailable\n>", new_food.available))
    {
        std::cout << "Available must be Yes or No\n";
        wait_enter();
        return;
    }

    food_list.add(new_food);
    wait_enter();
}

static void find_food()
{
    std::string food_name;
    get_input("Insert the food name you want to find\n>", food_name);

    Food *food = food_list.find(food_name);
    if (food != nullptr)
    {
        std::cout << "\n" << food->name << "'s data found\n";
        print_detail_food(food);
    }
    else
    {
        std::cout << food_name << "'s data not found";
    }
    wait_enter();
}

static void delete_food()
{
    std::string food_name;
    get_input("Insert the food name you want to delete\n>", food_name);

    DoublyLinkedList::Node *node = food_list.m_find(food_name);
    if (node != nullptr)
    {
        std::cout << "\n" << node->data.name << "'s data found\n";
        print_detail_food(&node->data);

        std::string choice;
        get_input("Are you sure you want to delete? (y/n)\n>", choice);

        if (choice == "y")
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
    std::string food_name;
    get_input("Insert the food name you want to change\n>", food_name);

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
                get_input("Insert the new category\n>", food->category);
                break;
            case 3:
                if (!get_input("Insert the new availability\n>", food->available))
                {
                    std::cout << "Availability must be Yes or No\n";
                    wait_enter();
                    return;
                }
                break;
        }
        std::cout << "\n" << food->name << "'s data has been changed\n";
        print_detail_food(food);
    }
    else
    {
        std::cout << food_name << "'s data not found";
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

static void admin()
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

    std::string message;
    while (1)
    {
        CLEAR_SCREEN
        if (!message.empty())
        {
            std::cout << message << "\n";
        }
        std::cout << "======================================\n";
        std::cout << "ADMIN'S DASHBOARD\n";
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
            message = "Invalid Input";
            continue;
        }

        if (choice == 6)
        {
            break;
        }

        CLEAR_SCREEN
        message = "";
        admin_menu[choice - 1]();
    }
}

static void cashier()
{
    // TODO
}

static void user()
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
            std::cout << "Not yet implemented\n"; // TODO
            wait_enter();
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

int main()
{
    food_db.read(food_list);

    const int privilage_count = 3;
    void (*const privilage[privilage_count])() = {admin, cashier, user};

    CLEAR_SCREEN
    std::cout << "======================================\n";
    std::cout << "WELCOME TO YU EN I ES EI\n";
    std::cout << "======================================\n";
    std::cout << "|1. Login as Admin\n";
    std::cout << "|2. Login as Cashier\n";
    std::cout << "|3. Login as User\n";
    std::cout << "|4. Exit\n";

    int choice;
    if (!get_input(">", choice, 1, privilage_count + 1))
    {
        return 1;
    }

    if (choice == 4)
    {
        return 0;
    }

    privilage[choice - 1]();

    food_db.write(food_list);
    return 0;
}
