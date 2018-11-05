#include "PomodoroTimerApp/gui/mainwindow.h"
#include <QApplication>
#include <QCommandLineParser>

int main(int argc, char ** argv) {
    QApplication a(argc, argv);
    MainWindow w(&a);
    w.show();
    return QApplication::exec();
}