#pragma once

namespace zad1 {

    // TODO 1: jaki jest kod liczbowy znaku `c`?

    inline int kod_znaku(char c) {
        return static_cast<int>(c);
    }

    // TODO 2: zwróć znak o kodzie o 1 większym niż `c` (z 'A' zrób 'B').

    inline char nastepny_znak(char c) {
        return '0';
    }

    // TODO 3: ile pozycji dzieli `a` od `b` w tabeli kodów? (b - a, może być ujemne)
    //         np. odleglosc('a', 'e') == 4, odleglosc('e', 'a') == -4
    inline int odleglosc(char a, char b) {
        return 0;
    }
} // namespace zad1
