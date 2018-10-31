#include "mainwindow.h"
#include <QMenuBar>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QPushButton>
#include <QtWidgets/QFormLayout>
// #include "ui_mainwindow.h"

//MainWindow::MainWindow(QWidget *parent) :
//        QMainWindow(parent),
//        ui(new Ui::MainWindow) {
//}

MainWindow::MainWindow() {
    createMenu();

    auto *mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    setLayout(mainLayout);


    mainTimerLabel = createMainTimerLabel(mainLayout);
    createStartStopButtons(mainLayout);


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

        // addWidget(QWidget *, int stretch = 0, Qt::Alignment alignment = Qt::Alignment());
    //    layout->addWidget(buttons[i]);
    }

    fireButton = buttons[0];
    endButton = buttons[1];
    QFormLayout *layout = new QFormLayout;
    layout->addRow(fireButton, endButton);

    ((QVBoxLayout*)pLayout)->addLayout(layout, 1);

//    pLayout->addWidget(fireButton, 5, 0, 2, NUM_GRID_COLS/2, Qt::AlignCenter);
//    pLayout->addWidget(endButton, 5, NUM_GRID_COLS/2+1, 2, NUM_GRID_COLS/2, Qt::AlignCenter);
}
