cmake_minimum_required(VERSION 3.7.0)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(MAP_DIR "map")
set(MAP_SOURCE "${MAP_DIR}/createmap.cpp")
add_executable(MAP ${MAP_SOURCE})

file(GLOB SOURCES
    "${SRC_DIR}/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)  # <-- Ajout de 'audio'

if(SFML_FOUND)
    message(STATUS "Found SFML")
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)  # <-- Ajout de 'sfml-audio'
else()
    message(STATUS "Could not locate SFML")
endif()
    

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

if(SFML_FOUND)
    message(STATUS "Found SFML")
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system )
else()
    message(STATUS "Could not locate SFML")
endif()

# Génération de la documentation avec Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    message(STATUS "Found DOXYGEN")
    set(DOXYGEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile)
    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM
    )
else()
    message(WARNING "Doxygen not found. Documentation will not be generated.")
endif()

# Ajout des commandes pour effacer le build et lancer le programme
add_custom_target(run
    COMMAND ./game
    DEPENDS game
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(clear
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(map
    COMMAND MAP
    DEPENDS MAP
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
