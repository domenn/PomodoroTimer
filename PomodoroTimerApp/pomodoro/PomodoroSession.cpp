//
// Created by domen on 23. 11. 2018.
//

#include "PomodoroSession.h"
#include <PomodoroTimerApp/utils/mockable_datetime.h>

void PomodoroSession::startNewPomodoro() {
    current_phase_start_timestamp = dt::currentTimeMs();
    state = PomodoroState::WORK;

    pomodori_.emplace_back(current_phase_start_timestamp,
            (sessionsForBigPause == LONG_BREAK_NUMBER - 1) ? TIME_LONG_PAUSE : TIME_PAUSE);
    current_pomodoro_ = &pomodori_.back();
}

void PomodoroSession::initialize() {
    work_start_timestamp = dt::currentTimeMs();
    startNewPomodoro();
}

qint64 PomodoroSession::getMainTimerValue() {
    auto elapsed = state != PomodoroState::INTERRUPTED ? current_pomodoro_->get_time_of_kind(state, true)
            : current_pomodoro_->get_time_of_kind(PomodoroState::WORK);

    return this->timeForTask.at(state) - elapsed;
}

QString PomodoroSession::saveState() {
    return QString();
}

void PomodoroSession::restore(const QString& state) {

}

QString PomodoroSession::fireAction() {
    auto actual_current_phase_start_ts = current_phase_start_timestamp;
    current_pomodoro_->add_time_of_kind(state, current_phase_start_timestamp - actual_current_phase_start_ts);
    if (timerExpired()) {
        current_phase_start_timestamp = dt::currentTimeMs();
        switch (state) {
        case PomodoroState::WORK: return selectPause();
        case PomodoroState::LONG_PAUSE:
        case PomodoroState::PAUSE: startNewPomodoro();
            return "Pause";
        default:
            throw std::logic_error(
                    "Invalid state: timerExpired() is true and pomodoroState is INTERRUPTED. This is not allowed.");
        }
    }

    current_phase_start_timestamp = dt::currentTimeMs();
    current_pomodoro_->add_time_of_kind(state, current_phase_start_timestamp - actual_current_phase_start_ts);
    if (state == PomodoroState::INTERRUPTED) {
        state = PomodoroState::WORK;
        return "Resume";
    }
    else { // if (state == PomodoroState::WORK) {
        state = PomodoroState::INTERRUPTED;
        return "Interrupt";
    }
}

bool PomodoroSession::timerExpired() {
    return getMainTimerValue() < 0;
}

QString PomodoroSession::selectPause() {
    ++sessionsForBigPause;
    current_phase_start_timestamp = dt::currentTimeMs();
    if (sessionsForBigPause >= LONG_BREAK_NUMBER) {
        sessionsForBigPause = 0;
        state = PomodoroState::LONG_PAUSE;
    }
    else {
        state = PomodoroState::PAUSE;
    }
    return "Start Work";
}

PomodoroSession::PomodoroSession()
        :timeForTask({{PomodoroState::PAUSE, TIME_PAUSE},
        { PomodoroState::WORK, TIME_WORK },
        { PomodoroState::LONG_PAUSE, TIME_LONG_PAUSE },
        // Interrupted is basically work, so planned time is same
        { PomodoroState::INTERRUPTED, TIME_WORK }}) { }

