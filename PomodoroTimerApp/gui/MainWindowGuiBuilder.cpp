//
// Created by domen on 23. 11. 2018.
//

#include "MainWindowGuiBuilder.h"
#include "main_window.h"


#include <QMenuBar>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>

#pragma clang diagnostic push
// Ignore IDE warnings for QVBoxLayout * casting for file
#pragma ide diagnostic ignored "OCDFAInspection"
MainWindowGuiBuilder::MainWindowGuiBuilder(const ApplicationMode mode, MainWindow *const mainWindow1)
        : mode(mode), mainWindow(mainWindow1) {}

void MainWindowGuiBuilder::build() {
    createMenu();
    auto *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainWindow->setLayout(mainLayout);

    mainTimerLabel = createMainTimerLabel(mainLayout);
    createStartStopButtons(mainLayout);

    if (mode==ApplicationMode::POMODORO_TIMER) {
        createAdditionalInfoItems(mainLayout);
        mainWindow->setWindowTitle(QObject::tr("Pomodoro Timer")
        );
    } else {
        initializeStopwatch();
    }

}

void MainWindowGuiBuilder::createAdditionalInfoItems(QVBoxLayout *pLayout) {
    const char *const names[]{"Pomodori done", "Short Pauses", "Long Pauses", "Total work", "Total Pause",
                              "Total Session time", "Time since session start", "Session start at", "CheatedTime"};

    auto *layout = new QFormLayout;
    constexpr int NUMBER_ROWS = sizeof(names) / sizeof(char *);

    QLabel *qLabel[NUMBER_ROWS];
    for (int i = 0; i < NUMBER_ROWS; ++i) {
        qLabel[i] = new QLabel(names[i]);
        layout->addRow(new QLabel(names[i]), qLabel[i]);
    }
    pLayout->addLayout(layout, 1);

}

void MainWindowGuiBuilder::createMenu() {
    menuBar = new QMenuBar;

    QMenu *fileMenu = new QMenu(QObject::tr("&File"), mainWindow);
    auto exitAction = fileMenu->addAction(QObject::tr("&Exit"));
    menuBar->addMenu(fileMenu);
    QObject::connect(exitAction, SIGNAL(triggered()), mainWindow, SLOT(accept()));
}

QLabel *MainWindowGuiBuilder::createMainTimerLabel(QLayout *targetGrid) {

    auto theLabel = new QLabel(QObject::tr("TimerPlaceholder"));
    QFont f("Arial", 36, QFont::Bold);
    theLabel->setFont(f);

    ((QVBoxLayout *) targetGrid)->addWidget(theLabel, 1, Qt::AlignCenter);
    return theLabel;
}

void MainWindowGuiBuilder::createStartStopButtons(QLayout *pLayout) {


    QPushButton *buttons[2];

    for (int i = 0; i < 2; ++i) {
        buttons[i] = new QPushButton(QObject::tr("Button %1").arg(i + 1));
        QFont f("Arial", 18, QFont::Bold);

        buttons[i]->setFont(f);
        buttons[i]->setContentsMargins(0, 32, 0, 32);
        buttons[i]->setStyleSheet(
                QStringLiteral("padding-top: %1px; padding-bottom: %1px;").arg(MAIN_BUTTONS_INNER_PADDING));
    }

    fireButton = buttons[0];
    endButton = buttons[1];
    fireButton->setText(buttonLabelStartWork);
    endButton->setText(buttonLabelFinishSession);
    btnToInitial = QObject::connect(fireButton, &QPushButton::released, mainWindow, &MainWindow::fireButtonClickInitial);
    QObject::connect(endButton, &QPushButton::released, mainWindow, &MainWindow::finishButtonClick);

    auto *box = new QHBoxLayout;
    box->addWidget(buttons[0], 1);
    box->addWidget(buttons[1], 1);
    box->setContentsMargins(0, 8, 0, 8);

    ((QVBoxLayout *) pLayout)->addLayout(box, 1);
}

void MainWindowGuiBuilder::changeFireBtnConnection() {
    QObject::disconnect(btnToInitial);
    QObject::connect(fireButton, &QPushButton::released, mainWindow, &MainWindow::fireButtonClick);
}

QPushButton * const MainWindowGuiBuilder::getFireButton() const {
    return fireButton;
}

QLabel * const MainWindowGuiBuilder::getMainTimerLabel() const {
    return mainTimerLabel;
}

void MainWindowGuiBuilder::initializeStopwatch() {

    mainWindow->setWindowTitle(QObject::tr("Stopwatch"));
    // TODO: Load qsettings from stored state. Here or in application.
//    QSettings settings("d", "PomodoroTimerApplication");
//    auto invalid = settings.value("stopwatch/invalidated").value<bool>();
//    if (invalid) {
//        return;
//    }
//    fireButtonClickInitial();
//    settings.setValue("stopwatch/invalidated", true);
//    QString stopwatchState = settings.value("stopwatch/state").value<QString>();
//    auto strr = stopwatchState.toStdString();
//    printf(strr.c_str());
//    session->restore(stopwatchState);
//    //session->beginPause();
//    fireButton->setText("Resume");
}
#pragma clang diagnostic pop