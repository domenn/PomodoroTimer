//
// Created by domen on 24.11.2018.
//

#pragma once
#pragma clang diagnostic push
// Tests use top level macro, probably global variables. We suppress compiler warnings.
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "test_util/tests_h_common.h"

TEST(interface, initialFieldValues) {
    auto tm = ft::getTime();
    auto app = mk::pomodoro_timer_app(mk::initial_state{{.time_work=100, .time_pause=20},
            .additional_time_to_advance=35});

    ASSERT_EQ(app->get_pomodori_done(), 0);
    ASSERT_EQ(app->get_short_pauses_done(), 0);
    ASSERT_EQ(app->get_long_pauses_done(), 0);
    ASSERT_EQ(app->get_total_non_interrupted_time(), 35);
    ASSERT_EQ(app->get_session_start_time(), tm);
    ASSERT_EQ(app->get_total_elapsed_time_of_kind(PomodoroState::INTERRUPTED), 0);

}

TEST(interface, countsItemsCorrectly) {
    auto tm = ft::getTime();
    auto app = mk::pomodoro_timer_app(mk::initial_state{.settings={.time_work=25, .time_pause=5, .time_long_pause=15,
            .long_break_number=3}, .current_pomodo_number=7, .start_as_pause=true, .additional_time_to_advance=7});
    // Pomodori: 0,1,2_L,3,4,5_L,6,7
    pcc::check_all_timers(app, {{eps::WORK, 25 * 8}, {eps::PAUSE, 5 * 5 + 7}, {eps::LONG_PAUSE, 30}}, __LINE__);

    ASSERT_EQ(app->get_pomodori_done(), 7);
    ASSERT_EQ(app->get_short_pauses_done(), 5);
    ASSERT_EQ(app->get_long_pauses_done(), 2);
    ASSERT_EQ(app->get_total_non_interrupted_time(), app->get_total_time());
    ASSERT_EQ(app->get_session_start_time(), tm);
    ASSERT_EQ(app->get_interrupted_pomodori(), 0);
    ASSERT_EQ(app->get_total_elapsed_time_of_kind(PomodoroState::INTERRUPTED), 0);
    ASSERT_EQ(app->get_non_interrupted_pomodori(), app->get_pomodori_done());

    app->fireAction();
    ASSERT_EQ(app->get_current_state(), eps::WORK);
    ASSERT_EQ(app->get_pomodori_done(), 8);
    ASSERT_EQ(app->get_short_pauses_done(), 6);
    ASSERT_EQ(app->get_long_pauses_done(), 2);
    ASSERT_EQ(app->get_interrupted_pomodori(), 0);

    ft::addMs(3);
    app->fireAction();
    ft::addMs(30);
    app->fireAction();
    ft::addMs(25);
    ASSERT_EQ(app->get_current_state(), eps::WORK);
    ASSERT_EQ(app->get_pomodori_done(), 8);
    ASSERT_EQ(app->get_short_pauses_done(), 6);
    ASSERT_EQ(app->get_long_pauses_done(), 2);
    ASSERT_EQ(app->get_interrupted_pomodori(), 0);
    ASSERT_EQ(app->get_non_interrupted_pomodori(), app->get_pomodori_done());

    app->fireAction();
    mk::advance_pomodoro(app, false);
    ASSERT_EQ(app->get_current_state(), eps::WORK);
    ASSERT_EQ(app->get_main_timer_value(), 25);

    ASSERT_EQ(app->get_pomodori_done(), 9);
    ASSERT_EQ(app->get_short_pauses_done(), 6);
    ASSERT_EQ(app->get_long_pauses_done(), 3);
    ASSERT_EQ(app->get_interrupted_pomodori(), 1);
    ASSERT_EQ(app->get_non_interrupted_pomodori(), 8);

    pcc::check_all_timers(app, {{eps::WORK, 25 * 9 + 3}, {eps::PAUSE, 5 * 5 + 7}, {eps::LONG_PAUSE, 30 + 15},
            {eps::INTERRUPTED, 30}}, __LINE__);


//    ft::addMs(3);
//    pcc::check_all_timers(app, {{eps::WORK, 25 * 9}, {eps::PAUSE, 6 * 5}, {eps::LONG_PAUSE, 33}}, __LINE__);
//    ASSERT_EQ(app->get_total_pause(), 6 * 5 + 33);
//    ASSERT_EQ(app->get_total_time(), (25 * 9 + 6 * 5 + 33));
}

#pragma clang diagnostic pop