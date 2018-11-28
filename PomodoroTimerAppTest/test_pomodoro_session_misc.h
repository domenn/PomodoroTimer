//
// Created by domen on 25.11.2018.
//

#pragma once
#pragma clang diagnostic push
// Tests use top level macro, probably global variables. We suppress compiler warnings.
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "test_util/tests_h_common.h"

typedef MockDateTime ft;

TEST(pomodoroSettings, canModifyItemTimes){
    auto app = mk::pomodoro_timer_app(mk::initial_state{.settings={.time_work=con::min_to_ms(12),
            .time_pause=con::min_to_ms(4), .long_break_number=3}, .additional_time_to_advance=con::min_to_ms(4)});
    ASSERT_EQ(app->get_total_time(), con::min_to_ms(4));
    ft::addMinutes(8);
    app->fireAction();

    ASSERT_EQ(app->get_current_state(), eps::PAUSE);
    ASSERT_EQ(app->get_total_time(), con::min_to_ms(12));
    ft::addMinutes(4);
    app->fireAction();

    ASSERT_EQ(app->get_current_state(), eps::WORK);
    ASSERT_EQ(app->get_total_time(), con::min_to_ms(16));
    ASSERT_EQ(app->get_main_timer_value(), con::min_to_ms(12));
}

TEST(pomodoroSettings, canEnterLongPause){
    auto app = mk::pomodoro_timer_app(mk::initial_state{.settings={.time_work=con::min_to_ms(12),
            .time_pause=con::min_to_ms(4), .long_break_number=3}, .current_pomodo_number = 2, .start_as_pause=true, .additional_time_to_advance=1000 });
    ASSERT_EQ(app->get_current_state(), eps::LONG_PAUSE);
}


#pragma clang pop