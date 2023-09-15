cmake_minimum_required(VERSION 3.7.0) # version minimal de cmake
project(main) # nom du projet

set(CMAKE_CXX_STANDARD 17) # la norme c++17 utilisée afin de compiler le projet
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}") # Stock le fichier CMakeLists.txt
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Ajout des fichiers sources 
set(SOURCES
    "${SRC_DIR}/main.cpp"
   
)

add_executable(${PROJECT_NAME} ${SOURCES}) # ajout d'un executable avec le nom du projet


find_package(SDL2) # recherche la bibliothèques SDL2

if(SDL2_FOUND) # on vérifie si SDL2 est trouvée

    message(STATUS "Found SDL2")

    # Spécifie les répertoires d'inclusion pour la cible
    target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})

    # Spécifie les bibliothèques à lier avec la cible
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
else()
    message(STATUS "Could not locate SDL2") 
endif()
