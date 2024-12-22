cmake_minimum_required(VERSION 3.13)

add_library(libltn 
    "Any.cxx"
    "reserved_members.cxx"
)

add_subdirectory("file")