#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QtWidgets/QGridLayout>

class QMenuBar;
class QMenu;

class MainWindow : public QDialog {

    constexpr static int NUM_GRID_ROWS = 16;
    constexpr static int NUM_GRID_COLS = 16;

    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *exitAction;
    QPushButton* fireButton;
    QPushButton* endButton;

    QLabel* mainTimerLabel;

    void createMenu();
    QGridLayout * createGridWidgets();

public:
    MainWindow();


    QLabel * createMainTimerLabel(QLayout *targetGrid);

    void createStartStopButtons(QLayout *pLayout);
};

#endif // MAINWINDOW_H
