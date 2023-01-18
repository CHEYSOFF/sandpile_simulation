#pragma once
#include "bmp.h"

#include <fstream>
#include <iostream>
#include <string>

Color::Color()
    : r(0), g(0), b(0) {}


Color::Color(unsigned char r, unsigned char g, unsigned char b)
    : r(r), g(g), b(b) {}

Image::Image(uint64_t width, uint64_t height)
    : width(width), height(height), colors(std::vector<Color>(width * height)) {}

Color Image::GetColor(uint64_t j, uint64_t i) const {
    return colors[i * width + j];
}

void Image::SetColor(const Color& color, uint64_t j, uint64_t i) {
    colors[i * width + j].r = color.r;
    colors[i * width + j].g = color.g;
    colors[i * width + j].b = color.b;
}

bool Image::Export(const std::string &path) {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        return 0;
    }

    unsigned char bmp_pad[3] = {0, 0, 0};
    const int padding_ammount = ((4 - (width * 3) % 4) % 4);

    const int file_header_size = 14;
    const int information_header_size = 40;
    const int file_size = file_header_size + information_header_size +
                          width * height + padding_ammount * height;

    unsigned char file_header[file_header_size];

    // file type
    file_header[0] = 'B';
    file_header[1] = 'M';
    // file size
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;
    // reserved 1 (not used)
    file_header[6] = 0;
    file_header[7] = 0;
    // reserved 2 (not used)
    file_header[8] = 0;
    file_header[9] = 0;
    // pixel data offset
    file_header[10] = file_header_size + information_header_size;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;

    unsigned char information_header[information_header_size];

    // header size
    information_header[0] = information_header_size;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;
    // image width
    information_header[4] = width;
    information_header[5] = width >> 8;
    information_header[6] = width >> 16;
    information_header[7] = width >> 24;
    // image height
    information_header[8] = height;
    information_header[9] = height >> 8;
    information_header[10] = height >> 16;
    information_header[11] = height >> 24;
    // planes
    information_header[12] = 1;
    information_header[13] = 0;
    // bits per pixel (RGB)
    information_header[14] = 24;
    information_header[15] = 0;
    // compression (no compression)
    information_header[16] = 0;
    information_header[17] = 0;
    information_header[18] = 0;
    information_header[19] = 0;
    // image size (no compression)
    information_header[20] = 0;
    information_header[21] = 0;
    information_header[22] = 0;
    information_header[23] = 0;
    // X pixels per meter (not specified)
    information_header[24] = 0;
    information_header[25] = 0;
    information_header[26] = 0;
    information_header[27] = 0;
    // Y pixels per meter (not specified)
    information_header[28] = 0;
    information_header[29] = 0;
    information_header[30] = 0;
    information_header[31] = 0;
    // total colors (color pallete not used)
    information_header[32] = 0;
    information_header[33] = 0;
    information_header[34] = 0;
    information_header[35] = 0;
    // important colors (generally ignored)
    information_header[36] = 0;
    information_header[37] = 0;
    information_header[38] = 0;
    information_header[39] = 0;

    f.write(reinterpret_cast<char*>(file_header), file_header_size);
    f.write(reinterpret_cast<char*>(information_header), information_header_size);
    for (uint64_t i = 0; i < height; i++) {
        for (uint64_t j = 0; j < width; j++) {
            unsigned char r = GetColor(j, i).r;
            unsigned char g = GetColor(j, i).g;
            unsigned char b = GetColor(j, i).b;

            unsigned char color[] = {b, g, r};

            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmp_pad), padding_ammount);
    }

    return 1;
}
