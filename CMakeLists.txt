cmake_minimum_required(VERSION 3.22)
project(3Lab_C++)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES main.cpp
        ArgumentParser.h
        ArgumentParser.cpp
        ConfigParser.h
        WAVHeader.h
        ReaderWAV.h
        ReaderWAV.cpp
        Converter.h
        Converter.cpp
        WriterWAV.h
        WriterWAV.cpp
        Creators.h
        Creators.cpp
)
add_executable(3Lab_C++ ${SOURCES})
