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
#include <PomodoroTimerApp/application/Session.h>
#include <PomodoroTimerApp/pomodoro/PomodoroSession.h>
#include <PomodoroTimerApp/utils/date_time_format_converter.h>

#include <Notifications/notifications_api.h>

MainWindow::MainWindow(QApplication* app, ApplicationMode app_mode)
        :QDialog(nullptr,
        Qt::Window |
                Qt::WindowMinimizeButtonHint |
                Qt::WindowMinMaxButtonsHint |
                Qt::WindowMaximizeButtonHint |
                Qt::WindowCloseButtonHint),
         applicationMode(app_mode),
         guiBuilder(applicationMode, this), app_settings(ApplicationSetting::make_default_settings_container()) {

    libn_init(ApplicationSetting::APPLICATION_NAME);
    ApplicationSetting::load_settings(app_settings);

    LOG_INFO << "App starting";
    guiBuilder.build();

    libn_show("Title of that thingy. Long.", "Some not very super short text. Lol. Wtf.", nullptr);
    // libn_show("Testing", "Just short TXT.", nullptr);
}

void MainWindow::myTimerHandler() {
    auto theNumber = session->get_main_timer_value();
    auto stringTimeRepr = con::interval_to_string2(theNumber, false);

    guiBuilder.getMainTimerLabel()->setText(stringTimeRepr);
    guiBuilder.update_time_labels(session);

    try_notify_timeout(session->get_current_state());
}

void MainWindow::finishButtonClick() {
    guiBuilder.get_end_button()->setEnabled(false);
    guiBuilder.getFireButton()->setText("Start");
    guiBuilder.changeFireBtnConnection(false);
    guiBuilder.set_settings_menu_item_enabled(true);
    timer->stop();
    log_current_times(
            (QString("Finishing the session after: ") + con::interval_to_ms_string(session->get_total_time(), ".",
                    false)).toStdString());
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
    LOG_INFO << "Started the session.";
    guiBuilder.get_end_button()->setEnabled(true);
    guiBuilder.set_session_start_label(QDateTime::fromMSecsSinceEpoch(tm).toString("HH:mm:ss"));

    guiBuilder.set_main_timer_label(session->get_main_timer_value());
    guiBuilder.fire_action_gui_update(session, map_button_text_for_state.at(session->get_current_state()));
    guiBuilder.set_settings_menu_item_enabled(false);
    create_timer();
    guiBuilder.changeFireBtnConnection(true);
}

void MainWindow::fire_button_click() {
    auto prev_state = session->get_current_state();
    auto st = session->fireAction();
    guiBuilder.fire_action_gui_update(session, map_button_text_for_state.at(st));
    guiBuilder.set_main_timer_label(session->get_main_timer_value());
    if (st == PomodoroState::WORK) {
        std::ostringstream ss;
        auto p_num = session->get_pomodori_done() + 1;
        ss << (prev_state == PomodoroState::INTERRUPTED ? "Resuming" : "Starting") << " pomodoro: " << p_num;
        log_current_times(ss.str());
    }
    notified = false;
}

const std::map<PomodoroState const, const char* const> MainWindow::map_button_text_for_state{ // NOLINT(cert-err58-cpp)
        {PomodoroState::INTERRUPTED, "Resume"},
        {PomodoroState::PAUSE, TIMEOUT_PAUSE_TEXT},
        {PomodoroState::LONG_PAUSE, TIMEOUT_PAUSE_TEXT},
        {PomodoroState::WORK, "Interrupt"}};

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

void MainWindow::log_current_times(const std::string& text_to_log) {
    auto wt = session->get_total_elapsed_time_of_kind(PomodoroState::WORK);
    auto pt = session->get_total_pause();
    auto effective_time = session->get_total_non_interrupted_time();
    auto it = session->get_total_elapsed_time_of_kind(PomodoroState::INTERRUPTED);

    LOG_INFO << text_to_log << ". Elapsed time (minutes) - Work: " << con::as_minutes(wt)
             << ". Pause: " << con::as_minutes(pt) << ". Effective: " << con::as_minutes(effective_time)
             << ". Interrupted: " <<
             con::as_minutes(it) << ". Total: " << con::as_minutes(session->get_total_time()) << ".";
}

void MainWindow::try_notify_timeout(PomodoroState const state) {
    if(!session->is_timer_expired() || notified){
        return;
    }
    notified = true;
    if (state == PomodoroState::WORK) {
        LibnNotificationButton b2 {"No pause plz", nullptr, ([](){ LOG_DEBUG << "Callback for Second"; }) };
        LibnNotificationButton b1 {"OK", &b2, ([](){ LOG_DEBUG << "Callback for OK"; }) };
        libn_show("Work timer run out.", "Start pause?", &b1);
        guiBuilder.getFireButton()->setText(TIMEOUT_WORK_TEXT);

    } else {
        libn_show("Pause finished.", "Start next round?", nullptr);
        guiBuilder.getFireButton()->setText(TIMEOUT_PAUSE_TEXT);
    }
}
