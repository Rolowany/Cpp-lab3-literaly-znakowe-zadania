cmake_minimum_required(VERSION 3.20)
project(chrono_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release)
endif()

# GoogleTest: systemowy, a gdy go brak - pobierany (git).
find_package(GTest QUIET)
if(NOT GTest_FOUND)
  message(STATUS "GoogleTest nie znaleziony w systemie - pobieram (FetchContent)")
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
    GIT_SHALLOW    TRUE
  )
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

include(GoogleTest)
enable_testing()

# Dla zadania N powstaje plik wykonywalny <prefix>N = tests/test_zadanieN.cpp
# z nagłówkiem <dir>/zadanieN.hpp (prefix=zadanie, dir=tasks | prefix=rozwiazanie, dir=solutions).
function(add_lab_targets prefix dir)
  foreach(i RANGE 1 5)
    set(target ${prefix}${i})
    add_executable(${target} tests/test_zadanie${i}.cpp)
    target_include_directories(${target} PRIVATE ${dir})
    target_link_libraries(${target} PRIVATE GTest::gtest_main)
    if(MSVC)
      target_compile_options(${target} PRIVATE /W4 /utf-8)
    else()
      target_compile_options(${target} PRIVATE -Wall -Wextra)
    endif()
    gtest_discover_tests(${target}
      TEST_PREFIX "${target}."
      DISCOVERY_MODE PRE_TEST
      PROPERTIES LABELS ${target})
  endforeach()
endfunction()

add_lab_targets(zadanie tasks)

