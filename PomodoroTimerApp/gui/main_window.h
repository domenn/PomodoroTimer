#pragma once
#include "main_window_gui_builder.h"

#include <PomodoroTimerApp/utils/PomodoroAppCommandLine.h>
#include <QDialog>



class QMenuBar;
class QMenu;
class QTimer;
class Session;

class MainWindow : public QDialog {


	constexpr static int TIMER_TICK_TIMEOUT = 133;

	// IMPORTANT: DO NOT CHANGE ORDER OF VARIABLES
	PomodoroAppCommandLine cmdLine;
    ApplicationMode applicationMode;
    MainWindowGuiBuilder guiBuilder;
	Session* session{};
	QTimer *timer{};
	static const std::map<PomodoroState const, const char * const> map_button_text_for_state;

    ApplicationMode figureOutAppMode();


protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit MainWindow(QApplication *app);

public slots:
    void fireButtonClickInitial();
    void fire_button_click();
    void finishButtonClick();
    void myTimerHandler();
	void settings_menu_action_click();
    void create_timer();
};