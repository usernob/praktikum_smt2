#include "doubly_linked_list.h"

DoublyLinkedList::Node *DoublyLinkedList::m_find(const std::string &name) const
{
    Node *current = head;
    for (int index = 0; index < size; index++)
    {
        if (current->data.name == name)
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
        tail = head;
    }
    else
    {
        Node *new_node = new Node(data);
        tail->next = new_node;
        head->prev = new_node;

        new_node->prev = tail;
        new_node->next = head;

        tail = new_node;
    }
    size++;
}

Food *DoublyLinkedList::find(const std::string &name) const
{
    Node *element = m_find(name);
    if (element != nullptr)
    {
        return &element->data;
    }
    return nullptr;
}

void DoublyLinkedList::remove(const std::string &name)
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
    if (node == tail)
    {
        tail = node->prev;
    }
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
        tail = nullptr;
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
    tail = nullptr;
    size = 0;
}
