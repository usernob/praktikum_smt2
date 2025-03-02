#include "fileio.h"

#include <cstddef>
#include <iostream>
#include <stdexcept>

BinaryFileHanlder::BinaryFileHanlder(const std::string &filename) : m_filename(filename)
{
    m_file.open(m_filename, std::ios::binary | std::ios::in | std::ios::out | std::ios::app);
    if (!m_file.is_open())
    {
        throw std::runtime_error("Tidak bisa membuka file database");
    }
}

BinaryFileHanlder::~BinaryFileHanlder()
{
    if (m_file.is_open())
    {
        m_file.close();
    }
}

void BinaryFileHanlder::m_read_string(std::string &output, size_t length)
{
    char *buffer = new char[length + 1];
    m_file.read(buffer, length);
    buffer[length] = '\0';
    output = std::string(buffer);
    delete[] buffer;
}

void BinaryFileHanlder::read(DoublyLinkedList &output)
{
    m_file.clear();
    m_file.seekg(0, std::ios::beg);

    while (m_file.peek() != EOF)
    {
        Food item;

        size_t name_length;
        m_file.read(reinterpret_cast<char *>(&name_length), sizeof(name_length));

        m_read_string(item.name, name_length);

        m_file.read(reinterpret_cast<char *>(&item.price), sizeof(item.price));

        size_t category_length;
        m_file.read(reinterpret_cast<char *>(&category_length), sizeof(category_length));

        m_read_string(item.category, category_length);

        m_file.read(reinterpret_cast<char *>(&item.available), sizeof(item.available));

        output.add(item);
    }
}

void BinaryFileHanlder::write(const DoublyLinkedList &input)
{
    m_file.close();
    m_file.open(m_filename, std::ios::binary | std::ios::out | std::ios::trunc);
    if (!m_file.is_open())
    {
        throw std::runtime_error("Gagal membuka file");
    }
    if (input.is_empty()) {
        m_file.close();
    }

    for (auto item = input.begin(); item != input.end() && item != nullptr; ++item)
    {
        Food *food = *item;

        size_t name_length = food->name.size();
        m_file.write(reinterpret_cast<char *>(&name_length), sizeof(name_length));
        m_file.write(food->name.data(), name_length);

        m_file.write(reinterpret_cast<char *>(&food->price), sizeof(food->price));

        size_t category_length = food->category.size();
        m_file.write(reinterpret_cast<char *>(&category_length), sizeof(category_length));
        m_file.write(food->category.data(), category_length);

        m_file.write(reinterpret_cast<char *>(&food->available), sizeof(food->available));
    }
}
