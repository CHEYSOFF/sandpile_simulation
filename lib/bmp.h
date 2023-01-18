#pragma once
#include <iostream>
#include <string>
#include <vector>

struct Color {
    unsigned char r, g, b;

    Color();
    Color(unsigned char r, unsigned char g, unsigned char b);
};

class Image {
   public:
    Image(uint64_t width, uint64_t height);

    Color GetColor(uint64_t j, uint64_t i) const;
    void SetColor(const Color& color, uint64_t j, uint64_t i);

    bool Export(const std::string &path);

   private:
    uint64_t width;
    uint64_t height;
    std::vector<Color> colors;
};
