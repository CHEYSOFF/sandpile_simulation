#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool TSVRead(std::vector<std::vector<uint64_t> >& v, std::string in_path) {
    std::ifstream txt_file(in_path, std::ios::binary);
    if (!txt_file) {
        return 0;
    }
    uint64_t nu = 0;
    uint64_t tmp;
    int x, y;
    while (true) {
        if (txt_file.eof()) {
            break;
        }
        txt_file >> x;
        txt_file >> y;
        txt_file >> tmp;
        x--;
        y--;
        v[x][y] = tmp;
    }
    return 1;
}
