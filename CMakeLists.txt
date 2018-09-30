cmake_minimum_required(VERSION 3.1)
project(cryptoquote)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES
        main.cpp
        dictionary.cpp
        quote.cpp
        crypto/letterset.cpp
        crypto/solver.cpp
)
add_executable(cryptoquote ${SOURCE_FILES})
target_link_libraries(cryptoquote pthread)
