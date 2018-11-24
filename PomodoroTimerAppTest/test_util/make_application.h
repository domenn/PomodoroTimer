//
// Created by domen on 24.11.2018.
//

#pragma once

namespace mk {
    inline Application* pomodoroTimerApp(bool start = true) {
        Application * app = new  Application(ApplicationMode::POMODORO_TIMER);
        if (start) {
            app->start();
        }
        return app;
    }
}