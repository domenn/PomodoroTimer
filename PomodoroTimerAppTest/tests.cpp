//
// Created by domen on 23. 11. 2018.
//

#include "test_cmdline_parser.h"
#include "test_pomodoro.h"
#include "test_time_setting.h"
#ifndef _MSC_VER
#include "test_main_timer_values.h"
#include "test_pomodoro_session_misc.h"
#include "test_total_elapsed_times.h"
#include "test_interrupts.h"
#include "test_interface.h"
#endif




qint64 MockDateTime::currentMillisecondsTime = DEFAULT_TIME_VALUE;

TEST(runningInTestMode, true){
    bool tests = false;
#ifdef RUNNING_POMODORO_TESTS
    tests = true;
#endif
    ASSERT_TRUE(tests);
}

/*
 * Still missing (tests):
 * [OK] Long pause correctly counts seperate from normal pause.
 * [OK] Interrupts and not interrupts .. Do timers work correctly while interupt (no change on countdown. Interrupt timer ticking). Total time ticking.
 * [OK]  Interrupt can only be activated during pomodoro .. not pause.
 */

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
