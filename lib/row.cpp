#pragma once
#include "row.h"

#include <iostream>

Row::Row() {
    n_tail = new Node;
    n_head = new Node;
    r_prev = nullptr;
    r_next = nullptr;
    n_tail->n_next = nullptr;
    n_tail->n_prev = nullptr;
    n_head->n_next = nullptr;
    n_head->n_prev = nullptr;
}

Row::~Row() {
    while (n_head) {
        n_tail = n_head->n_next;
        delete n_head;
        n_head = n_tail;
    }
};