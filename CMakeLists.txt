cmake_minimum_required(VERSION 3.10)
project(QRcode)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -Wall")


include_directories(include)
include_directories("C:/Dev/msys64/mingw64/include")
link_directories("C:/Dev/msys64/mingw64/include/gtk-4.0")

# Add the source files
set(SOURCES
    src/main.c
    src/qrcodegen.c
)

add_library(qrcodegen STATIC src/qrcodegen.c)
target_include_directories(qrcodegen PUBLIC ./include)

add_executable(QRcode src/main.c)
target_link_libraries(QRcode PRIVATE PkgConfig::GTK4 qrcodegen)
