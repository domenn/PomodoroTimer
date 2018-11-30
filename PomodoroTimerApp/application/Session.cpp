//
// Created by domen on 31/10/18.
//

#include <PomodoroTimerApp/pomodoro/PomodoroSession.h>

#include "Session.h"
#include <PomodoroTimerApp/application/application_settings/application_setting.h>

Session* const Session::create(const ApplicationMode& mode) {
    return template_create<PomodoroSessionSettings>(mode, nullptr);
}

Session* const Session::create(const ApplicationMode& mode, array_of_settings const& settings) {
    switch (mode) {
    case ApplicationMode::POMODORO_TIMER: {
        PomodoroSessionSettings settings_structure{ApplicationSetting::get_setting_by_key(settings, ApplicationSetting::KEY_S_WORK_TIME),
                ApplicationSetting::get_setting_by_key(settings, ApplicationSetting::KEY_S_PAUSE_TIME),
                ApplicationSetting::get_setting_by_key(settings,
                        ApplicationSetting::KEY_S_LONG_PAUSE_TIME),
                static_cast<const qint8>(ApplicationSetting::get_setting_by_key(settings,
                        ApplicationSetting::KEY_S_WORK_TIME))
        };
        return template_create<PomodoroSessionSettings>(mode, &settings_structure);
    }
    default:
        throw std::logic_error("Stopwatch mode not implemented");
    }
}