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
    const qint64 start_timestamp_;
    const qint64 planned_pause_time_;
    qint64 running_time_{};
    qint64 pause_time_{};
    qint64 interrupt_time{};
    const std::map<PomodoroState, qint64*> map_;

public:

    /**
     * Creating new Pomodoro automatically starts it in work mode.
     * @param start_timestamp Start time of this pomodoro
     * @param pause_time planned pause time for this one in milliseconds
     */
    Pomodoro(qint64 start_timestamp, qint64 planned_pause_time);

    /**
     * Increments time for what_kind by how_much
     * @param what_kind state to add
     * @param how_much time in ms
     */
    void add_time_of_kind(PomodoroState what_kind, qint64 how_much);

    /**
     * @param what_kind PomodoroState type to return .. pause, interrupt or work.
     * @param is_current_time is current state equals to state that is being returned.
     * If true, the difference between start time and current time will be added.
     * @return Time in ms for state of choice
     */
    qint64 get_time_of_kind(PomodoroState what_kind, bool is_current_state = false) const;

    /**
     * @param return_stored_only If true, only stored time is returned. If false, returns time difference between start of this pmodoro and now.
     * @return Total elapsed time for this pomodoro, sum of all.
     */
    qint64 get_total_time(bool return_stored_only = false) const;
};
