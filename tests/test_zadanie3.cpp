// Testy do zadania 3. NIE MODYFIKUJ tego pliku.
#include <gtest/gtest.h>

#include "zadanie3.hpp"

using namespace zad3;

TEST(Zadanie3_Dlugosc, Napis1011) {
    EXPECT_EQ(dlugosc_napisu_1011(), 2);
}

TEST(Zadanie3_WartoscOsemkowa, Poprawne) {
    EXPECT_EQ(wartosc_osemkowa("7"), 7);
    EXPECT_EQ(wartosc_osemkowa("12"), 10);
    EXPECT_EQ(wartosc_osemkowa("101"), 65);
    EXPECT_EQ(wartosc_osemkowa("0"), 0);
    EXPECT_EQ(wartosc_osemkowa("377"), 255);
}
TEST(Zadanie3_WartoscOsemkowa, Niepoprawne) {
    EXPECT_EQ(wartosc_osemkowa(""), -1);
    EXPECT_EQ(wartosc_osemkowa("8"), -1);
    EXPECT_EQ(wartosc_osemkowa("19"), -1);
    EXPECT_EQ(wartosc_osemkowa("1a"), -1);
    EXPECT_EQ(wartosc_osemkowa("1011"), -1);
}
