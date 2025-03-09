#include "cashier.h"
#include "utils.h"

void cashier()
{
    while (1)
    {
        CLEAR_SCREEN
        std::cout << "======================================\n";
        std::cout << "        CASHIER'S DASHBOARD\n";
        std::cout << "======================================\n";

        Order *order = queue.front();
        if (order == nullptr)
        {
            std::cout << "\nFor now, no orders have come in yet.\n";
            wait_enter();
            continue;
        }
        std::cout << "Order No. " << queue.counter() << "\n";
        print_detail_order(order);

        std::cout << "1. Accept\n";
        std::cout << "2. Reject\n";
        std::cout << "3. Exit\n";

        int choice;
        if (!get_input(">", choice, 1, 3))
        {
            std::cout << "\nInvalid input\n";
            wait_enter();
            continue;
        }

        if (choice == 1)
        {
            std::cout << "\nWhat payment method does the customer refer to?\n";
            std::cout << "1. QRIS\n";
            std::cout << "2. Debit Card\n";
            std::cout << "3. Cash\n";
            int payment_method;

            if (!get_input(">", payment_method, 1, 3))
            {
                std::cout << "\nInvalid input\n";
                wait_enter();
                continue;
            }

            queue.dequeue();
            std::cout << "\nOrder " << order->id << " has been processed!\n";
            wait_enter();
        }

        else if (choice == 2)
        {
            queue.dequeue();
            std::cout << "\nOrder rejected\n";
            wait_enter();
        }

        else if (choice == 3)
        {
            break;
        }
    }
}
