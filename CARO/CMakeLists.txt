cmake_minimum_required(VERSION 3.24)
project(CARO CXX C)

if (NOT (${CMAKE_SYSTEM_NAME} STREQUAL "Windows" OR ${CMAKE_SYSTEM_NAME} STREQUAL "Linux"))
    message(FATAL_ERROR "Unsupported platform.")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

set(SOURCE_FILES)
set(MAIN_SOURCE_FILES CARO.cpp)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")

list (APPEND SOURCE_FILES ${MAIN_SOURCE_FILES})

include_directories(${PROJECT_NAME} "include")

set(CMAKE_CXX_FLAGS_DEBUG "-g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_compile_options(-static -static-libgcc -static-libstdc++)
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2main SDL2::SDL2-static)
endif()

if ((${CMAKE_SYSTEM_NAME} STREQUAL "Linux"))
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2 SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer)
endif()

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND bash -c "mkdir -pv ../bin/assets"
    VERBATIM
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND bash -c "cp -ruv ../assets ../bin"
    VERBATIM
)

