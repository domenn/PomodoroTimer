#pragma clang diagnostic push
// Tests use top level macro, probably global variables. We suppress compiler warnings.
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by domen on 23. 11. 2018.
//

#pragma once

#include "gtest/gtest.h"
#include "../PomodoroTimerApp/utils/PomodoroAppCommandLine.h"
#include <QApplication>


TEST(cmdLineParser, isStopwatch)
{
//    constexpr char const * const app = "app";
//    constexpr char const * const stopwatch = "--stopwatch";

    // Note: string literal to char* conversion invalid in C++ ... but works with explicit cast
    char* argv1[]{(char *)"app", (char *)"--stopwatch"};
    int argc = 2;

    QApplication a(argc, argv1);
    PomodoroAppCommandLine cmdLine(&a);
    ASSERT_TRUE(cmdLine.isStopwatchMode);
}

TEST(cmdLineParser, isNotStopwatch)
{
    char* argv1[]{(char *)"app"};
    int argc = 1;

    QApplication a(argc, argv1);
    PomodoroAppCommandLine cmdLine(&a);
    ASSERT_FALSE(cmdLine.isStopwatchMode);
}
#pragma clang diagnostic pop