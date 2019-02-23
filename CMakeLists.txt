cmake_minimum_required(VERSION 3.12)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler src/main.cpp
        src/Compilador.cpp
        src/Compilador.h
        src/IScanner.h
        src/main.cpp
        src/Scanner.cpp
        src/Scanner.h
        src/ScannerFactory.cpp
        src/ScannerFactory.h
        src/Token.h)