# Zadania lab 3


## Uruchomienie

Wymagania: CMake >= 3.20, GCC 13+ / Clang 16+ / MSVC 19.29+, git i internet przy pierwszej
konfiguracji (CMake pobiera GoogleTest). Zadanie 5 wymaga też `tzdata` (Linux).

```bash
cmake -S . -B build
cmake --build build
```

## Testy

```bash
./build/zadanie1                                         # testy zadania 1 (analogicznie 2-5)
./build/zadanie3 --gtest_filter='Zadanie3_AddMonths.*'   # tylko wybrane testy
cd build && ctest -L zadanie --output-on-failure         # wszystkie zadania
```

Windows: `cmake --build build --config Release`, pliki w `build\Release\`, `ctest -C Release -L zadanie`.
