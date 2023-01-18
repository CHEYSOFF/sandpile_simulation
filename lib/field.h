#pragma once
#include <iostream>
#include <string>

#include "flags.cpp"
#include "node.cpp"
#include "row.cpp"

class Field {
   public:
    uint64_t n = 0;
    uint64_t m = 0;
    Field *f_prev;
    Field *f_next;
    Row *r_tail;
    Row *r_head;
    Field();
    ~Field();
    void output();
    void BmpOutput(const std::string &path);
    bool NodeAdd(uint64_t i, uint64_t j, uint64_t x);
    void NodeAddLeft(uint64_t i_0, uint64_t x);
    void NodeAddRight(uint64_t i_0, uint64_t x);
    void NodeAddUp(uint64_t j_0, uint64_t x);
    void NodeAddDown(uint64_t j_0, uint64_t x);
    void NodeAddMiddle(uint64_t i_0, uint64_t j_0, uint64_t x);
    bool MakeFieldIteration();
    void Epoch(input_var inp);
};
