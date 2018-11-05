#include "mainwindow.h"
#include <QMenuBar>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QPushButton>
#include <QtWidgets/QFormLayout>
#include <QTimer>
#include <PomodoroTimerApp/utils/millisecondsToTimer.h>
#include <QtCore/QCommandLineParser>
#include <QApplication>

// #include "ui_mainwindow.h"

//MainWindow::MainWindow(QWidget *parent) :
//        QMainWindow(parent),
//        ui(new Ui::MainWindow) {
//}

MainWindow::MainWindow(QApplication * app) {

    handleCommandLineArguments(app);

    createMenu();

    auto *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    setLayout(mainLayout);


    mainTimerLabel = createMainTimerLabel(mainLayout);
    createStartStopButtons(mainLayout);

    createAdditionalInfoItems(mainLayout);


    setWindowTitle(tr("Pomodoro Timer"));
}

void MainWindow::createMenu() {
    menuBar = new QMenuBar;

    fileMenu = new QMenu(tr("&File"), this);
    exitAction = fileMenu->addAction(tr("E&xit"));
    menuBar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));
}

QGridLayout * MainWindow::createGridWidgets() {
    auto *layout = new QGridLayout;





    // int row, int column, int rowSpan, int columnSpan, Qt::Alignment = Qt::Alignment
   //  layout->addWidget(smallEditor, 4, 4, 8, 8, Qt::AlignCenter);

    return layout;
}

QLabel *MainWindow::createMainTimerLabel(QLayout *targetGrid) {

    auto theLabel = new QLabel(tr("TimerPlaceholder"));
    QFont f( "Arial", 36, QFont::Bold);
    theLabel->setFont(f);

    //((QHBoxLayout*)targetGrid)->addWidget(theLabel, 1, 1, NUM_GRID_COLS-2, 4, Qt::AlignCenter); // Variant for grid
    ((QVBoxLayout*)targetGrid)->addWidget(theLabel, 1, Qt::AlignCenter);
    return theLabel;
}

void MainWindow::createStartStopButtons(QLayout *pLayout) {



    QPushButton* buttons[2];

    for (int i = 0; i < 2; ++i) {
        buttons[i] = new QPushButton(tr("Button %1").arg(i + 1));
        QFont f( "Arial", 18, QFont::Bold);

        buttons[i]->setFont(f);
        buttons[i]->setContentsMargins(0,32,0,32);
        buttons[i]->setStyleSheet(QStringLiteral("padding-top: %1px; padding-bottom: %1px;").arg(MAIN_BUTTONS_INNER_PADDING));
        // addWidget(QWidget *, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
    //    layout->addWidget(buttons[i]);
    }

    fireButton = buttons[0];
    endButton = buttons[1];
    fireButton->setText(buttonLabelStartWork);
    endButton->setText(buttonLabelFinishSession);
    // connect(fireButton, SIGNAL(released()), this, SLOT(fireButtonClickInitial()));
    btnToInitial = QObject::connect(fireButton, &QPushButton::released, this, &MainWindow::fireButtonClickInitial);

    QHBoxLayout * box = new QHBoxLayout;
    box->addWidget(buttons[0], 1);
    box->addWidget(buttons[1], 1);
    box->setContentsMargins(0,8,0,8);
  //  box->set

//    QFormLayout *layout = new QFormLayout;
//    layout->addRow(fireButton, endButton);

    ((QVBoxLayout*)pLayout)->addLayout(box, 1);

//    pLayout->addWidget(fireButton, 5, 0, 2, NUM_GRID_COLS/2, Qt::AlignCenter);
//    pLayout->addWidget(endButton, 5, NUM_GRID_COLS/2+1, 2, NUM_GRID_COLS/2, Qt::AlignCenter);
}

void MainWindow::createAdditionalInfoItems(QVBoxLayout *pLayout) {

    // std::map<QString, QString> mymap = {{"one", 1}, {"two", 2}, {"three", 3}};
    const char* const names[]{"Pomodori done", "Short Pauses", "Long Pauses", "Total work", "Total Pause", "Total Session time", "Time since session start", "Session start at", "CheatedTime"};


    QFormLayout *layout = new QFormLayout;
    constexpr int NUMBER_ROWS = sizeof(names)/ sizeof(char*);
    // QLabel* qLabel[names->size()];

    QLabel* qLabel[NUMBER_ROWS];
    // for(int i = 0; i<names->size(); ++i){
    for(int i = 0; i<NUMBER_ROWS; ++i){
        qLabel[i] = new QLabel(names[i]);
        layout->addRow(new QLabel(names[i]), qLabel[i]);
    }
    pLayout->addLayout(layout, 1);


}

void MainWindow::fireButtonClickInitial() {
    session.decide();
    timer = new QTimer;
    QObject::connect(timer, &QTimer::timeout, this, &MainWindow::myTimerHandler);
    timer->start(1000);  // 100 nanoseconds or 1 second interval
    QObject::disconnect (btnToInitial);
    // disconnect(fireButton, SIGNAL(released), 0, 0);
    QObject::connect(fireButton, &QPushButton::released, this, &MainWindow::fireButtonClick);
}

void MainWindow::myTimerHandler() {
    auto stringTimeRepr = millisecondsToTimer::intervalToString(session.getTaskTimeMs());
    mainTimerLabel->setText(stringTimeRepr);
}

void MainWindow::fireButtonClick() {
    session.decide();
}

void MainWindow::handleCommandLineArguments(QApplication *application) {
    QCommandLineParser parser;
    parser.setApplicationDescription("Pomodoro timer and stopwatch");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption stopwatchModeOption("stopwatch", QCoreApplication::translate("main", "Run as a simple stopwatch."));
    parser.addOption(stopwatchModeOption);
    parser.process(*application);

    is_stopwatch_mode = parser.isSet(stopwatchModeOption);

}
