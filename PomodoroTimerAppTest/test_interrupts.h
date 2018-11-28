//
// Created by domen on 24.11.2018.
//

#pragma once
#pragma clang diagnostic push
// Tests use top level macro, probably global variables. We suppress compiler warnings.
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "test_util/tests_h_common.h"

TEST(interruptions, canInterruptAndResumeInterruptedTimerCorrect) {
    auto& app = (*mk::pomodoro_timer_app(mk::initial_state{{.time_work=100, .time_pause=20},
            .additional_time_to_advance=35}));
    app.fireAction();
    ASSERT_EQ(app.get_current_state(), eps::INTERRUPTED);
    ft::addMs(35);
    pcc::check_all_timers(&app, {{eps::WORK, 35}, {eps::PAUSE, 0}, {eps::INTERRUPTED, 35}}, __LINE__);
    ASSERT_EQ(app.get_total_time(), 70);
    app.fireAction();
    ASSERT_EQ(app.get_current_state(), eps::WORK);
    ft::addMs(10);
    pcc::check_all_timers(&app, {{eps::WORK, 45}, {eps::PAUSE, 0}, {eps::INTERRUPTED, 35}}, __LINE__);

    ft::addMs(55);
    app.fireAction();
    ft::addMs(10);
    ASSERT_EQ(app.get_current_state(), eps::PAUSE);
    pcc::check_all_timers(&app, {{eps::WORK, 100}, {eps::PAUSE, 10}, {eps::INTERRUPTED, 35}}, __LINE__);

    app.fireAction();
    ASSERT_EQ(app.get_current_state(), eps::WORK);
    ft::addMs(20);
    pcc::check_all_timers(&app, {{eps::WORK, 120}, {eps::PAUSE, 10}, {eps::INTERRUPTED, 35}}, __LINE__);
    ASSERT_EQ(app.get_total_time(), 120+10+35);
}

TEST(interruptions, mainTimerDoesntChange) {
    auto& app = (*mk::pomodoro_timer_app(mk::initial_state{{.time_work=100, .time_pause=20},
            .additional_time_to_advance=0}));
    ft::addMs(10);
    ASSERT_EQ(app.get_main_timer_value(), 90);
    app.fireAction();
    ft::addMs(10);
    ASSERT_EQ(app.get_main_timer_value(), 90);
    app.fireAction();
    ft::addMs(10);
    ASSERT_EQ(app.get_main_timer_value(), 80);
}

TEST(cannotInterruptPause, mainTimerDoesntChange) {
    auto& app = (*mk::pomodoro_timer_app(mk::initial_state{{.time_work=100, .time_pause=20},
            .start_as_pause=true, .additional_time_to_advance=2}));
    app.fireAction();
    ASSERT_EQ(app.get_total_time(), 102);

    ft::addMs(2);
    ASSERT_EQ(app.get_total_time(), 104);
    pcc::check_all_timers(&app, {{eps::WORK, 102}, {eps::PAUSE, 2}, {eps::INTERRUPTED, 0}}, __LINE__);

    app.fireAction();
    ft::addMs(2);
    pcc::check_all_timers(&app, {{eps::WORK, 102}, {eps::PAUSE, 2}, {eps::INTERRUPTED, 2}}, __LINE__);
    ASSERT_EQ(app.get_total_time(), 106);
}

#pragma clang diagnostic pop