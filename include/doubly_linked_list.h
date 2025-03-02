#pragma once

#include <string>

struct Food
{
    std::string name;
    int price;
    std::string category;
    bool available;
};

class DoublyLinkedList
{
  public:
    struct Node
    {
        Food data;
        Node *next;
        Node *prev;

        Node(Food data)
        {
            this->data = data;
            this->next = nullptr;
            this->prev = nullptr;
        }
    };

  private:
    Node *head = nullptr;
    Node *tail = nullptr;

    int size = 0;

  public:
    DoublyLinkedList() {};

    ~DoublyLinkedList()
    {
        clear();
    }

    void add(const Food &data); // Create

    Food *find(const std::string &name) const; // Search

    // Internal find very dangerous to use directly, avoid it if you can
    Node *m_find(const std::string &name) const;

    void remove(const std::string &name); // Delete
    void remove(Node *node);

    void clear();

    int get_size() const
    {
        return size;
    }

    bool is_empty() const
    {
        return size == 0;
    }

    class Iterator
    {
        Node *current;
        bool first_iterator;

      public:
        Iterator(Node *node)
        {
            current = node;
            first_iterator = true;
        }

        Food *operator*() const
        {
            return &current->data;
        }

        Iterator &operator++()
        {
            current = current->next;
            return *this;
        }

        Iterator &operator--()
        {
            current = current->prev;
            return *this;
        }

        bool operator!=(const Iterator &other)
        {
            if (first_iterator)
            {
                first_iterator = false;
                return true;
            }
            return current != other.current;
        }
    };

    Iterator begin() const
    {
        return Iterator(head);
    }

    Iterator end() const
    {
        return Iterator(head);
    }
};
