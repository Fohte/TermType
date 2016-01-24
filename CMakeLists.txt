cmake_minimum_required(VERSION 3.0.0)
project(TermType C)

find_package(CURSES)
INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}")

add_executable(TermType
    src/main.c
    src/menu.c
    src/typing.c
    src/result.c
    src/ir.c
    src/word.c
    src/api.c
    src/csv.c
)
target_link_libraries(TermType ${CURSES_LIBRARY})
