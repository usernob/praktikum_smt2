#include "doubly_linked_list.h"
#include "fileio.h"
#include "utils.h"

#include "admin.h"
#include "cashier.h"
#include "user.h"

static BinaryFileHanlder food_db("database.bin");
DoublyLinkedList food_list;
SharedQueue queue = SharedQueue();

int main()
{
    food_db.read(food_list);

    const int privilage_count = 3;
    void (*const privilage[privilage_count])() = {admin, cashier, user};

    while (1)
    {

        CLEAR_SCREEN
        std::cout << "======================================\n";
        std::cout << "      WELCOME TO YU EN I ES EI\n";
        std::cout << "======================================\n";
        std::cout << "|1. Login as Admin\n";
        std::cout << "|2. Login as Cashier\n";
        std::cout << "|3. Login as User\n";
        std::cout << "|4. Exit\n";

        int choice;
        if (!get_input(">", choice, 1, privilage_count + 1))
        {
            std::cout << "Invalid input\n";
            wait_enter();
            continue;
        }

        if (choice == 4)
        {
            break;
        }

        privilage[choice - 1]();
    }

    food_db.write(food_list);
    return 0;
}
