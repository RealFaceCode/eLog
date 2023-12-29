cmake_minimum_required(VERSION 3.5)
project(eLogTests VERSION 0.1.0 LANGUAGES C CXX)

add_executable(eLog_logBuilding logBuilding.cxx)
target_compile_features(eLog_logBuilding PRIVATE cxx_std_20)
add_test(NAME eLog_logBuilding COMMAND eLog_logBuilding)

add_executable(fmt_isContainer isContainer.cxx)
target_compile_features(fmt_isContainer PRIVATE cxx_std_20)
add_test(NAME fmt_isContainer COMMAND fmt_isContainer)

add_executable(fmt_containsChas containsChar.cxx)
target_compile_features(fmt_containsChas PRIVATE cxx_std_20)
add_test(NAME fmt_containsChas COMMAND fmt_containsChas)

add_executable(fmt_simple fmtSimple.cxx)
target_compile_features(fmt_simple PRIVATE cxx_std_20)
add_test(NAME fmt_simple COMMAND fmt_simple)

add_executable(fmt_precision fmtPrecision.cxx)
target_compile_features(fmt_precision PRIVATE cxx_std_20)
add_test(NAME fmt_precision COMMAND fmt_precision)

add_executable(fmt_alignment fmtAlignment.cxx)
target_compile_features(fmt_alignment PRIVATE cxx_std_20)
add_test(NAME fmt_alignment COMMAND fmt_alignment)

add_executable(fmt_complex fmtComplex.cxx)
target_compile_features(fmt_complex PRIVATE cxx_std_20)
add_test(NAME fmt_complex COMMAND fmt_complex)