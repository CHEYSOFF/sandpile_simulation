#pragma once
#include "field.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "bmp.cpp"

Field::Field() {
    r_tail = new Row;
    r_head = new Row;
    f_prev = nullptr;
    f_next = nullptr;
    r_tail->r_next = nullptr;
    r_tail->r_prev = nullptr;
    r_head->r_next = nullptr;
    r_head->r_prev = nullptr;
}

Field::~Field() {
    while (r_head) {
        r_tail = r_head->r_next;
        delete r_head;
        r_head = r_tail;
    }
}

void Field::output() {
    Row* r_cur = r_tail;
    while (true) {
        Node* n_cur = r_cur->n_tail;

        while (true) {
            std::cout << n_cur->x << " ";
            n_cur = n_cur->n_next;

            if (n_cur == nullptr) {
                break;
            }
        }

        r_cur = r_cur->r_next;
        std::cout << '\n';

        if (r_cur == nullptr) {
            break;
        }
    }
    std::cout << '\n';
}

Color ColorOfCell(uint64_t amount) {
    Color cell;
    switch (amount) {
        case 0:
            cell = Color(255, 255, 255);
            break;
        case 1:
            cell = Color(0, 214, 120);
            break;
        case 2:
            cell = Color(139, 0, 255);
            break;
        case 3:
            cell = Color(255, 255, 0);
            break;
        default:
            cell = Color(0, 0, 0);
            break;
    }
    return cell;
}

// 0 - белый, 1 - зеленый, 2 - фиолетовый, 3 - желтый, > 3 - черный.

void Field::BmpOutput(const std::string& path) {
    const uint64_t width = m;
    const uint64_t height = n;
    Image image(width, height);
    Row* r_cur = r_tail;
    uint64_t i = 0;
    while (true) {
        uint64_t j = 0;
        Node* n_cur = r_cur->n_tail;

        while (true) {
            image.SetColor(ColorOfCell(n_cur->x), j, i);
            n_cur = n_cur->n_next;
            j++;

            if (n_cur == nullptr) {
                break;
            }
        }

        r_cur = r_cur->r_next;
        i++;

        if (r_cur == nullptr) {
            break;
        }
    }
    if (image.Export(path) == 0) {
        std::cerr << "Wrong output directory\n";
        return;
    }
}

Field* From2DArray(const std::vector<std::vector<uint64_t>>& sand_field) {
    uint64_t n = sand_field.size();
    uint64_t m = sand_field[0].size();
    for (uint64_t i = 0; i < n; i++) {
        m = std::max(m, sand_field[i].size());
    }

    Field* new_field = new Field;
    new_field->n = n;
    new_field->m = m;
    Row* prev_row = nullptr;

    for (uint64_t i = 0; i < n; i++) {
        Row* r_cur = new Row;
        r_cur->m = m;
        r_cur->r_prev = prev_row;
        if (prev_row != nullptr) {
            prev_row->r_next = r_cur;
        }
        r_cur->r_next = nullptr;
        prev_row = r_cur;

        if (i == 0) {
            new_field->r_tail = r_cur;
        }
        if (i == n - 1) {
            new_field->r_head = r_cur;
        }

        Node* prev_node = nullptr;

        for (uint64_t j = 0; j < m; j++) {
            Node* n_cur = new Node();
            n_cur->n_prev = prev_node;

            if (prev_node != nullptr) {
                prev_node->n_next = n_cur;
            }

            n_cur->n_next = nullptr;
            n_cur->x = sand_field[i][j];
            prev_node = n_cur;

            if (j == 0) {
                r_cur->n_tail = n_cur;
            }
            if (j == m - 1) {
                r_cur->n_head = n_cur;
            }
        }
    }
    return new_field;
}

bool Field::NodeAdd(uint64_t i, uint64_t j, uint64_t x) {
    if (j == -1) {
        NodeAddLeft(i, x);
    } else if (j == m) {
        NodeAddRight(i, x);
    } else if (i == -1) {
        NodeAddUp(j, x);
    } else if (i == n) {
        NodeAddDown(j, x);
    } else if (i >= 0 && i < n && j >= 0 && j < m) {
        NodeAddMiddle(i, j, x);
        return false;
    }
    return true;
}

void Field::NodeAddMiddle(uint64_t i_0, uint64_t j_0, uint64_t x) {
    Row* r_cur = r_tail;
    while (true) {
        Node* n_cur = r_cur->n_tail;

        while (true) {
            if (i_0 == 0 && j_0 == 0) {
                n_cur->x = n_cur->x + x;
                return;
            }
            n_cur = n_cur->n_next;
            if (i_0 == 0) {
                j_0--;
            }

            if (n_cur == nullptr) {
                break;
            }
        }

        r_cur = r_cur->r_next;
        i_0--;

        if (r_cur == nullptr) {
            break;
        }
    }
}

void Field::NodeAddLeft(uint64_t i_0, uint64_t x) {
    m++;
    Row* r_cur = r_tail;
    while (true) {
        Node* n_cur = r_cur->n_tail;

        Node* n_new = new Node;
        n_cur->n_prev = n_new;
        n_new->n_next = n_cur;

        if (i_0 == 0) {
            n_new->x = x;
        }

        r_cur->n_tail = n_new;

        r_cur = r_cur->r_next;
        i_0--;
        if (r_cur == nullptr) {
            break;
        }
    }
}

void Field::NodeAddRight(uint64_t i_0, uint64_t x) {
    m++;
    Row* r_cur = r_tail;
    while (true) {
        Node* n_cur = r_cur->n_head;

        Node* n_new = new Node;
        n_cur->n_next = n_new;
        n_new->n_prev = n_cur;

        if (i_0 == 0) {
            n_new->x = x;
        }

        r_cur->n_head = n_new;

        r_cur = r_cur->r_next;
        i_0--;

        if (r_cur == nullptr) {
            break;
        }
    }
}

void Field::NodeAddUp(uint64_t j_0, uint64_t x) {
    n++;
    Row* r_cur = r_tail;
    Row* r_new = new Row;
    r_new->r_next = r_cur;

    r_tail = r_new;

    Node* prev_node = nullptr;

    for (uint64_t j = 0; j < m; j++) {
        Node* n_cur = new Node();
        n_cur->n_prev = prev_node;

        if (prev_node != nullptr) {
            prev_node->n_next = n_cur;
        }

        n_cur->n_next = nullptr;
        if (j_0 == j) n_cur->x = x;
        prev_node = n_cur;

        if (j == 0) {
            r_new->n_tail = n_cur;
        }
        if (j == m - 1) {
            r_new->n_head = n_cur;
        }
    }
}

void Field::NodeAddDown(uint64_t j_0, uint64_t x) {
    n++;
    Row* r_cur = r_head;
    Row* r_new = new Row;
    r_new->r_prev = r_cur;
    r_cur->r_next = r_new;

    r_head = r_new;

    Node* prev_node = nullptr;

    for (uint64_t j = 0; j < m; j++) {
        Node* n_cur = new Node();
        n_cur->n_prev = prev_node;

        if (prev_node != nullptr) {
            prev_node->n_next = n_cur;
        }

        n_cur->n_next = nullptr;
        if (j_0 == j) n_cur->x = x;
        prev_node = n_cur;

        if (j == 0) {
            r_new->n_tail = n_cur;
        }
        if (j == m - 1) {
            r_new->n_head = n_cur;
        }
    }
}

bool Field::MakeFieldIteration() {
    bool was_change = 0;
    Row* r_cur = r_tail;
    uint64_t i = 0;
    while (true) {
        uint64_t j = 0;
        Node* n_cur = r_cur->n_tail;

        while (true) {
            if (n_cur->x >= 4) {
                was_change = 1;
                uint64_t x = n_cur->x;
                n_cur->x = x % 4;
                if (NodeAdd(i - 1, j, x / 4)) {
                    i++;
                }
                NodeAdd(i + 1, j, x / 4);
                if (NodeAdd(i, j - 1, x / 4)) {
                    j++;
                }
                NodeAdd(i, j + 1, x / 4);
            }
            n_cur = n_cur->n_next;
            j++;

            if (n_cur == nullptr) {
                break;
            }
        }

        r_cur = r_cur->r_next;
        i++;

        if (r_cur == nullptr) {
            break;
        }
    }
    return was_change;
}

void Field::Epoch(input_var inp) {
    uint64_t i = 0;
    uint64_t num = 1;
    BmpOutput(inp.out_path + "0.bmp");
    while (MakeFieldIteration()) {
        if (i >= inp.max_iter) {
            return;
        }
        if (inp.freq != 0 && i % inp.freq == 0) {
            BmpOutput(inp.out_path + std::to_string(num) + ".bmp");
            num++;
        }
        i++;
    }
    if (inp.freq == 0) {
        BmpOutput(inp.out_path + std::to_string(num) + ".bmp");
    }
}
