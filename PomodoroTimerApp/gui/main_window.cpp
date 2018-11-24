#include "main_window.h"

#include <QTimer>
#include <QApplication>
#include <QPushButton>
#include <QThread>
#include <QLabel>

#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

#include "PomodoroTimerApp/utils/app_directories.h"
#include <PomodoroTimerApp/utils/millisecondsToTimer.h>

MainWindow::MainWindow(QApplication *app) : QDialog(nullptr,
                                                    Qt::Window |
                                                    Qt::WindowMinimizeButtonHint |
                                                    Qt::WindowMinMaxButtonsHint |
                                                    Qt::WindowMaximizeButtonHint |
                                                    Qt::WindowCloseButtonHint),
                                            cmdLine(app),
                                            applicationMode(figureOutAppMode()),
                                            guiBuilder(applicationMode, this),
                                            application(applicationMode){

    static plog::RollingFileAppender<plog::TxtFormatter> fileAppender(app_directories::getDefaultLogFilePath().toStdString().c_str(), 8000, 2); // Create the 1st appender.
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender; // Create the 2nd appender.

    plog::init(plog::debug, &fileAppender).addAppender(&consoleAppender);

    LOG_INFO << "App starting";
    guiBuilder.build();

}

void MainWindow::myTimerHandler() {

//    // REFACTOR: the number should be command line parameter, or option
	auto theNumber = application.getMainTimerValue();
    auto stringTimeRepr = millisecondsToTimer::intervalToString(theNumber);

    guiBuilder.getMainTimerLabel()->setText(stringTimeRepr);
}

void MainWindow::finishButtonClick() {
    guiBuilder.getFireButton()->setText("Finishing");
}

void MainWindow::closeEvent(QCloseEvent *event) {

    LOG_DEBUG << "Closing the app";

    // TODO implement close event

    QDialog::closeEvent(event);
//
//    if (!session)
//        return;
//    QString store = session->saveState();
//    if (store.isEmpty()) {
//        return;
//    }
//
//    QSettings settings("d", "PomodoroTimerApplication");
//
//    if (is_stopwatch_mode) {
//        settings.setValue("stopwatch/state", store);
//        settings.setValue("stopwatch/invalidated", false);
//    } else {
//        return;
//    }

}


void MainWindow::fireButtonClickInitial() {

    // session = Session::create(applicationMode);

	application.start();

    fireButtonClick();
    timer = new QTimer;
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::myTimerHandler);
    QThread::msleep(80);
    timer->start(1000);  // 100 nanoseconds or 1 second interval
    guiBuilder.changeFireBtnConnection();
}

void MainWindow::fireButtonClick() {
    application.fireAction();
}

ApplicationMode MainWindow::figureOutAppMode() {
    if (cmdLine.isStopwatchMode) {
        return ApplicationMode::STOPWATCH;
    }
    return ApplicationMode::POMODORO_TIMER;
}
