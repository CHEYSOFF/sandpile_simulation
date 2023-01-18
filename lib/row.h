#pragma once
#include <iostream>
#include <string>

#include "node.cpp"

class Row {
   public:
    uint64_t m = 0;
    Row *r_prev;
    Row *r_next;
    Node *n_tail;
    Node *n_head;
    Row();
    ~Row();
};