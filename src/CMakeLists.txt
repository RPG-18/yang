include_directories(ui
    core
    parsers)

add_subdirectory(ui)
add_subdirectory(core)
add_subdirectory(parsers)
add_subdirectory(resources)

set(SOURCE_FILES main.cpp
        Utils.h
        Utils.cpp)

set(LIBS ui
         core
         parsers
         resources)

add_executable(yang ${SOURCE_FILES})
target_link_libraries(yang ${LIBS}
                           Qt5::WebEngineWidgets)