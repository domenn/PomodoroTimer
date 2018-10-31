#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QtWidgets/QGridLayout>
#include <PomodoroTimerApp/pomodoro/Session.h>

class QMenuBar;
class QMenu;

class MainWindow : public QDialog {

    constexpr static int MAIN_BUTTONS_INNER_PADDING = 16;
    static constexpr const char*const buttonLabelStartWork = "Start work";
    static constexpr const char*const buttonLabelStartPause = "Start pause";
    static constexpr const char*const buttonLabelStartLongPause = "Start long pause";
    static constexpr const char*const buttonLabelInterrupt = "Interrupt";
    static constexpr const char*const buttonLabelContinue = "Continue";

    static constexpr const char*const buttonLabelFinishSession = "Finish";

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *exitAction;
    QPushButton* fireButton;
    QPushButton* endButton;

    QLabel* mainTimerLabel;

    QLabel* lTotalWork;
    QLabel* lTotalPause;
    QLabel* lTotalSessionTime;
    QLabel* lTimeSinceSessionStart;
    QLabel* lSessionStartAt;
    QLabel* lPomodoriDone;
    QLabel* lShortPauses;
    QLabel* lLongPauses;
    QLabel* lCheatedTime;
    QTimer * timer;
    qint32  counter;
    QMetaObject::Connection btnToInitial;


    void createMenu();
    QGridLayout * createGridWidgets();

    Session session;

    QLabel * createMainTimerLabel(QLayout *targetGrid);

    void createStartStopButtons(QLayout *pLayout);

    void createAdditionalInfoItems(QVBoxLayout *pLayout);

private slots:
    void fireButtonClickInitial();
    void fireButtonClick();
    void myTimerHandler();

public:
    MainWindow();


};

#endif // MAINWINDOW_H