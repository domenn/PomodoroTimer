//
// Created by domen on 23. 11. 2018.
//
#pragma once

#include "../application/Session.h"
#include "PomodoroState.h"
#include "Pomodoro.h"
#include <PomodoroTimerApp/utils/mockable_datetime.h>
#include <map>
#include <vector>
#include <array>

struct PomodoroSessionSettings{
    const qint64 time_work{1000 * 60 * 25};
    const qint64 time_pause = 1000 * 60 * 5;
    const qint64 time_long_pause = 1000 * 60 * 15;
    const qint8 long_break_number = 4;
};

class PomodoroSession : public Session {

    // Inherited: qint64 current_phase_start_timestamp_;
	// Inherited: qint64 work_start_timestamp_;
    PomodoroState state;
    qint8 sessionsForBigPause = 0;
    const qint8 long_break_number;
	std::vector<Pomodoro> pomodori_;
    Pomodoro* current_pomodoro_;
    std::array<qint64,POMODORO_STATE_NUM_ELEMENTS> elapsed_times_{};


	void start_new_pomodoro(qint64 start_timestamp);
	void complete_pomodoro_and_start_next(qint64 timestamp_override);
	inline qint64 calculate_elapsed_time_for_current_run() const;
	/**
	 * @param timestamp_override Use this time instead of current system time.
	 * @return elapsed time for current non-written-into run (can be work, interrupt, ...)
	 */
	inline qint64 calculate_elapsed_time_for_current_run(qint64 timestamp_override) const;
    inline bool work_time_ran_out(qint64 current_time) const;
	inline void select_pause();

public:
    const std::map<PomodoroState, qint64> time_for_task_;

    explicit PomodoroSession(PomodoroSessionSettings const & settings = {});
    inline bool is_current_pomodoro_long_pause() const;
	void initialize() override;
	qint64 getMainTimerValue() override;
	QString saveState() override;
	void restore(const QString &state) override;
    void fireAction() override;
    qint64 get_total_elapsed_time_of_kind(PomodoroState kind) const override;
    qint64 get_total_pause() const override;
    qint64 get_total_time() const override;
    PomodoroState get_current_state() const override;


};


inline qint64 PomodoroSession::calculate_elapsed_time_for_current_run() const {
    return dt::currentTimeMs() - current_phase_start_timestamp_;
}

inline qint64 PomodoroSession::calculate_elapsed_time_for_current_run(qint64 timestamp_override) const {
    return timestamp_override - current_phase_start_timestamp_;
}

inline bool PomodoroSession::is_current_pomodoro_long_pause() const {
    return sessionsForBigPause == long_break_number - 1;
}

inline bool PomodoroSession::work_time_ran_out(qint64 current_time) const {
    return current_pomodoro_->get_time_of_kind(PomodoroState::WORK, current_time, true) >=
            time_for_task_.at(PomodoroState::WORK);
}

inline void PomodoroSession::select_pause() {
    ++sessionsForBigPause;
    if (sessionsForBigPause >= long_break_number) {
        sessionsForBigPause = 0;
        state = PomodoroState::LONG_PAUSE;
    } else {
        state = PomodoroState::PAUSE;
    }
}
