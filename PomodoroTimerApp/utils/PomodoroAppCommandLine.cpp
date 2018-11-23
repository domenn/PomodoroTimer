//
// Created by domen on 23. 11. 2018.
//

#include "PomodoroAppCommandLine.h"
#include <QApplication>
#include <c++/8.2.0/bits/move.h>

QCommandLineParser * PomodoroAppCommandLine::handleCommandLineArguments(QApplication *application) {
    auto * parser = new QCommandLineParser;
    parser->setApplicationDescription("Pomodoro timer and stopwatch");
    parser->addHelpOption();
    parser->addVersionOption();

    parser->addOption(*stopwatchModeOption);
    parser->process(*application);

    return parser;
}

PomodoroAppCommandLine::PomodoroAppCommandLine(QApplication * app) :
    stopwatchModeOption(new QCommandLineOption("stopwatch",
                                               QCoreApplication::translate("main", "Run as a simple stopwatch."))),
    parser(handleCommandLineArguments(app)),
    isStopwatchMode(parser->isSet(*stopwatchModeOption))
{
    delete stopwatchModeOption;
    delete parser;
}
