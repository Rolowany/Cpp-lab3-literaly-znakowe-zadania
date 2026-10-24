#pragma once

#include <string>

namespace zad4 {

    struct Statystyka {
        int wielkie = 0;
        int male = 0;
        int cyfry = 0;
        int spacje = 0;
    };

    // Wszystkie funkcje poniżej mają używać WYŁĄCZNIE porównań z literałami
    // znakowymi ('a', 'z', 'A', 'Z', '0', '9', ' '). Bez <cctype>!
    // Tekst zawiera tylko znaki ASCII.

    // Wskazówka do zadań: spróbuj użyć count_if
    // TODO 1: ile cyfr ('0'..'9') jest w `tekst`?
    inline int ile_cyfr(const std::string& tekst) {
        return 0;
    }

    // TODO 2: ile liter (małych i wielkich, 'a'..'z' i 'A'..'Z') jest w `tekst`?
    inline int ile_liter(const std::string& tekst) {
        return 0;
    }

    // TODO 3: policz wielkie litery, małe litery, cyfry i spacje jednocześnie
    inline Statystyka policz(const std::string& tekst) {
        return {};
    }
} // namespace zad4
