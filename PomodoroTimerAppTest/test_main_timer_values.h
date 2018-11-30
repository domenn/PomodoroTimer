//
// Created by domen on 24.11.2018.
//
#pragma once

#pragma clang diagnostic push
// Tests use top level macro, probably global variables. We suppress compiler warnings.
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "test_util/tests_h_common.h"

TEST(timeMocks, correct){
    MockDateTime::setTime();
    ASSERT_EQ(dt::currentTimeMs(), DEFAULT_TIME_VALUE);
}

TEST(timersCorrect, startsAt25Minutes) {
    MockDateTime::setTime();
    auto& app = (*mk::pomodoro_timer_app());
    auto timer = app.get_main_timer_value();
    ASSERT_EQ(con::as_minutes(timer), 25);
}

TEST(timersCorrect, countdownCorrect) {
    auto& app = (*mk::pomodoro_timer_app());
    MockDateTime::addMinutes(5);
    ASSERT_EQ(con::as_minutes(app.get_main_timer_value()), 20);
    MockDateTime::addSeconds(12);
    ASSERT_EQ(QTime(0, 19, 48), QTime(0, 19, 48));
    auto t1 = con::as_qtime(app.get_main_timer_value());
    auto t2 = QTime(0, 19, 48);
    ASSERT_EQ(t1, t2);
}

TEST(timersCorrect, correctTimersInPauseAndLongPause) {
    auto& app = (*mk::pomodoro_timer_app());
    MockDateTime::addMinutes(25);
    // Timer is now below 0. FireAction should start the pause
    app.fireAction();
    // Pause is active, that means we have 5 minutes
    ASSERT_EQ(con::as_minutes(app.get_main_timer_value()), 5);
    MockDateTime::addMinutes(6);
    ASSERT_EQ(con::as_minutes(app.get_main_timer_value()), -1);
    delete &app;

    /*
     * Session 0 is first .. session 4 is fourth, must have extended pause.
     */
    auto& app1 = (*mk::pomodoro_timer_app());
    int activeSession = 0;
    for (int i = 0; i<3; ++i) {
        MockDateTime::addMinutes(26);
        app1.fireAction();
        // state is pause
        MockDateTime::addMinutes(6);
        app1.fireAction();
        ++ activeSession;
        // state is work
    }
    ASSERT_EQ(activeSession, 3);
    MockDateTime::addMinutes(26);
    app1.fireAction();

    auto appMinutes = con::as_minutes(app1.get_main_timer_value());
    // Now in long pause, timer should be at 15 minutes
    ASSERT_EQ(appMinutes, 15);
    // Expire some time
    MockDateTime::add_min_sec_ms(10,41,711);
    QTime expectedTime(0, 4, 18, (1000-711));
    auto actualTime = con::as_qtime(app1.get_main_timer_value());
    ASSERT_EQ(expectedTime, actualTime);
    MockDateTime::addMinutes(5);
    app1.fireAction();
    // Now should be in new work session after long pause.
    ASSERT_EQ(con::as_minutes(app1.get_main_timer_value()), 25);
    MockDateTime::addMinutes(26);
    app1.fireAction();
    // Entered first 5 minute pause
    ASSERT_EQ(con::as_minutes(app1.get_main_timer_value()), 5);
    for (int i = 0; i<3; ++i) {
        MockDateTime::addMinutes(6);
        app1.fireAction();
        MockDateTime::addMinutes(26);
        app1.fireAction();
    }
    // Entered 3 more pauses. One and two 5 min, third should be 15 min
    ASSERT_EQ(con::as_minutes(app1.get_main_timer_value()), 15);
    // Advance the pause and start new work interval
    MockDateTime::addMinutes(17);
    app1.fireAction();
    ASSERT_EQ(con::as_minutes(app1.get_main_timer_value()), 25);
    MockDateTime::addMinutes(26);
    app1.fireAction();
    // Should have entered the 5 minute pause again
    ASSERT_EQ(con::as_minutes(app1.get_main_timer_value()), 5);
}

#pragma clang diagnostic pop