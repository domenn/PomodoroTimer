//
// Created by domen on 24.11.2018.
//

#pragma once
#pragma clang diagnostic push
// Tests use top level macro, probably global variables. We suppress compiler warnings.
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "gtest/gtest.h"
#include <PomodoroTimerApp/utils/mockable_datetime.h>
#include <PomodoroTimerApp/utils/date_format_converter.h>
#include <PomodoroTimerApp/pomodoro/Pomodoro.h>

TEST(pomodoro, canGetAndSetTimes) {
    constexpr qint64 TP = 1000;
    constexpr qint64 TLP = 2000;
    constexpr qint64 TI = 188;
    constexpr qint64 TW = 18114;
    constexpr qint64 TTP = TP + TLP;
    constexpr qint64 T_SUM_ALL = TTP + TI + TW;

    auto t_initial = MockDateTime::getTime();
    // Second value is irrelevant for this test
    Pomodoro pomodoro(t_initial, 0);
    pomodoro.add_time_of_kind(PomodoroState::PAUSE, TP);
    pomodoro.add_time_of_kind(PomodoroState::LONG_PAUSE, TLP);
    pomodoro.add_time_of_kind(PomodoroState::INTERRUPTED, TI);
    pomodoro.add_time_of_kind(PomodoroState::WORK, TW);

    ASSERT_EQ(TTP, pomodoro.get_time_of_kind(PomodoroState::PAUSE));
    ASSERT_EQ(TTP, pomodoro.get_time_of_kind(PomodoroState::LONG_PAUSE));
    ASSERT_EQ(TI, pomodoro.get_time_of_kind(PomodoroState::INTERRUPTED));
    ASSERT_EQ(TW, pomodoro.get_time_of_kind(PomodoroState::WORK));

    ASSERT_EQ(pomodoro.get_total_time(true), TTP + TI + TW);
    ASSERT_EQ(pomodoro.get_total_time(false), 0);
    MockDateTime::addMs(T_SUM_ALL);
    ASSERT_EQ(pomodoro.get_total_time(false), T_SUM_ALL);
    constexpr auto T_ADD = 10000LL;
    MockDateTime::addMs(T_ADD);

    ASSERT_EQ(pomodoro.get_total_time(false), TTP + TI + TW + T_ADD);
    ASSERT_EQ(pomodoro.get_total_time(true), TTP + TI + TW);


    // Just to be sure: current time minus start time equals total elapsed time
    constexpr auto TOTAL_ELAPSED_TIME = T_SUM_ALL + T_ADD;
    ASSERT_EQ(dt::currentTimeMs() - t_initial, TOTAL_ELAPSED_TIME);
    // Current time minus start time minus all elapsed parts except work must equal work time
    // But work time has T_ADD elapsed .. so it is DIFFERENT than stored in the object
    constexpr auto REAL_WORK_TIME = TW + T_ADD;
    ASSERT_EQ(TOTAL_ELAPSED_TIME - TTP - TI, REAL_WORK_TIME);

    // The following assert confirms the equality for special case, when State is WORK
    ASSERT_EQ(TOTAL_ELAPSED_TIME -
            pomodoro.get_time_of_kind(PomodoroState::INTERRUPTED) - pomodoro.get_time_of_kind(PomodoroState::PAUSE),
            REAL_WORK_TIME);
    // The following two asserts define generalised way to get the value of REAL_WORK_TIME
    ASSERT_EQ(T_ADD, TOTAL_ELAPSED_TIME - pomodoro.get_total_time(true));
    ASSERT_EQ(REAL_WORK_TIME, T_ADD + TW);
    // The above 3 asserts are implemented inside get_time_of_kind for parameter true

    // After time added, if we get stored time it is same as before. If we get running time (counts realtime), we get including added
    ASSERT_EQ(TW, pomodoro.get_time_of_kind(PomodoroState::WORK));
    ASSERT_EQ(REAL_WORK_TIME, pomodoro.get_time_of_kind(PomodoroState::WORK, true));

    ASSERT_EQ(TTP + T_ADD, pomodoro.get_time_of_kind(PomodoroState::PAUSE, true));
    ASSERT_EQ(TTP + T_ADD, pomodoro.get_time_of_kind(PomodoroState::LONG_PAUSE, true));
    ASSERT_EQ(TI + T_ADD, pomodoro.get_time_of_kind(PomodoroState::INTERRUPTED, true));

    constexpr auto ADD_WORK_TIME_TOTAL = T_ADD + 50;
    MockDateTime::addMs(50);
    ASSERT_EQ(TW + ADD_WORK_TIME_TOTAL, pomodoro.get_time_of_kind(PomodoroState::WORK, true));

    constexpr auto UPDATED_WORK_TIME = ADD_WORK_TIME_TOTAL + TW;
    pomodoro.add_time_of_kind(PomodoroState::WORK, ADD_WORK_TIME_TOTAL);
    ASSERT_EQ(UPDATED_WORK_TIME, pomodoro.get_time_of_kind(PomodoroState::WORK, false));
    ASSERT_EQ(pomodoro.get_time_of_kind(PomodoroState::WORK, false),pomodoro.get_time_of_kind(PomodoroState::WORK, true));

    // Simulate interruption for 12331 ms
    MockDateTime::addMs(12331);
    ASSERT_EQ(pomodoro.get_time_of_kind(PomodoroState::INTERRUPTED, true), TI + 12331);
    ASSERT_EQ(pomodoro.get_time_of_kind(PomodoroState::INTERRUPTED), TI);
}

#pragma clang diagnostic pop