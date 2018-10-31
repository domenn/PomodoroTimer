cmake_minimum_required(VERSION 3.12)
project(PomodoroTimer)

set(CMAKE_CXX_STANDARD 17)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
 set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
 set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources

file(GLOB_RECURSE SOURCE_FILES
        ./PomodoroTimerApp/*.cpp
        ./PomodoroTimerApp/*.h
        )

file(GLOB_RECURSE SOURCE_FILES1
        ./ExampleFromOnline/*.cpp
        ./ExampleFromOnline/*.h
        )

add_executable(PomodoroTimer ${SOURCE_FILES})
target_link_libraries(PomodoroTimer Qt5::Widgets)

add_executable(ExampleFromOnline ${SOURCE_FILES1})
target_link_libraries(ExampleFromOnline Qt5::Widgets)