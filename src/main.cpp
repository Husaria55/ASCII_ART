#include <iostream>
#include <string>

// To makro musi znajdować się dokładnie w jednym pliku .cpp przed inkludowaniem nagłówka.
// Sprawia, że plik stb_image.h zachowuje się jak skompilowana biblioteka.
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Funkcja pomocnicza wyświetlająca instrukcję użytkowania programu
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
    // 1. Obsługa argumentów wiersza poleceń
    // Jeśli nie podano żadnego argumentu (argc == 1, bo argv[0] to nazwa programu)
    if (argc < 2) {
        std::cerr << "Blad: Nie podano pliku wejsciowego.\n";
        std::cerr << "Uzyj: ./ascii_generator -h aby uzyskac pomoc.\n";
        return 1;
    }

    // Jeśli podano flagę pomocy
    std::string arg = argv[1];
    if (arg == "-h" || arg == "--help") {
        print_help();
        return 0; // Zamykamy program po wyświetleniu pomocy
    }

    // 2. Ładowanie pliku graficznego
    const char* filepath = argv[1];
    int width, height, channels;

    // Wczytujemy obrazek. '3' na końcu wymusza format RGB (Red, Green, Blue)
    unsigned char* img_data = stbi_load(filepath, &width, &height, &channels, 3);

    // Weryfikacja, czy plik istnieje i ma poprawny format
    if (img_data == nullptr) {
        std::cerr << "Blad: Nie udalo sie wczytac pliku: " << filepath << '\n';
        std::cerr << "Powod z biblioteki stb: " << stbi_failure_reason() << '\n';
        return 1;
    }

    // 3. Paleta znaków ASCII - od najciemniejszego do najjaśniejszego
    // Uwaga: Jeśli masz jasne tło terminala, obrazek może wyjść w "negatywie".
    // Wtedy zmień kolejność na: "@%#*+=-:. "
    // 3. Paleta znaków ASCII
    const std::string ascii_chars = " .:-=+*#%@";

    // --- NOWY KOD: Normalizacja / Skalowanie ---
    // Definiujemy maksymalną szerokość, która bezpiecznie zmieści się w terminalu
    int target_width = 100;

    // Jeśli obrazek jest mniejszy niż target_width, nie powiększamy go na siłę
    if (width < target_width) {
        target_width = width;
    }

    // Obliczamy docelową wysokość z zachowaniem oryginalnych proporcji obrazka.
    // Mnożymy to dodatkowo przez 0.5, ponieważ znak w terminalu nie jest kwadratem,
    // a prostokątem (zazwyczaj jest ok. 2 razy wyższy niż szerszy).
    int target_height = (height * target_width / (double)width) * 0.5;

    // 4. Przetwarzanie i wyświetlanie obrazka
    for (int y = 0; y < target_height; y++) {
        for (int x = 0; x < target_width; x++) {

            // Mapujemy współrzędne z "nowego", małego wymiaru na oryginalne piksele
            int orig_x = x * width / target_width;
            int orig_y = y * height / target_height;

            // Obliczamy indeks piksela z oryginalnego obrazu (mnożymy razy 3, bo RGB)
            int pixel_index = (orig_y * width + orig_x) * 3;

            unsigned char r = img_data[pixel_index];
            unsigned char g = img_data[pixel_index + 1];
            unsigned char b = img_data[pixel_index + 2];

            // Obliczamy jasność
            int luminance = (0.299 * r) + (0.587 * g) + (0.114 * b);

            // Mapujemy jasność na indeks w palecie znaków
            int char_index = luminance * (ascii_chars.length() - 1) / 255;

            std::cout << ascii_chars[char_index];
        }
        std::cout << '\n';
    }

    // 5. Zwalnianie pamięci
    stbi_image_free(img_data);

    return 0;
}