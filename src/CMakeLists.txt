
include_directories(${INCLUDE_DIR})
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -O3")

add_executable(flange main.c)
