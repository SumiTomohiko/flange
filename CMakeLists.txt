
project(flange)
cmake_minimum_required(VERSION 2.8)

set(FLANGE_VERSION \"1.0.0dev1\")

set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
configure_file(${INCLUDE_DIR}/flange/config.h.in ${INCLUDE_DIR}/flange/config.h)

subdirs(src tests)
