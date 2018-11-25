//
// Created by domen on 24.11.2018.
//

#pragma once
#pragma clang diagnostic push
// Tests use top level macro, probably global variables. We suppress compiler warnings.
#pragma ide diagnostic ignored "cert-err58-cpp"

#include "test_util/tests_h_common.h"

typedef MockDateTime ft;

TEST(totalTimes, workTime) {
    auto& app = (*mk::pomodoroTimerApp());
    ft::addMinutes(2);

}

#pragma clang diagnostic pop