cmake_minimum_required(VERSION 3.12)
project(Compiler)

set(CMAKE_CXX_STANDARD 14)

add_executable(Compiler src/main.cpp
        src/Compilador.h
        src/Compilador.cpp
        src/ScannerReturn.h
        src/ScannerReturn.cpp
        src/IScanner.h
        src/IParser.h
        src/ParserFactory.h
        src/ParserFactory.cpp
        src/Scanner.h
        src/Scanner.cpp
        src/ScannerFactory.h
        src/ScannerFactory.cpp
        src/ScannerException.h
        src/ScannerException.cpp
        src/Token.h
        src/Token.cpp src/Parser.cpp src/Parser.h src/ParserException.cpp src/ParserException.h)