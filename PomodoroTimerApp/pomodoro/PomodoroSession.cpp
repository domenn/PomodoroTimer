//
// Created by domen on 23. 11. 2018.
//

#include "PomodoroSession.h"

void PomodoroSession::start_new_pomodoro(qint64 start_timestamp) {
    current_phase_start_timestamp_ = start_timestamp;
    state = PomodoroState::WORK;
    auto make_long_pause = sessionsForBigPause == long_break_number - 1;
    pomodori_.emplace_back(current_phase_start_timestamp_,
            time_for_task_.at(make_long_pause? PomodoroState::LONG_PAUSE : PomodoroState::PAUSE), make_long_pause);

    current_pomodoro_ = &pomodori_.back();
}

void PomodoroSession::initialize() {
    work_start_timestamp_ = dt::currentTimeMs();
    start_new_pomodoro(work_start_timestamp_);
}

qint64 PomodoroSession::get_main_timer_value() {
    auto elapsed = state != PomodoroState::INTERRUPTED ? current_pomodoro_->get_time_of_kind(state, true)
            : current_pomodoro_->get_time_of_kind(PomodoroState::WORK);

    return this->time_for_task_.at(state) - elapsed;
}

QString PomodoroSession::saveState() {
    return QString();
}

void PomodoroSession::restore(const QString& state) {

}

void PomodoroSession::fireAction() {
    const auto timestamp_function_call = dt::currentTimeMs();
    current_pomodoro_->add_time_of_kind(state, calculate_elapsed_time_for_current_run(timestamp_function_call));
    switch (state) {
    case PomodoroState::WORK:
        if (work_time_ran_out(timestamp_function_call)) {
            select_pause();
        } else {
            state = PomodoroState::INTERRUPTED;
        }
        break;
    case PomodoroState::LONG_PAUSE:
    case PomodoroState::PAUSE:
        complete_pomodoro_and_start_next(timestamp_function_call);
        break;
    case PomodoroState::INTERRUPTED:
        state = PomodoroState::WORK;
        break;
    }
    current_phase_start_timestamp_ = timestamp_function_call;
}

PomodoroSession::PomodoroSession(PomodoroSessionSettings const& settings)
        :time_for_task_({{PomodoroState::PAUSE, settings.time_pause},
        {PomodoroState::WORK, settings.time_work},
        {PomodoroState::LONG_PAUSE, settings.time_long_pause},
        // Interrupted is basically work, so planned time is same
        {PomodoroState::INTERRUPTED, settings.time_work}}),
         long_break_number(settings.long_break_number) { }

qint64 PomodoroSession::get_total_elapsed_time_of_kind(PomodoroState kind) const {
    return elapsed_times_[static_cast<int>(kind)] + (kind == state ? calculate_elapsed_time_for_current_run() : 0)
            + current_pomodoro_->get_time_of_kind(kind);
}

qint64 PomodoroSession::get_total_pause() const {
    return get_total_elapsed_time_of_kind(PomodoroState::LONG_PAUSE)
            + get_total_elapsed_time_of_kind(PomodoroState::PAUSE);
}

void PomodoroSession::complete_pomodoro_and_start_next(const qint64 timestamp_override) {
    elapsed_times_[static_cast<int>(PomodoroState::WORK)] += current_pomodoro_->get_time_of_kind(PomodoroState::WORK);
    elapsed_times_[static_cast<int>(PomodoroState::INTERRUPTED)] += current_pomodoro_
            ->get_time_of_kind(PomodoroState::INTERRUPTED);
    const auto which_pause = current_pomodoro_->is_long_pause ? PomodoroState::LONG_PAUSE : PomodoroState::PAUSE;
    elapsed_times_[static_cast<int>(which_pause)] += current_pomodoro_->get_time_of_kind(PomodoroState::PAUSE);
    start_new_pomodoro(timestamp_override);
}

qint64 PomodoroSession::get_total_time() const {
    return dt::currentTimeMs() - work_start_timestamp_;
}

PomodoroState PomodoroSession::get_current_state() const {
    return state;
}