cmake_minimum_required(VERSION 3.7.0) 
project(main) 

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src") 
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(SOURCES
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/cartes.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES}) 

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED) 

if(SFML_FOUND) 

    message(STATUS "Found SFML")

    include_directories(${SFML_INCLUDE_DIR})

    target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
else()
    message(STATUS "Could not locate SFML") 
endif()
