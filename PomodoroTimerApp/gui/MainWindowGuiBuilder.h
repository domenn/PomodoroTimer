//
// Created by domen on 23. 11. 2018.
//

#pragma once

#include <PomodoroTimerApp/application/ApplicationMode.h>
#include <QMetaObject>

class QMenuBar;
class MainWindow;
class QLabel;
class QLayout;
class QAction;
class QVBoxLayout;
class QPushButton;

class MainWindowGuiBuilder {
public:
    MainWindowGuiBuilder(ApplicationMode mode, MainWindow*mainWindow1);
    void build();

    void changeFireBtnConnection();
    QPushButton * const getFireButton() const;
	QLabel * const getMainTimerLabel() const;
    void initializeStopwatch();
private:
    constexpr static int MAIN_BUTTONS_INNER_PADDING = 16;
    static constexpr const char*const buttonLabelStartWork = "Start work";
    static constexpr const char*const buttonLabelStartPause = "Start pause";
    static constexpr const char*const buttonLabelStartLongPause = "Start long pause";
    static constexpr const char*const buttonLabelInterrupt = "Interrupt";
    static constexpr const char*const buttonLabelContinue = "Continue";
    static constexpr const char*const buttonLabelFinishSession = "Finish";


    ApplicationMode const mode;
    MainWindow* const mainWindow;
    QMenuBar *menuBar;
    QLabel* mainTimerLabel;
    QAction *exitAction;
    QPushButton* fireButton;
    QPushButton* endButton;

    QLabel* lTotalWork;
    QLabel* lTotalPause;
    QLabel* lTotalSessionTime;
    QLabel* lTimeSinceSessionStart;
    QLabel* lSessionStartAt;
    QLabel* lPomodoriDone;
    QLabel* lShortPauses;
    QLabel* lLongPauses;
    QLabel* lCheatedTime;
    QMetaObject::Connection btnToInitial;

    void createMenu();
    QLabel * createMainTimerLabel(QLayout *targetQLayout);
    void createStartStopButtons(QLayout*);
    void createAdditionalInfoItems(QVBoxLayout *pLayout);
};