#include "PomodoroTimerApp/gui/mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>

// Some cool idea:
// https://stackoverflow.com/questions/33638433/setup-google-test-in-clion

int main(int argc, char ** argv) {
    QApplication a(argc, argv);
    MainWindow w(&a);
    w.show();
    return QApplication::exec();
}