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
    qint8 sessionsForBigPause{};
    const qint8 long_break_number;
	std::vector<Pomodoro> pomodori_;
    Pomodoro* current_pomodoro_;
    std::array<qint64,POMODORO_STATE_NUM_ELEMENTS> elapsed_times_{};
    mutable std::pair<Pomodoro*, int> cache_short_pauses_done{};
    mutable std::pair<Pomodoro*, int> cache_long_pauses_done{};
    mutable std::pair<Pomodoro*, int> cache_interrupted_pomodori{};
    mutable std::pair<Pomodoro*, int> cache_non_interrupted_pomodori{};


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
	int count_pomodori_with(bool (*predicate) (Pomodoro const * const)) const;
	int calculate_pauses() const;
	int calculate_long_pauses() const;
	int calculate_interrupted_pomodori() const;
	int calculate_non_interrupted_pomodori() const;
    template <typename integer_type>
    qint64 handle_cache (std::pair<Pomodoro*, integer_type> & variable, integer_type (PomodoroSession::*) () const) const;

public:
    const std::map<PomodoroState, qint64> time_for_task_;

    explicit PomodoroSession(PomodoroSessionSettings const & settings = {});
    inline bool is_current_pomodoro_long_pause() const;
	void initialize() override;
	qint64 get_main_timer_value() override;
	QString saveState() override;
	void restore(const QString &state) override;
    void fireAction() override;
    qint64 get_total_elapsed_time_of_kind(PomodoroState kind) const override;
    qint64 get_total_pause() const override;
    qint64 get_total_time() const override;
    PomodoroState get_current_state() const override;
    int get_pomodori_done() const override;
    int get_short_pauses_done() const override;
    int get_long_pauses_done() const override;
    qint64 get_total_non_interrupted_time() const override;
    qint64 get_session_start_time() const override;
    int get_interrupted_pomodori() const override;
    int get_non_interrupted_pomodori() const override;
};


inline qint64 PomodoroSession::calculate_elapsed_time_for_current_run() const {
    return dt::currentTimeMs() - current_phase_start_timestamp_;
}

inline qint64 PomodoroSession::calculate_elapsed_time_for_current_run(qint64 timestamp_override) const {
    return timestamp_override - current_phase_start_timestamp_;
}

inline bool PomodoroSession::is_current_pomodoro_long_pause() const {
    return current_pomodoro_->is_long_pause;
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

template <typename settings_type>
Session* const Session::create(const ApplicationMode& mode, settings_type const * const settings_structure) {
    switch (mode) {
    case ApplicationMode::POMODORO_TIMER:
        if (settings_structure != nullptr) {
            return new PomodoroSession(*settings_structure);
        } else {
            return new PomodoroSession;
        }

        //	case ApplicationMode::STOPWATCH:
    default:
        throw std::logic_error("Stopwatch mode not implemented");
    }
}