cmake_minimum_required(VERSION 3.10)
project(game)

set(CMAKE_CXX_STANDARD 14)

# Add include directories
include_directories(include/entity)
include_directories(include/gameplay)
include_directories(include/item)
include_directories(include/lib)
include_directories(include/map)
include_directories(include/rendering)
include_directories(include/ui)
include_directories(include/utils)

# Add source files
file(GLOB SOURCES "src/entity/*.cpp" "src/gameplay/*.cpp" "src/item/*.cpp" "src/map/*.cpp" "src/rendering/*.cpp" "src/ui/*.cpp" "src/utils/*.cpp" "src/main.cpp")

add_executable(game ${SOURCES})

# Link libraries
target_link_libraries(game sfml-graphics sfml-window sfml-system sfml-audio)

# Custom targets
add_custom_target(run
    COMMAND ./game
    DEPENDS  game 
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(clear
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(valgrind
    COMMAND valgrind --leak-check=full --suppressions=../.valgrind.supp --track-origins=yes $<TARGET_FILE:${PROJECT_NAME}>
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)