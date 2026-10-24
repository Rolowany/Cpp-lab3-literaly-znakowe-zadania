#pragma once

#include <string>

namespace zad5 {

    // TODO 1: wartość cyfry szesnastkowej:
    //         '0'..'9' -> 0..9,  'a'..'f' i 'A'..'F' -> 10..15,
    //         każdy inny znak -> -1.
    //         Wskazówka: c - '0'  oraz  c - 'a' + 10.
    inline int cyfra_hex(char c) {
        return '0';
    }

    // TODO 2: zamień napis szesnastkowy na liczbę (wagi: 1, 16, 256, ...).
    //         "ff" -> 255, "1A3" -> 419
    //         Zwróć -1, gdy napis jest pusty lub zawiera niepoprawny znak.
    //         Wskazówka: wynik = wynik * 16 + cyfra.
    inline int hex_na_liczbe(const std::string& tekst) {
        return 0;
    }

    // TODO 3: operacja odwrotna do TODO 1: liczba 0..15 -> znak
    //         ('0'..'9', potem MAŁE litery 'a'..'f').
    //         Dla liczby spoza 0..15 zwróć '?'.
    //         Wskazówka: '0' + v  oraz  'a' + (v - 10), pamiętaj o static_cast<char>.
    inline char liczba_na_cyfre_hex(int v) {
        return '0';
    }
} // namespace zad5
