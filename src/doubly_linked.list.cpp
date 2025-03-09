#include "doubly_linked_list.h"
#include <cstring>

DoublyLinkedList::Node *DoublyLinkedList::m_find(const char *name) const
{
    Node *current = head;
    for (int index = 0; index < size; index++)
    {
        if (strcmp(current->data.name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void DoublyLinkedList::add(const Food &data)
{
    if (is_empty())
    {
        head = new Node(data);
        head->next = head;
        head->prev = head;
    }
    else
    {
        Node *new_node = new Node(data);
        Node *last = head->prev;

        new_node->next = head;
        new_node->prev = last;

        last->next = new_node;
        head->prev = new_node;
    }
    size++;
}

Food *DoublyLinkedList::find(const char *name) const
{
    Node *element = m_find(name);
    if (element != nullptr)
    {
        return &element->data;
    }
    return nullptr;
}

void DoublyLinkedList::remove(const char *name)
{
    if (is_empty())
    {
        return;
    }

    Node *element = m_find(name);
    if (element == nullptr)
    {
        return;
    }

    remove(element);
}

void DoublyLinkedList::remove(Node *node)
{
    if (node == head)
    {
        head = node->next;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    size--;
    if (size == 0)
    {
        head = nullptr;
    }
}

void DoublyLinkedList::clear()
{
    Node *current = head;
    for (int index = 0; index < size; index++)
    {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    size = 0;
}
