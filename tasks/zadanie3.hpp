#pragma once

#include <sstream>
#include <string>

namespace zad3 {
    // TODO 1: ile znaków ma napis "\1011"?
    //         Zanim zrobisz przy użyciu dedykowanej funkcji (jakiej?) spróbuj zgadnąć
    //         Wskazówka: kod ósemkowy kończy się po 3 cyfrach.
    inline int dlugosc_napisu_1011() {
        return 0;
    }

    // TODO 2: zamień kod ósemkowy zapisany jako napis cyfr (np. "101")
    //         na liczbę. Wagi pozycji: 1, 8, 64.
    //         "7" -> 7, "12" -> 10, "101" -> 65
    //         Zwróć -1, gdy: napis jest pusty, ma więcej niż 3 cyfry
    //         albo zawiera znak spoza '0'..'7'.
    inline int wartosc_osemkowa(const std::string& cyfry) {
        return 0;
    }
} // namespace zad3
