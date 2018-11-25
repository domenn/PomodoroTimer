//
// Created by domen on 24.11.2018.
//

#pragma once
#include <PomodoroTimerApp/pomodoro/PomodoroSession.h>
#include "tests_h_common.h"
#include <map>

namespace mk {

    struct initial_state {
        PomodoroSessionSettings settings{};
        short current_pomodo_number{0};

        bool start_as_pause{false};
        qint64 additional_time_to_advance{0};
    };

    /**
     * Note: returns dumb pointer to heap. For tests should be good enough.
     * @param start If true, starts the created session. If false, doesn't.
     * @return Pointer to created session (heap)
     */
    inline PomodoroSession* pomodoro_timer_app(const bool start = true, const PomodoroSessionSettings& settings = {}) {
        PomodoroSession* app = (PomodoroSession*) Session::create(ApplicationMode::POMODORO_TIMER, &settings);
        if (start) {
            app->initialize();
        }
        return app;
    }

    /**
    * Skipps the time and fires pomodoros, depending on parameters
    * @param session session to modify
    * @param full_pomodoro if true, advances full circle, lands at same state as started (example: from pause to pause)
    * @param how_many Number of advancments or (if full_pomodoro is false) half-advancments to do.
    */
    void advance_pomodoro(PomodoroSession* const session, bool const full_pomodoro = true, int const how_many = 1) {
        for (int i = 0; i < how_many * (full_pomodoro ? 2 : 1); ++i) {
            MockDateTime::addMs(static_cast<int>(session->time_for_task_.at(session->get_current_state())));
            session->fireAction();
        }
    }

    inline PomodoroSession* pomodoro_timer_app(initial_state const& initial_state_) {
        // TODO future: first make use of first four parameters to modify the values. Once the feture gets supported
        auto* app = pomodoro_timer_app(true, initial_state_.settings);
        advance_pomodoro(app, true, initial_state_.current_pomodo_number);

        if (initial_state_.start_as_pause) {
            if (app->get_current_state() != PomodoroState::PAUSE
                    || app->get_current_state() != PomodoroState::LONG_PAUSE) {
                advance_pomodoro(app, false);
            }
        }
        MockDateTime::addMs(static_cast<int>(initial_state_.additional_time_to_advance));
        return app;
    }
}