#include "PomodoroTimerApp/gui/main_window.h"
#include <QApplication>
#include <QCommandLineParser>

#ifdef RUNNING_POMODORO_TESTS
#include <iostream>
#endif

// Some cool idea:
// https://stackoverflow.com/questions/33638433/setup-google-test-in-clion

int main(int argc, char ** argv) {
#ifdef RUNNING_POMODORO_TESTS
    std::cerr << "This file should not be ran in tests mode! The application will now exit." << endl;
    return -1;
#endif

    QApplication a(argc, argv);
    MainWindow w(&a);
    w.show();
    return QApplication::exec();
}