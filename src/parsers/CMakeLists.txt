file(GLOB PARSERS_SOURCE_FILES
        "*.h"
        "*.hpp"
        "*.cpp"
) 
add_library(parsers ${PARSERS_SOURCE_FILES})
target_link_libraries(parsers gumbo-parser Qt5::Core)