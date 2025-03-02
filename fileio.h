#pragma once

#include "doubly_linked_list.h"
#include <fstream>

class BinaryFileHanlder
{
  private:
    std::fstream m_file;
    std::string m_filename;

    void m_read_string(std::string &output, size_t length);

  public:
    BinaryFileHanlder(const std::string &filename);

    ~BinaryFileHanlder();

    void read(DoublyLinkedList &output);
    void write(const DoublyLinkedList &input);
};
