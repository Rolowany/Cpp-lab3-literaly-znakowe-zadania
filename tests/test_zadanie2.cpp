// Testy do zadania 2. NIE MODYFIKUJ tego pliku.
#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "zadanie2.hpp"

using namespace zad2;

TEST(Zadanie2_Tabelka, Calosc) {
    EXPECT_EQ(tabelka(), "Znak\tNazwa\n'\tapostrof\n\"\tcudzyslow\n\\\tukosnik\n");
}
TEST(Zadanie2_Tabelka, LiczbaLiniiITabulatorow) {
    const std::string t = tabelka();
    EXPECT_EQ(std::count(t.begin(), t.end(), '\n'), 4);
    EXPECT_EQ(std::count(t.begin(), t.end(), '\t'), 4);
}

TEST(Zadanie2_SciezkaWindows, Tresc) {
    EXPECT_EQ(sciezka_windows(), "C:\\Users\\student");
}
TEST(Zadanie2_SciezkaWindows, Dlugosc) {
    EXPECT_EQ(sciezka_windows().size(), 16u);
}

TEST(Zadanie2_AbcHex, Tresc) {
    EXPECT_EQ(abc_hex(), "ABC");
}
TEST(Zadanie2_AbcHex, Dlugosc) {
    EXPECT_EQ(abc_hex().size(), 3u);
}
