#pragma once
#include <iostream>

class Node {
   public:
    uint64_t x;
    Node *n_prev;
    Node *n_next;
    Node();
};
