#pragma once
#include "main_window_gui_builder.h"

#include <PomodoroTimerApp/utils/PomodoroAppCommandLine.h>
#include <QDialog>
#include <PomodoroTimerApp/application/application_settings/application_setting.h>
#include <memory>

class QMenuBar;
class QMenu;
class QTimer;
class Session;

class MainWindow : public QDialog {

    constexpr static int TIMER_TICK_TIMEOUT = 133;
    constexpr static char const * const TIMEOUT_WORK_TEXT = "Begin pause";
    constexpr static char const * const TIMEOUT_PAUSE_TEXT = "Start next";

    // IMPORTANT: DO NOT CHANGE ORDER OF VARIABLES
    ApplicationMode applicationMode;
    MainWindowGuiBuilder guiBuilder;
    Session* session{};
    QTimer* timer{};
    array_of_settings const app_settings;
    bool notified{};

    static const std::map<PomodoroState const, const char* const> map_button_text_for_state;

    void log_current_times(const std::string& text_to_log);

protected:
    void closeEvent(QCloseEvent* event) override;

public:
    MainWindow(QApplication* app, ApplicationMode app_mode);

public slots:
    void fireButtonClickInitial();
    void fire_button_click();
    void finishButtonClick();
    void myTimerHandler();
    void settings_menu_action_click();
    void create_timer();
    void try_notify_timeout(PomodoroState state);
};