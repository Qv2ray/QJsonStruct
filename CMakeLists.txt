cmake_minimum_required(VERSION 3.5)

project(QJsonStruct LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTING ON)

include(QJsonStruct.cmake)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(main main.cpp header.hpp QJsonStruct.hpp QJsonIO.hpp macroexpansion.hpp JsonConvertMacros.hpp QJsonStructBase.hpp ConstructorMacros.hpp CompareMacros.hpp)

target_link_libraries(main Qt5::Core)

if(BUILD_TESTING)
    include(CTest)
    add_subdirectory(test)
endif()
