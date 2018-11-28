//
// Created by domen on 24.11.2018.
//

#pragma once
#pragma clang diagnostic push
// Tests use top level macro, probably global variables. We suppress compiler warnings.
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "test_util/tests_h_common.h"

typedef MockDateTime ft;

TEST(totalTimes, startsAtZero) {
    auto& app = (*mk::pomodoro_timer_app());
    for (int i = 0; i < POMODORO_STATE_NUM_ELEMENTS; ++i) {
        ASSERT_EQ(app.get_total_elapsed_time_of_kind(static_cast<PomodoroState>(i)), 0LL);
    }
}

TEST(totalTimes, workTimeElapsesCorrectly) {
    auto& app = (*mk::pomodoro_timer_app());
    ft::addMinutes(2);
    auto te = app.get_total_elapsed_time_of_kind(PomodoroState::WORK);
    ASSERT_EQ(con::as_minutes(te), 2);
    ft::addSeconds(18);
    ASSERT_EQ(con::as_qtime(app.get_total_elapsed_time_of_kind(PomodoroState::WORK)), QTime(0, 2, 18, 0));
}

TEST(totalTimes, pauseTimeCorrect) {
    auto& app = (*mk::pomodoro_timer_app());
    ft::addMinutes(27);
    ASSERT_EQ(con::as_minutes(app.get_total_elapsed_time_of_kind(PomodoroState::WORK)), 27);
    app.fireAction();
    ASSERT_EQ(con::as_minutes(app.get_total_elapsed_time_of_kind(PomodoroState::WORK)), 27);
    ft::addSeconds(18);
    ASSERT_EQ(con::as_minutes(app.get_total_elapsed_time_of_kind(PomodoroState::WORK)), 27);
    ASSERT_EQ(con::as_seconds(app.get_total_elapsed_time_of_kind(PomodoroState::PAUSE)), 18);
    ASSERT_EQ(con::as_seconds(app.get_total_pause()), 18);

    app.fireAction();
    ASSERT_EQ(con::as_seconds(app.get_total_elapsed_time_of_kind(PomodoroState::LONG_PAUSE)), 0);
    ASSERT_EQ(con::as_seconds(app.get_total_elapsed_time_of_kind(PomodoroState::PAUSE)), 18);
    ASSERT_EQ(con::as_seconds(app.get_total_pause()), 18);
    ft::addMinutes(5);
    ASSERT_EQ(con::as_minutes(app.get_total_elapsed_time_of_kind(PomodoroState::WORK)), 32);
    ASSERT_EQ(con::as_seconds(app.get_total_pause()), 18);
    ASSERT_EQ(con::as_qtime(app.get_total_time()), QTime(0, 32, 18, 0));
}

TEST(totalTimes, testIfMyUtilCorrectlyAdvancesPomodori) {
    // Trivial case
    auto app = mk::pomodoro_timer_app(
            mk::initial_state{.current_pomodo_number = 0, .start_as_pause=false, .additional_time_to_advance=0});
    pcc::check_all_timers(app, {{PomodoroState::WORK, 0}}, __LINE__);

    delete app;
    app = mk::pomodoro_timer_app(
            mk::initial_state{.current_pomodo_number = 0, .start_as_pause=true, .additional_time_to_advance=0});
    pcc::check_all_timers(app, {{PomodoroState::WORK, 25 * 60 * 1000}, {eps::LONG_PAUSE, 0}, {PomodoroState::PAUSE, 0}},
            __LINE__);

    delete app;
    app = mk::pomodoro_timer_app(
            mk::initial_state{.current_pomodo_number = 1, .start_as_pause=false, .additional_time_to_advance=0});
    pcc::check_all_timers(app,
            {{PomodoroState::WORK, 25 * 60 * 1000}, {eps::LONG_PAUSE, 0}, {PomodoroState::PAUSE, 5 * 60 * 1000}},
            __LINE__);

    delete app;
    app = mk::pomodoro_timer_app(
            mk::initial_state{.current_pomodo_number = 1, .start_as_pause=true, .additional_time_to_advance=8177});
    pcc::check_all_timers(app,
            {{eps::WORK, 2 * 25 * 60 * 1000}, {eps::LONG_PAUSE, 0}, {eps::PAUSE, 5 * 60 * 1000 + 8177}}, __LINE__);

    delete app;
    app = mk::pomodoro_timer_app(
            mk::initial_state{.current_pomodo_number = 2, .start_as_pause=true, .additional_time_to_advance=0});
    pcc::check_all_timers(app,
            {{eps::WORK, 3 * 25 * 60 * 1000}, {eps::LONG_PAUSE, 0}, {eps::PAUSE, 2 * 5 * 60 * 1000},
                    {eps::INTERRUPTED, 0}}, __LINE__);

//    delete app;
//    app = mk::pomodoro_timer_app(mk::initial_state{.current_pomodo_number = 3, .start_as_pause=false, .additional_time_to_advance=0});
//    pcc::check_all_timers(app, {{eps::WORK, 3*25*60*1000}, {eps::LONG_PAUSE, 0}}, __LINE__);

}

TEST(totalTimes, correctlyEnablesLongPause) {
    auto app = mk::pomodoro_timer_app(
            mk::initial_state{.current_pomodo_number = 3, .start_as_pause=false, .additional_time_to_advance=0});
    ASSERT_TRUE(app->is_current_pomodoro_long_pause());
    mk::advance_pomodoro(app, false);
    ASSERT_EQ(app->get_current_state(), eps::LONG_PAUSE);

    delete app;
    app = mk::pomodoro_timer_app(
            mk::initial_state{.current_pomodo_number = 3, .start_as_pause=true, .additional_time_to_advance=0});
    ASSERT_EQ(app->get_current_state(), eps::LONG_PAUSE);
}

TEST(totalTimes, enterLongPauseAsZero) {

    auto app = mk::pomodoro_timer_app(mk::initial_state{.settings={.time_work=25, .time_pause=5, .time_long_pause=15,
            .long_break_number=2}, .current_pomodo_number=0, .start_as_pause=true, .additional_time_to_advance=5});
    pcc::check_all_timers(app, {{PomodoroState::WORK, 25}, {eps::PAUSE, 5}, {eps::LONG_PAUSE, 0}}, __LINE__);
    ASSERT_FALSE(app->is_current_pomodoro_long_pause());
    app->fireAction();
    ASSERT_TRUE(app->is_current_pomodoro_long_pause());
    pcc::check_all_timers(app, {{PomodoroState::WORK, 25}, {eps::PAUSE, 5}, {eps::LONG_PAUSE, 0}}, __LINE__);
}

TEST(totalTimes, allTimesCorrectIncludingLongPause) {

    auto app_delayed_long_pause = mk::pomodoro_timer_app(
            mk::initial_state{.settings={.long_break_number=6}, .current_pomodo_number = 3, .start_as_pause=true, .additional_time_to_advance=0});
    pcc::check_all_timers(app_delayed_long_pause,
            {{PomodoroState::WORK, 25 * 4 * 60 * 1000}, {eps::PAUSE, 5 * 3 * 60 * 1000},
                    {eps::LONG_PAUSE, 0}}, __LINE__);
    delete app_delayed_long_pause;

    auto app = mk::pomodoro_timer_app(mk::initial_state{.settings={.time_work=25, .time_pause=5, .time_long_pause=15,
            .long_break_number=4}, .current_pomodo_number=3, .start_as_pause=true, .additional_time_to_advance=5});
    pcc::check_all_timers(app, {{eps::WORK, 25 * 4}, {eps::PAUSE, 5 * 3}, {eps::LONG_PAUSE, 5}}, __LINE__);

    MockDateTime::addMs(2);
    ASSERT_EQ(app->get_total_pause(), 5 * 3 + 5 + 2);
    ASSERT_EQ(app->get_total_elapsed_time_of_kind(eps::LONG_PAUSE), 5 + 2);
    app->fireAction();
    mk::advance_pomodoro(app, false, 1);

    ASSERT_EQ(app->get_current_state(), eps::PAUSE);
    ASSERT_EQ(app->get_main_timer_value(), 5);
}

TEST(totalTimes, multipleLongPausesActivated) {

    auto app = mk::pomodoro_timer_app(mk::initial_state{.settings={.time_work=25, .time_pause=5, .time_long_pause=15,
            .long_break_number=3}, .current_pomodo_number=7, .start_as_pause=true, .additional_time_to_advance=0});
    // Pomodori: 0,1,2_L,3,4,5_L,6,7
    pcc::check_all_timers(app, {{eps::WORK, 25 * 8}, {eps::PAUSE, 5 * 5}, {eps::LONG_PAUSE, 30}}, __LINE__);

    mk::advance_pomodoro(app);  // 8_l
    ft::addMs(3);
    pcc::check_all_timers(app, {{eps::WORK, 25 * 9}, {eps::PAUSE, 6 * 5}, {eps::LONG_PAUSE, 33}}, __LINE__);
    ASSERT_EQ(app->get_total_pause(), 6 * 5 + 33);
    ASSERT_EQ(app->get_total_time(), (25 * 9 + 6 * 5 + 33));
}

#pragma clang diagnostic pop