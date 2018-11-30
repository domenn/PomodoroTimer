//
// Created by domen on 23. 11. 2018.
//
#pragma once

class QApplication;
#include <QtCore/QCommandLineParser>

class PomodoroAppCommandLine {

    QCommandLineOption *const stopwatchModeOption;
    QCommandLineParser *const parser;

    QCommandLineParser * handleCommandLineArguments(QApplication *application);

public:
    bool const isStopwatchMode;

    explicit PomodoroAppCommandLine(QApplication * app);
};


