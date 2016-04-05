set(CORE_SOURCE_FILES
        Row.h
        Row.cpp
        Size.h
        Size.cpp
        Column.h
        Column.cpp
        Crossword.h
        Crossword.cpp
)        

add_library(core ${CORE_SOURCE_FILES})
target_link_libraries(core Qt5::Core)