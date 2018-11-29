//
// Created by domen on 23. 11. 2018.
//

#pragma once

#include <PomodoroTimerApp/application/ApplicationMode.h>
#include <QMetaObject>
#include <PomodoroTimerApp/application/Session.h>
#include <QLabel>

class QMenuBar;
class MainWindow;
class QLayout;
class QAction;
class QVBoxLayout;
class QPushButton;

#define GUI_BUILDER_FORM_LABEL(name, str, index)

class MainWindowGuiBuilder {

public:
    MainWindowGuiBuilder(ApplicationMode mode, MainWindow*mainWindow1);
    void build();

    void changeFireBtnConnection();
    QPushButton * const getFireButton() const;
	QLabel * const getMainTimerLabel() const;
    void initializeStopwatch();
    void set_main_timer_label(qint64 millis);
	void fire_action_gui_update(Session const* session);
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

    typedef std::pair<QLabel*, char const* const> additional_info_field;

    struct sadditional_info_fields {
		additional_info_field lTotalWork{nullptr, "Total work"};
		additional_info_field lTotalPause{nullptr, "Total pause"};
		additional_info_field lTotalSessionTime{nullptr, "Total legal time"};
		additional_info_field lTimeSinceSessionStart{nullptr, "Time since session start"};
		additional_info_field lSessionStartAt{nullptr, "Session start at"};
		additional_info_field lPomodoriDone{nullptr, "Pomodori done"};
		additional_info_field lShortPauses{nullptr, "Short pauses"};
		additional_info_field lLongPauses{nullptr, "Long pauses"};
		additional_info_field lCheatedTime{nullptr, "Interruptions time"};
	}additional_info_fields;

    QMetaObject::Connection btnToInitial;

    void createMenu();
    QLabel * createMainTimerLabel(QLayout *targetQLayout);
    void createStartStopButtons(QLayout*);
    void createAdditionalInfoItems(QVBoxLayout *pLayout);
};