//
// Created by domen on 23. 11. 2018.
//

#include "main_window_gui_builder.h"
#include "main_window.h"

#include <QMenuBar>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <PomodoroTimerApp/utils/millisecondsToTimer.h>

#pragma clang diagnostic push
// Ignore IDE warnings for QVBoxLayout * casting for file
#pragma ide diagnostic ignored "OCDFAInspection"

MainWindowGuiBuilder::MainWindowGuiBuilder(const ApplicationMode mode, MainWindow* const mainWindow1)
        :mode(mode), mainWindow(mainWindow1) { }

void MainWindowGuiBuilder::build() {
    createMenu();
    auto* mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainWindow->setLayout(mainLayout);

    mainTimerLabel = createMainTimerLabel(mainLayout);
    createStartStopButtons(mainLayout);

    if (mode == ApplicationMode::POMODORO_TIMER) {
        createAdditionalInfoItems(mainLayout);
        mainWindow->setWindowTitle(QObject::tr("Pomodoro Timer"));
    } else {
        initializeStopwatch();
    }

}

void MainWindowGuiBuilder::createAdditionalInfoItems(QVBoxLayout* pLayout) {

    auto* layout = new QFormLayout;
    auto ptr_struct_items = reinterpret_cast<additional_info_field*>(&additional_info_fields);
    for (std::size_t i = 0; i <(sizeof(additional_info_fields) / sizeof(additional_info_field)); ++i) {
        auto itm = ptr_struct_items + i;
        itm->first = new QLabel(itm->second);
        layout->addRow(new QLabel(itm->second), itm->first);
    }
    pLayout->addLayout(layout, 1);
}

void MainWindowGuiBuilder::createMenu() {
    menuBar = new QMenuBar;

    QMenu* fileMenu = new QMenu(QObject::tr("&File"), mainWindow);
    settings_menu_action = fileMenu->addAction(QObject::tr("&Settings"));
    fileMenu->addSeparator();
    exitAction = fileMenu->addAction(QObject::tr("&Exit"));
    menuBar->addMenu(fileMenu);
    QObject::connect(exitAction, SIGNAL(triggered()), mainWindow, SLOT(accept()));
    QObject::connect(settings_menu_action, &QAction::triggered, mainWindow, &MainWindow::settings_menu_action_click);
}

QLabel* MainWindowGuiBuilder::createMainTimerLabel(QLayout* targetGrid) {

    auto theLabel = new QLabel(QObject::tr("TimerPlaceholder"));
    QFont f("Arial", 36, QFont::Bold);
    theLabel->setFont(f);

    ((QVBoxLayout*) targetGrid)->addWidget(theLabel, 1, Qt::AlignCenter);
    return theLabel;
}

void MainWindowGuiBuilder::createStartStopButtons(QLayout* pLayout) {

    QPushButton* buttons[2];

    for (int i = 0; i < 2; ++i) {
        buttons[i] = new QPushButton(QObject::tr("Button %1").arg(i + 1));
        QFont f("Arial", 18, QFont::Bold);

        buttons[i]->setFont(f);
        buttons[i]->setContentsMargins(0, 32, 0, 32);
        buttons[i]->setStyleSheet(
                QStringLiteral("padding-top: %1px; padding-bottom: %1px;").arg(MAIN_BUTTONS_INNER_PADDING));
    }

    fire_button = buttons[0];
    endButton = buttons[1];
    fire_button->setText(buttonLabelStartWork);
    endButton->setText(buttonLabelFinishSession);
    endButton->setEnabled(false);
    btnToInitial = QObject::connect(fire_button, &QPushButton::released, mainWindow,
            &MainWindow::fireButtonClickInitial);
    QObject::connect(endButton, &QPushButton::released, mainWindow, &MainWindow::finishButtonClick);

    auto* box = new QHBoxLayout;
    box->addWidget(buttons[0], 1);
    box->addWidget(buttons[1], 1);
    box->setContentsMargins(0, 8, 0, 8);

    ((QVBoxLayout*) pLayout)->addLayout(box, 1);
}

void MainWindowGuiBuilder::changeFireBtnConnection(bool const starting) {
    if (starting) {
        QObject::disconnect(btnToInitial);
        btn_to_working = QObject::connect(fire_button, &QPushButton::released, mainWindow,
                &MainWindow::fire_button_click);
    } else {
        QObject::disconnect(btn_to_working);
        btnToInitial = QObject::connect(fire_button, &QPushButton::released, mainWindow,
                &MainWindow::fireButtonClickInitial);
    }
}

QPushButton* const MainWindowGuiBuilder::getFireButton() const {
    return fire_button;
}

QLabel* const MainWindowGuiBuilder::getMainTimerLabel() const {
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
//    fire_button->setText("Resume");
}

void MainWindowGuiBuilder::set_main_timer_label(qint64 const millis) {
    mainTimerLabel->setText(millisecondsToTimer::interval_to_string(millis));
}

void MainWindowGuiBuilder::fire_action_gui_update(Session const* const session, QString const& fire_btn_text) {
    additional_info_fields.lPomodoriDone.first->setText(QString::number(session->get_pomodori_done()));
    additional_info_fields.lLongPauses.first->setText(QString::number(session->get_long_pauses_done()));
    additional_info_fields.lShortPauses.first->setText(QString::number(session->get_short_pauses_done()));
    fire_button->setText(fire_btn_text);
}

void MainWindowGuiBuilder::update_time_labels(Session const* const session) {
    additional_info_fields.lTimeSinceSessionStart.first
            ->setText(millisecondsToTimer::interval_to_string(session->get_total_time()));

    additional_info_fields.lTotalPause.first
            ->setText(millisecondsToTimer::interval_to_string(session->get_total_pause()));

    additional_info_fields.lTotalWork.first->setText(
            millisecondsToTimer::interval_to_string(session->get_total_elapsed_time_of_kind(PomodoroState::WORK)));

    additional_info_fields.lTotalSessionTime.first
            ->setText(millisecondsToTimer::interval_to_string(session->get_total_non_interrupted_time()));

    additional_info_fields.lCheatedTime.first->setText(millisecondsToTimer::interval_to_string(
            session->get_total_elapsed_time_of_kind(PomodoroState::INTERRUPTED)));

}

void MainWindowGuiBuilder::set_session_start_label(const QString& qString) {
    additional_info_fields.lSessionStartAt.first->setText(qString);
}

void MainWindowGuiBuilder::set_settings_menu_item_enabled(const bool b) {
    settings_menu_action->setEnabled(b);
}

#pragma clang diagnostic pop