#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void print_help() {
    std::cout << "=========================================\n";
    std::cout << "          ASCII ART GENERATOR            \n";
    std::cout << "=========================================\n";
    std::cout << "Program zamienia pliki graficzne na sztuke ASCII.\n\n";
    std::cout << "Uzycie:\n";
    std::cout << "  ./ascii_generator <sciezka_do_pliku>\n\n";
    std::cout << "Opcje:\n";
    std::cout << "  -h, --help    Wyswietla ten ekran pomocy.\n";
    std::cout << "=========================================\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Blad: Nie podano pliku wejsciowego.\n";
        std::cerr << "Uzyj: ./ascii_generator -h aby uzyskac pomoc.\n";
        return 1;
    }

    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help") {
        print_help();
        return 0;
    }

    const char* filepath = argv[1];
    int width, height, channels;

    unsigned char* img_data = stbi_load(filepath, &width, &height, &channels, 3);

    if (img_data == nullptr) {
        std::cerr << "Blad: Nie udalo sie wczytac pliku: " << filepath << '\n';
        std::cerr << "Powod z biblioteki stb: " << stbi_failure_reason() << '\n';
        return 1;
    }

    const std::string ascii_chars = ".:-=+*#%@"; //

    int target_width = 100;

    if (width < target_width) {
        target_width = width;
    }

    int target_height = (height * target_width / (double)width) * 0.5;

    for (int y = 0; y < target_height; y++) {
        for (int x = 0; x < target_width; x++) {

            int orig_x = x * width / target_width;
            int orig_y = y * height / target_height;

            int pixel_index = (orig_y * width + orig_x) * 3;

            unsigned char r = img_data[pixel_index];
            unsigned char g = img_data[pixel_index + 1];
            unsigned char b = img_data[pixel_index + 2];

            int luminance = (0.299 * r) + (0.587 * g) + (0.114 * b);

            int char_index = luminance * (ascii_chars.length() - 1) / 255;

            std::cout << ascii_chars[char_index];
        }
        std::cout << '\n';
    }

    stbi_image_free(img_data);

    return 0;
}