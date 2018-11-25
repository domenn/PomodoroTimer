cmake_minimum_required(VERSION 3.12)
project(PomodoroTimer)

set(CMAKE_CXX_STANDARD 17)

# Find includes in corresponding build directories
# set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
include_directories(. External/cpplogger/include)
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
# set(CMAKE_AUTOUIC ON)

# The method below isn't very fast. I don't relly like.
#include(ExternalProject)
#ExternalProject_Add(
#        cpplogger
#        PREFIX cpplogger
#        GIT_REPOSITORY https://github.com/SergiusTheBest/plog.git
#        GIT_TAG tags/1.1.4
#        CONFIGURE_COMMAND ""
#        BUILD_COMMAND ""
#        INSTALL_COMMAND ""
#        SOURCE_DIR ${CMAKE_SOURCE_DIR}/External/cpplogger
#        LOG_DOWNLOAD ON
#)
#add_dependencies(PomodoroTimer cpplogger)
#
#ExternalProject_Get_Property(cpplogger source_dir)
#message("CppLogger sources at ${source_dir}")
#include_directories(${source_dir}/include)

# Find the QtWidgets library

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.11.2\\msvc2017_64\\")
endif ()

find_package(Qt5Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources
file(GLOB_RECURSE SOURCE_FILES
        ./PomodoroTimerApp/*.cpp
        ./PomodoroTimerApp/*.h
        )

#message(WARNING "${SOURCE_FILES}")

list(FILTER SOURCE_FILES EXCLUDE REGEX ".*main.cpp$")
#message(WARNING "${SOURCE_FILES}")

add_subdirectory(./PomodoroTimerAppTest)

add_executable(PomodoroTimer PomodoroTimerApp/main.cpp ${SOURCE_FILES})
target_link_libraries(PomodoroTimer Qt5::Widgets)
