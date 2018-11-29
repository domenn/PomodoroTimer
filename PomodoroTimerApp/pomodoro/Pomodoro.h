//
// Created by domen on 31/10/18.
//
#pragma once

#include <QtCore>
#include "PomodoroState.h"

/**
 * This class keeps some information. It does not do any logic, only store information. All calculation must be provided
 * externally. .
 */
class Pomodoro {
    friend class PomodoroSession;

    const qint64 start_timestamp_;
    const qint64 planned_pause_time_;
    qint64 running_time_{};
    qint64 pause_time_{};
    qint64 interrupt_time{};
    const std::map<PomodoroState, qint64*> map_;

    /**
     * Similiar to other Pomodoro::get_time_of_kind function, but uses provided start time instead of checking it.
     * @param what_kind PomdoroState to get the time for
     * @param current_timestamp current timestamp .. Will use instead of checking system time
     * @param is_current_state read is_current_state for other Pomodoro::get_time_of_kind
     * @return Time of what_kind
     */
    qint64 get_time_of_kind(PomodoroState what_kind, qint64 current_timestamp, bool is_current_state) const;

public:

    const bool is_long_pause;

    /**
     * Creating new Pomodoro automatically starts it in work mode.
     * @param start_timestamp Start time of this pomodoro
     * @param pause_time planned pause time for this one in milliseconds
     */
    Pomodoro(qint64 start_timestamp, qint64 planned_pause_time, bool is_long_pause = false);

    /**
     * Increments time for what_kind by how_much
     * @param what_kind state to add
     * @param how_much time in ms
     */
    void add_time_of_kind(PomodoroState what_kind, qint64 how_much);

    /**
     * @param what_kind PomodoroState type to return .. pause, interrupt or work.
     * @param is_current_state is current state equals to state that is being returned.
     * If true, the difference between start time and current time will be added.
     * @return Time in ms for state of choice
     */
    qint64 get_time_of_kind(PomodoroState what_kind, bool is_current_state = false) const;

    /**
     * @param return_stored_only If true, only stored time is returned. If false, returns time difference between start of this pmodoro and now.
     * @return Total elapsed time for this pomodoro, sum of all.
     */
    qint64 get_total_time(bool return_stored_only = false) const;

    /**
     * @return True if work of this was ever interrupted.
     */
    bool was_interrupted() const;
};
