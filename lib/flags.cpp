#pragma once
#include <cstring>
#include <iostream>
#include <string>

struct input_var {
    int n = 0;
    int m = 0;
    std::string in_path = "../test.txt";
    std::string out_path = "";
    uint64_t max_iter = 0;
    uint64_t freq = 1;
};

char *ArgumentValue(char *argument) {
    int begining = 0;

    while (argument[begining] != '=') {
        if (begining >= strlen(argument) - 1) {
            return 0;
        }
        begining++;
    }
    begining++;

    while (isspace(argument[begining])) {
        begining++;
    }

    return argument + begining;
}

void FlagInput(input_var &inp, char *argument) {
    char *new_argument = ArgumentValue(argument);
    // checking if we have undefined flag
    if(new_argument == 0){
        return;
    }

    switch (argument[0]) {
        case 'l':
            inp.n = std::stoi(new_argument);
            break;
        case 'w':
            inp.m = std::stoi(new_argument);
            break;
        case 'i':
            inp.in_path = new_argument;
            break;
        case 'o':
            inp.out_path = new_argument;
            break;
        case 'm':
            inp.max_iter = std::stoi(new_argument);
            break;
        case 'f':
            inp.freq = std::stoi(new_argument);
            break;

        default:
            break;
    }
}

void ReadFlags(input_var &inp, int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        if (strlen(argv[i]) > 1 && argv[i][1] == '-') {
            FlagInput(inp, &argv[i][2]);
        } else {
            FlagInput(inp, &argv[i][1]);
        }
    }
}
