cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(../External/googletest ${CMAKE_CURRENT_BINARY_DIR}/googleTestBuild)

include_directories(${gtesr_SOURCE_DIR}/include)

file(GLOB_RECURSE TEST_SRC_FILES
        ./*.cpp
        ./*.h
        )

add_executable(pomodoroTests ${TEST_SRC_FILES} ${SOURCE_FILES})
target_compile_definitions(pomodoroTests PUBLIC RUNNING_POMODORO_TESTS)

target_link_libraries(pomodoroTests gtest gtest_main ${NOTIFICATION_IMPLEMENTATION} Qt5::Widgets)