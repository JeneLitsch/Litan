cmake_minimum_required(VERSION 3.13)

add_library(litan_core STATIC
    "Any.cxx"
    "utf8.cxx"
    "reserved_members.cxx"
)

add_subdirectory("file")

target_link_libraries(litan_core PUBLIC litan_config_cxx)