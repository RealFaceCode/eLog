cmake_minimum_required(VERSION 3.5)
project(eLogTests VERSION 0.1.0 LANGUAGES C CXX)

add_executable(eLog_logBuilding logBuilding.cxx)
target_compile_options(eLog_logBuilding PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_compile_features(eLog_logBuilding PRIVATE cxx_std_20)
add_test(NAME eLog_logBuilding COMMAND eLog_logBuilding)

