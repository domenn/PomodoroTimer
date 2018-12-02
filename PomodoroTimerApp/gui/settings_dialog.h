//
// Created by domen on 29.11.2018.
//

#pragma once

#include <QtWidgets/QDialog>
#include <PomodoroTimerApp/application/application_settings/application_setting.h>
#include <PomodoroTimerApp/application/application_settings/time_setting.h>
#include <PomodoroTimerApp/application/application_settings/integer_setting.h>
#include <QWidget>

class SettingsDialog : public QDialog {
Q_OBJECT

public:
    explicit SettingsDialog(const array_of_settings* arr_of_settings, QWidget* parent = nullptr,
            const Qt::WindowFlags& f = Qt::WindowFlags());
    ~SettingsDialog() override;
//    const array_of_settings & get_settings() const;

private:
    typedef ApplicationSetting sk;
//        std::array<std::unique_ptr<ApplicationSetting>, 1> settings{
//            std::make_unique<TimeSetting>("Work time", KEY_S_WORK_TIME)};
    array_of_settings const* const settings;

public slots:
    void accept() override;
    void show_help();
};


