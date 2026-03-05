cmake_minimum_required(VERSION 3.16)

project(catalog LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(catalog main.cpp
    geo.h input_reader.cpp input_reader.h stat_reader.cpp stat_reader.h transport_catalogue.cpp transport_catalogue.h)

include(GNUInstallDirs)
install(TARGETS catalog
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
