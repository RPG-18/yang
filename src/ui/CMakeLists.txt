file(GLOB UI_SOURCE_FILES
    "*.h"
    "*.cpp"
) 
add_library(ui ${UI_SOURCE_FILES})
target_link_libraries(ui Qt5::Qml parsers)