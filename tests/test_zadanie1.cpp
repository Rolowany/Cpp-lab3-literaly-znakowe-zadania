// Testy do zadania 1. NIE MODYFIKUJ tego pliku.
#include <gtest/gtest.h>

#include "zadanie1.hpp"

using namespace zad1;

TEST(Zadanie1_KodZnaku, Litery) {
    EXPECT_EQ(kod_znaku('A'), 65);
    EXPECT_EQ(kod_znaku('a'), 97);
}
TEST(Zadanie1_KodZnaku, CyfryISpecjalne) {
    EXPECT_EQ(kod_znaku('0'), 48);
    EXPECT_EQ(kod_znaku(' '), 32);
    EXPECT_EQ(kod_znaku('\n'), 10);
    EXPECT_EQ(kod_znaku('\0'), 0);
}

TEST(Zadanie1_NastepnyZnak, Litery) {
    EXPECT_EQ(nastepny_znak('A'), 'B');
    EXPECT_EQ(nastepny_znak('m'), 'n');
}
TEST(Zadanie1_NastepnyZnak, CyfryISpecjalne) {
    EXPECT_EQ(nastepny_znak('0'), '1');
    EXPECT_EQ(nastepny_znak('z'), '{');
}

TEST(Zadanie1_Odleglosc, Dodatnia) {
    EXPECT_EQ(odleglosc('a', 'e'), 4);
    EXPECT_EQ(odleglosc('0', '9'), 9);
}
TEST(Zadanie1_Odleglosc, ZeroIUjemna) {
    EXPECT_EQ(odleglosc('A', 'A'), 0);
    EXPECT_EQ(odleglosc('e', 'a'), -4);
}
TEST(Zadanie1_Odleglosc, WielkaMalaLitera) {
    EXPECT_EQ(odleglosc('A', 'a'), 32);
}
