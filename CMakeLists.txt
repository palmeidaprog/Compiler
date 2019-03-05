cmake_minimum_required(VERSION 3.12)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler src/main.cpp
        src/Compilador.h
        src/Compilador.cpp
        src/IScanner.h
        src/Scanner.h
        src/Scanner.cpp
        src/ScannerFactory.h
        src/ScannerFactory.cpp
        src/ScannerException.h
        src/ScannerException.cpp
        src/Token.h
        src/Token.cpp)