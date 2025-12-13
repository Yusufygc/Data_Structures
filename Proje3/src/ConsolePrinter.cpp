#include "ConsolePrinter.hpp"
#include <cstdlib> // system için
#include <iostream>

void ConsolePrinter::clearScreen()
{
    // Windows ortamı kontrolü
    #ifdef _WIN32
        // Ekrana boş satır basmak yerine doğrudan ekranı temizleyen komut
        std::system("cls");
    #else
        // Linux/Mac ortamları için (Proje MinGW olsa da standart kalsın)
        std::system("clear");
    #endif
}