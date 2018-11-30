#include "main_window.h"

#include <QTimer>
#include <QApplication>
#include <QPushButton>
#include <QThread>
#include <QLabel>

#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>

#include "PomodoroTimerApp/utils/app_directories.h"
#include "settings_dialog.h"
#include <PomodoroTimerApp/utils/millisecondsToTimer.h>
#include <PomodoroTimerApp/application/Session.h>
#include <PomodoroTimerApp/pomodoro/PomodoroSession.h>

MainWindow::MainWindow(QApplication* app, ApplicationMode app_mode)
        :QDialog(nullptr,
        Qt::Window |
                Qt::WindowMinimizeButtonHint |
                Qt::WindowMinMaxButtonsHint |
                Qt::WindowMaximizeButtonHint |
                Qt::WindowCloseButtonHint),
         applicationMode(app_mode),
         guiBuilder(applicationMode, this), app_settings(ApplicationSetting::make_default_settings_container()) {

    ApplicationSetting::load_settings(app_settings);

    LOG_INFO << "App starting";
    guiBuilder.build();

}

void MainWindow::myTimerHandler() {
    auto theNumber = session->get_main_timer_value();
    auto stringTimeRepr = millisecondsToTimer::interval_to_string(theNumber);

    guiBuilder.getMainTimerLabel()->setText(stringTimeRepr);
    guiBuilder.update_time_labels(session);
}

void MainWindow::finishButtonClick() {
    guiBuilder.get_end_button()->setEnabled(false);
    guiBuilder.getFireButton()->setText("Start");
    guiBuilder.changeFireBtnConnection(false);
    guiBuilder.set_settings_menu_item_enabled(true);
    timer->stop();
}

void MainWindow::closeEvent(QCloseEvent* event) {

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
    delete session;

    session = Session::create(applicationMode, app_settings);
    auto tm = session->initialize();
    guiBuilder.get_end_button()->setEnabled(true);
    guiBuilder.set_session_start_label(millisecondsToTimer::interval_to_string(tm));

    guiBuilder.set_main_timer_label(session->get_main_timer_value());
    guiBuilder.fire_action_gui_update(session, map_button_text_for_state.at(session->get_current_state()));
    guiBuilder.set_settings_menu_item_enabled(false);
    create_timer();
    guiBuilder.changeFireBtnConnection(true);
}

void MainWindow::fire_button_click() {
    auto st = session->fireAction();
    guiBuilder.fire_action_gui_update(session, map_button_text_for_state.at(st));
    guiBuilder.set_main_timer_label(session->get_main_timer_value());
}

const std::map<PomodoroState const, const char* const> MainWindow::map_button_text_for_state{ // NOLINT(cert-err58-cpp)
        {PomodoroState::INTERRUPTED, "Resume"}, {PomodoroState::PAUSE, "Start next"},
        {PomodoroState::LONG_PAUSE, "Start next"}, {PomodoroState::WORK, "Interrupt"}};

void MainWindow::settings_menu_action_click() {
    LOG_DEBUG << "Settings menu option click";
    SettingsDialog d(&app_settings, this);
    d.setMinimumSize(400, 60);
    d.setModal(true);
    d.exec();
}

void MainWindow::create_timer() {
    if (timer == nullptr) {
        timer = new QTimer;
        QObject::connect(timer, &QTimer::timeout, this, &MainWindow::myTimerHandler);
        QThread::msleep(30);
    }
    timer->start(TIMER_TICK_TIMEOUT);
}
