//
// Created by domen on 31/10/18.
//

#include "Pomodoro.h"
#include <PomodoroTimerApp/utils/mockable_datetime.h>

Pomodoro::Pomodoro(const qint64 start_timestamp, const qint64 planned_pause_time, const bool is_long_pause)
        :start_timestamp_(start_timestamp), planned_pause_time_(planned_pause_time),
         map_({{PomodoroState::LONG_PAUSE, &pause_time_},
                 {PomodoroState::PAUSE, &pause_time_},
                 {PomodoroState::INTERRUPTED, &interrupt_time},
                 {PomodoroState::WORK, &running_time_}
         }), is_long_pause(is_long_pause) { }

void Pomodoro::add_time_of_kind(const PomodoroState what_kind, const qint64 how_much) {
    *(map_.at(what_kind)) += how_much;
}

qint64 Pomodoro::get_total_time(const bool return_stored_only) const {
    if (return_stored_only) {
        return get_time_of_kind(PomodoroState::WORK)
                + get_time_of_kind(PomodoroState::INTERRUPTED)
                + get_time_of_kind(PomodoroState::PAUSE);
    }
    return dt::currentTimeMs() - start_timestamp_;
}

qint64 Pomodoro::get_time_of_kind(const PomodoroState what_kind, const bool is_current_state) const {
    return get_time_of_kind(what_kind, dt::currentTimeMs(), is_current_state);
}

qint64 Pomodoro::get_time_of_kind(PomodoroState what_kind, qint64 current_timestamp, bool is_current_state) const {
    auto current_state_time = *(map_.at(what_kind));
    if (is_current_state) {
        auto total_elapsed_time = current_timestamp - start_timestamp_;
        auto not_stored_time = total_elapsed_time - get_total_time(true);
        return not_stored_time + current_state_time;
    }
    return current_state_time;
}