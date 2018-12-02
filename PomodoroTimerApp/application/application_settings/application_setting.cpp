//
// Created by domen on 30.11.2018.
//

#include <External/cpplogger/include/plog/Log.h>
#include "application_setting.h"
#include "time_setting.h"
#include "integer_setting.h"
#include <PomodoroTimerApp/gui/main_window.h>

const std::map<QString const, qint64> ApplicationSetting::MAP_DEFAULT_SETTINGS = { // NOLINT(cert-err58-cpp)
        {ApplicationSetting::KEY_S_WORK_TIME, 25 * 60 * 1000},
        {ApplicationSetting::KEY_S_PAUSE_TIME, 5 * 60 * 1000},
        {ApplicationSetting::KEY_S_LONG_PAUSE_TIME, 15 * 60 * 1000},
        {ApplicationSetting::KEY_S_LONG_PAUSE_WHICH, 4}
};

void ApplicationSetting::load_settings(array_of_settings const& container) {
    auto s = application_settings();
    for (auto& item : container) {
        if (s.contains(SETTINGS_KEY_APP + item->options_key)) {
            item->value = s.value(SETTINGS_KEY_APP + item->options_key).value<qint64>();
        } else {
            LOG_DEBUG << "Accessing default value for: " << item->options_key.toStdString();
            item->value = MAP_DEFAULT_SETTINGS.at(item->options_key.toStdString().c_str());
        }
    }
}

QSettings ApplicationSetting::application_settings() {
    return QSettings("d", "PomodoroTimerApplication");
}

qint64 ApplicationSetting::get_setting_by_key(array_of_settings const& container, char const* const key) {
    for (const auto& i : container) {
        if (i->options_key == key) {
            return i->value;
        }
    }
    return 0;
}

array_of_settings ApplicationSetting::make_default_settings_container() {
    return {
            std::make_shared<TimeSetting>(MainWindow::tr("Work time"), ApplicationSetting::KEY_S_WORK_TIME),
            std::make_shared<TimeSetting>(MainWindow::tr("Pause time"), ApplicationSetting::KEY_S_PAUSE_TIME),
            std::make_shared<TimeSetting>(MainWindow::tr("Long pause time"), ApplicationSetting::KEY_S_LONG_PAUSE_TIME),
            std::make_shared<IntegerSetting>(MainWindow::tr("Long pause pomodoro number"),
                    ApplicationSetting::KEY_S_LONG_PAUSE_WHICH,
                    MainWindow::tr(
                            "Pass single number, every which pomodoro should have long pause instead of short.\n"
                            "For example: number 4 means every fourth has long pause. Said differently, 3 short and one long."))
    };
}

void ApplicationSetting::persist_settings(array_of_settings const& container) {
    auto s = application_settings();
    for (auto& item : container) {
        s.setValue(SETTINGS_KEY_APP + item->options_key, QVariant(item->get_value()).toString());
    }
}
