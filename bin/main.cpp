#include <iostream>
#include <string>
#include <vector>

#include "../lib/node.cpp"
#include "../lib/row.cpp"
#include "../lib/field.cpp"
#include "../lib/bmp.cpp"
#include "../lib/flags.cpp"
#include "../lib/read.cpp"

// EXAMPLE of programm usage
// main.exe --length=1 --width=1 --input=../test.txt --output=../out4/new --max-iter=100000000 --freq=1
// cd Desktop/code/itmo/op/lab3/labwork-3-CHEYSOFF/bin
int main(int argc, char** argv) {
    input_var inp;
    ReadFlags(inp, argc, argv);
    std::vector<std::vector<uint64_t>> sand_field(inp.n, std::vector<uint64_t>(inp.m, 0));
    if (TSVRead(sand_field, inp.in_path) == 0) {
        std::cerr << "File adress is incorrect or file is corrupted\n";
        return 1;
    }

    Field* f = From2DArray(sand_field);
    f->Epoch(inp);
}
