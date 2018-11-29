#pragma once
#include "MainWindowGuiBuilder.h"

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
	Session* const session;

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
    QTimer *timer;
};