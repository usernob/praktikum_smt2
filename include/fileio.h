#pragma once

#include "doubly_linked_list.h"
#include "type.h"
#include <fstream>
#include <stdexcept>

class BinaryFileHanlder
{
private:
    void m_read_string(char *output, size_t length);
    std::fstream m_file;
    const char *m_filename;

public:
    BinaryFileHanlder(const char *filename);

    ~BinaryFileHanlder();

    void read(DoublyLinkedList &output);
    void write(const DoublyLinkedList &input);
};
