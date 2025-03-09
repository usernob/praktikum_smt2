#include "fileio.h"

BinaryFileHanlder::BinaryFileHanlder(const char *filename) : m_filename(filename)
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

void BinaryFileHanlder::m_read_string(char *output, size_t length)
{
    m_file.read(output, length);
    output[length] = '\0';
}

void BinaryFileHanlder::read(DoublyLinkedList &output)
{
    m_file.clear();
    m_file.seekg(0, std::ios::beg);

    while (m_file.peek() != EOF)
    {
        Food item;

        m_read_string(item.name, FOOD_NAME_MAX);

        m_file.read(reinterpret_cast<char *>(&item.price), sizeof(item.price));

        m_read_string(item.category, CATEGORY_MAX);

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
    if (input.is_empty())
    {
        m_file.close();
        return;
    }

    for (auto item = input.begin(); item != input.end(); ++item)
    {
        Food *food = *item;

        m_file.write(food->name, FOOD_NAME_MAX);

        m_file.write(reinterpret_cast<char *>(&food->price), sizeof(food->price));

        m_file.write(food->category, CATEGORY_MAX);

        m_file.write(reinterpret_cast<char *>(&food->available), sizeof(food->available));
    }
}
