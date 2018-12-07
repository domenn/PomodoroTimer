#include "PomodoroTimerApp/gui/main_window.h"
#include <QApplication>
#include <QCommandLineParser>
#include <External/cpplogger/include/plog/Log.h>
#include <PomodoroTimerApp/utils/app_directories.h>
#include <External/cpplogger/include/plog/Appenders/ConsoleAppender.h>

#ifdef RUNNING_POMODORO_TESTS
#include <iostream>
#endif




// How to correctly configure project and tests:
// https://stackoverflow.com/questions/33638433/setup-google-test-in-clion
// Idea: reduce timer rate on minimize
// More: clean and interrupted pomodori count
// When timer runs out, textButton doesn't change. It should.
// Idea: settings window can set times. Give ability to reset to defaults.
// -------------------------------------------------------------------------------------
// Info: To use notifications, there are some items online
// -- https://forum.qt.io/topic/63357/how-to-set-alerts-in-mac-system
// -- https://techbase.kde.org/Projects/Snorenotify (https://github.com/KDE/snorenotify)
//   -- !! Badly documented. Don't know how to set backend. Examples don't work for me.
// -- https://blogs.msdn.microsoft.com/tiles_and_toasts/2015/07/08/toast-notification-and-action-center-overview-for-windows-10/
//  -- https://docs.microsoft.com/en-us/windows/uwp/design/shell/tiles-and-notifications/send-local-toast
// -- https://github.com/mohabouje/WinToast
// Idea for notification: the popup that shows timer and buttons: start pause (work or smth), skip pause, dismiss

ApplicationMode figureOutAppMode(PomodoroAppCommandLine& cmdLine) {
    if (cmdLine.isStopwatchMode) {
        return ApplicationMode::STOPWATCH;
    }
    return ApplicationMode::POMODORO_TIMER;
}

void setup_logger() {
    static plog::RollingFileAppender<plog::TxtFormatter> fileAppender(
            app_directories::getDefaultLogFilePath().toStdString().c_str(), 8000, 2); // Create the 1st appender.
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender; // Create the 2nd appender.

    plog::init(plog::verbose, &fileAppender).addAppender(&consoleAppender);
}

int main(int argc, char** argv) {
#ifdef RUNNING_POMODORO_TESTS
    std::cerr << "This file should not be ran in tests mode! The application will now exit." << endl;
    return -1;
#endif

    QApplication a(argc, argv);
    setup_logger();
    PomodoroAppCommandLine cmdLine(&a);
    MainWindow w(&a, figureOutAppMode(cmdLine));
    w.show();
    return QApplication::exec();
}