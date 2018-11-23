#pragma once
#include "MainWindowGuiBuilder.h"

#include <PomodoroTimerApp/utils/PomodoroAppCommandLine.h>
#include <PomodoroTimerApp/application/Application.h>
#include <QDialog>



class QMenuBar;
class QMenu;
class QTimer;

class MainWindow : public QDialog {

    constexpr static int MAIN_BUTTONS_INNER_PADDING = 16;
    static constexpr const char*const buttonLabelStartWork = "Start work";
    static constexpr const char*const buttonLabelStartPause = "Start pause";
    static constexpr const char*const buttonLabelStartLongPause = "Start long pause";
    static constexpr const char*const buttonLabelInterrupt = "Interrupt";
    static constexpr const char*const buttonLabelContinue = "Continue";
    static constexpr const char*const buttonLabelFinishSession = "Finish";

    ApplicationMode applicationMode;
    MainWindowGuiBuilder guiBuilder;
    PomodoroAppCommandLine cmdLine;

    ApplicationMode figureOutAppMode();
    Application application;

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit MainWindow(QApplication *app);

public slots:
    void fireButtonClickInitial();
    void fireButtonClick();
    void finishButtonClick();
    void myTimerHandler();
    QTimer *timer;
};