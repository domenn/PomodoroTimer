//
// Created by domen on 31/10/18.
//

#include <PomodoroTimerApp/utils/millisecondsToTimer.h>
#include <PomodoroTimerApp/pomodoro/PomodoroSession.h>
#include "Session.h"

Session::Session() {
}

Session *const Session::create(const ApplicationMode &mode) {
    switch (mode){
        case ApplicationMode ::POMODORO_TIMER:
            return new PomodoroSession;
        case ApplicationMode::STOPWATCH:
            throw std::logic_error("Stopwatch mode not implemented");
    }
}