
include_directories(${INCLUDE_DIR})
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "-g -Wall -Wextra -Werror -O3")

add_executable(flange main.c)

install(PROGRAMS flange DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
