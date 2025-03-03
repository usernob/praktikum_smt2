#pragma once

#include "doubly_linked_list.h"
#include <fstream>

class BinaryFileHanlder
{
  private:
    void m_read_string(std::string &output, size_t length);
    std::fstream m_file;
    std::string m_filename;

  public:
    BinaryFileHanlder(const std::string &filename);

    ~BinaryFileHanlder();

    void read(DoublyLinkedList &output);
    void write(const DoublyLinkedList &input);
};
