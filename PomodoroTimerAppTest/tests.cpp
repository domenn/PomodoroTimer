//
// Created by domen on 23. 11. 2018.
//


#include "test_cmdline_parser.h"
#include "test_main_timer_values.h"
#include "test_total_elapsed_times.h"
#include "test_pomodoro.h"



qint64 MockDateTime::currentMillisecondsTime = DEFAULT_TIME_VALUE;

TEST(runningInTestMode, true){
    bool tests = false;
#ifdef RUNNING_POMODORO_TESTS
    tests = true;
#endif
    ASSERT_TRUE(tests);
}

/*
 * NOTE: Test for pause switch is failing.
 * Next: will first make tests for total times. For example: start the app, advance 2 minutes .. total time should now be
 * 2 minute work. Advance another 25 min .. now 27 min. work.
 * If I fire then, I have 27 min. work and 0 pause. 2 minute advance, now I have 2 min. total pause, 27 work, 29 total.
 * Idea: when new pomodoro starts, increment old values to current in session, so no need to traverse vector each time.
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}