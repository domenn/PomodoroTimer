//
// Created by domen on 24.11.2018.
//

#pragma once
#include <PomodoroTimerApp/pomodoro/PomodoroSession.h>
#include "tests_h_common.h"

namespace mk {
    inline PomodoroSession* pomodoroTimerApp(bool start = true) {
        PomodoroSession * app = (PomodoroSession*) Session::create (ApplicationMode::POMODORO_TIMER);
        if (start) {
            app->initialize();
        }
        return app;
    }
}