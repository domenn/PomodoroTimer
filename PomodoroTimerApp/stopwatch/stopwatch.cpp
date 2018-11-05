//
// Created by domen on 05/11/18.
//

#include "stopwatch.h"

QString stopwatch::decide() {
    // REFACTOR better return value handling
    if (state == PomodoroState::PAUSE) {
        total_pause += (QDateTime::currentMSecsSinceEpoch() - pause_start_time);
        state = PomodoroState::WORK;
        return "Pause";
    } else {
        pause_display_timestamp = getTaskTimeMs();
        pause_start_time = QDateTime::currentMSecsSinceEpoch();
        state = PomodoroState::PAUSE;
        return "Resume";
    }
}

stopwatch::stopwatch() : state(PomodoroState::PAUSE),
                         total_pause(0),
                         start_time(QDateTime::currentMSecsSinceEpoch()),
                         pause_start_time(QDateTime::currentMSecsSinceEpoch()) {}

qint64 stopwatch::getTaskTimeMs() const {
    if (state == PomodoroState::WORK) {
        return QDateTime::currentMSecsSinceEpoch() - start_time - total_pause;
    }else{
        return pause_display_timestamp;
    }
}
