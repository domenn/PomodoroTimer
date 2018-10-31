//
// Created by domen on 31/10/18.
//


#include "Run.h"

Run::Run(const PomodoroState &pomodoroState, const qint64 remainingTime) : startTime(QDateTime::currentMSecsSinceEpoch()),
                                                                     state(pomodoroState), timer() {
    if (remainingTime == -1) {
        // REFACTOR_JOB: define some map between enum and time somewhere else .. Should even be configurable
        plannedWorkTime = defaultRemainingTime(pomodoroState);
    }else{
        plannedWorkTime = remainingTime;
    }
    timer.start();
}

void Run::finish() {
    actualWorkTime = timer.elapsed();
}

qint64 Run::remainingTimeMs() const {
    return plannedWorkTime - timer.elapsed();
}

qint64 Run::defaultRemainingTime(const PomodoroState &state) const {
    switch (state) {
        case PomodoroState::WORK:
            return 1000 * 60 * 25;
        case PomodoroState::LONG_PAUSE:
            return 1000 * 60 * 15;
        case PomodoroState::PAUSE:
            return 1000 * 60 * 5;
        default:
            return QDateTime::currentMSecsSinceEpoch();
    }
}
