//
// Created by domen on 24.11.2018.
//
#pragma once

#pragma clang diagnostic push
// Tests use top level macro, probably global variables. We suppress compiler warnings.
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "test_util/tests_h_common.h"
#define DEFAULT_TIME_VALUE 1262347200000

TEST(timeMocks, correct){
    MockDateTime::setTime();
    ASSERT_EQ(dt::currentTimeMs(), DEFAULT_TIME_VALUE);
}

TEST(timersCorrect, startsAt25Minutes) {
    MockDateTime::setTime();
    auto& app = (*mk::pomodoroTimerApp());
    auto timer = app.getMainTimerValue();
    ASSERT_EQ(con::as_minutes(timer), 25);
}

TEST(timersCorrect, countdownCorrect) {
    auto& app = (*mk::pomodoroTimerApp());
    MockDateTime::addMinutes(5);
    ASSERT_EQ(con::as_minutes(app.getMainTimerValue()), 20);
    MockDateTime::addSeconds(12);
    ASSERT_EQ(QTime(0, 19, 48), QTime(0, 19, 48));
    auto t1 = con::as_qtime(app.getMainTimerValue());
    auto t2 = QTime(0, 19, 48);
    ASSERT_EQ(t1, t2);
}


#ifdef TESTS_THAT_FAIL

TEST(switchCorrect, correctlySwitchesToPauseAndLongPause) {
    auto& app = (*mk::pomodoroTimerApp());
    MockDateTime::addMinutes(25);
    MockDateTime::addMs(1);
    // Timer is now below 0. FireAction should start the pause
    app.fireAction();
    // Pause is active, that means we have 5 minutes
    ASSERT_EQ(con::as_minutes(app.getMainTimerValue()), 5);
    MockDateTime::addMinutes(6);
    ASSERT_EQ(con::as_minutes(app.getMainTimerValue()), -1);
    delete &app;

    /*
     * Session 0 is first .. session 4 is fourth, must have extended pause.
     */
    auto& app1 = (*mk::pomodoroTimerApp());
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

    auto appMinutes = con::as_minutes(app1.getMainTimerValue());
    ASSERT_EQ(appMinutes, 15);
    // Expire some time
    MockDateTime::add_min_sec_ms(10,41,711);
    QTime expectedTime(0, 4, 18, (1000-711));
    auto actualTime = con::as_qtime(app1.getMainTimerValue());
    ASSERT_EQ(expectedTime, actualTime);
    MockDateTime::addMinutes(5);
    app1.fireAction();
    // Now should be in new work session after long pause.
    ASSERT_EQ(con::as_minutes(app1.getMainTimerValue()), 25);
    MockDateTime::addMinutes(26);
    app1.fireAction();
    // Entered first 5 minute pause
    ASSERT_EQ(con::as_minutes(app1.getMainTimerValue()), 5);
    for (int i = 0; i<3; ++i) {
        MockDateTime::addMinutes(6);
        app1.fireAction();
        MockDateTime::addMinutes(26);
        app1.fireAction();
    }
    // Entered 3 more pauses. One and two 5 min, third should be 15 min
    ASSERT_EQ(con::as_minutes(app1.getMainTimerValue()), 15);
    // Advance the pause and start new work interval
    MockDateTime::addMinutes(17);
    app1.fireAction();
    ASSERT_EQ(con::as_minutes(app1.getMainTimerValue()), 25);
    MockDateTime::addMinutes(26);
    app1.fireAction();
    // Should have entered the 5 minute pause again
    ASSERT_EQ(con::as_minutes(app1.getMainTimerValue()), 5);
}


TEST(canInterruptWork, mainTimerDoesntChange) {
    auto& app = (*mk::pomodoroTimerApp());
    am::advance_mins_and_test(&app, 4, 21);
    app.fireAction();
    // App should now be in interrupted state. After 12 minutes the timer should still be as previously
    MockDateTime::addMinutes(12);
    ASSERT_EQ(app.getMainTimerValue(), 21);
    app.fireAction();
    // Should be back in work ..The following call should only add 12 seconds, and not 12 minutes 12 seconds
    am::advance_seconds_and_test(app, 12, 20, 48);
}

#endif

#pragma clang diagnostic pop