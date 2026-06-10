# ASCII Art Generator

Prosty, ale efektowny program konsolowy napisany w C++, który zamienia pliki graficzne (np. PNG, JPG) na sztukę ASCII wyświetlaną bezpośrednio w terminalu. 

## Funkcje
* **Wczytywanie popularnych formatów:** Obsługa plików PNG, JPEG, BMP i innych.
* **Automatyczne skalowanie:** Program dynamicznie zmniejsza obrazki do rozmiaru mieszczącego się w standardowym terminalu (domyślnie szerokość do 100 znaków).
* **Korekta proporcji:** Uwzględnia fakt, że znaki w terminalu nie są idealnymi kwadratami, co zapobiega nienaturalnemu rozciągnięciu obrazu.
* **Wbudowana pomoc:** Opcja wyświetlenia instrukcji bezpośrednio w aplikacji.

## Wykorzystane technologie i biblioteki
Projekt wykorzystuje nowoczesne standardy i sprawdzone rozwiązania:
* **C++17**
* **CMake** – system budowania ułatwiający kompilację na różnych platformach.
* **stb_image** (`stb_image.h`) – świetna, jednoplikowa biblioteka niestandardowa typu "header-only" autorstwa Seana Barretta. Służy do bezproblemowego dekodowania plików graficznych bez konieczności skomplikowanego linkowania zewnętrznych zależności.

---

## Jak skompilować projekt?

Dzięki użyciu CMake, kompilacja jest prosta i uniwersalna dla różnych systemów operacyjnych. Wymagane jest posiadanie zainstalowanego kompilatora C++ oraz programu CMake.

1. Otwórz terminal w głównym folderze projektu (tam gdzie znajduje się ten plik README).
2. Utwórz folder do budowania i wejdź do niego:
   ```bash
   mkdir build
   cd build
   ```
3. Wygeneruj pliki konfiguracyjne:
   ```bash
   cmake ..
   ```
4. Skompiluj program:
   ```bash
   cmake --build .
   ```

---

## Jak używać programu?

Program uruchamia się z wiersza poleceń, podając ścieżkę do obrazka jako argument. Będąc w folderze `build`, użyj poniższych komend.

**Przetworzenie obrazka:**
```bash
# Na systemach Linux/macOS:
./ascii_generator ../sciezka/do/obrazka.png

# Na systemach Windows (zależnie od kompilatora):
Debug\ascii_generator.exe ..\sciezka\do\obrazka.png
```

**Wyświetlenie pomocy (dostępne flagi):**
Aby dowiedzieć się, jak używać programu, możesz wywołać wbudowany ekran pomocy:
```bash
./ascii_generator -h
# lub
./ascii_generator --help
```

---


