cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

project(
  c_text_rpg
  DESCRIPTION "Text RPG written in C"
  HOMEPAGE_URL https://github.com/KN13KOMETA/c_text_rpg
  LANGUAGES C
)

include("cmake/version.cmake")

# Force CMake to use c99 instead of gnu99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(
  ${PROJECT_NAME}
  src/main.c
  src/functions.c
  src/location/location.c
  src/character/character.c
  src/character/weapon.c
  src/story/story.c
)

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES OUTPUT_NAME "${PROJECT_NAME}_${PROJECT_FULL_VERSION}"
)

# Turning on every compiler checks
target_compile_options(
  ${PROJECT_NAME}
  PUBLIC -xc -Wall -Wextra -Wpedantic $<$<CONFIG:RELEASE>:-Werror>
)

target_compile_definitions(
  ${PROJECT_NAME}
  PUBLIC
    PROJECT_NAME=\"${PROJECT_NAME}\"
    PROJECT_FULL_VERSION=\"${PROJECT_FULL_VERSION}\"
    PROJECT_VERSION=\"${PROJECT_FULL_VERSION}\"
    COMMIT_SHORT_HASH=\"\"
    $<$<CONFIG:DEBUG>:DEBUG>
)

get_property(
  TARGET_COMPILE_OPTS
  TARGET ${PROJECT_NAME}
  PROPERTY COMPILE_OPTIONS
)
message(STATUS "Compile options for my_target: ${TARGET_COMPILE_OPTS}")

include("cmake/target/todo.cmake")
