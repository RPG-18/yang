configure_file(config.h.in config.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(TestGumbo TestGumbo.cpp)
target_link_libraries(TestGumbo parsers gtest gtest_main)

add_executable(TestNonogramsParser TestNonogramsParser.cpp)
target_link_libraries(TestNonogramsParser parsers gtest gtest_main)


add_test(NAME Test_Gumbo_Wrapper COMMAND TestGumbo)
add_test(NAME Test_Crossword_Parser COMMAND TestNonogramsParser)