//
// Created by domen on 25.11.2018.
//

#pragma once
#include "tests_h_common.h"

namespace pcc {

    void check_all_timers(PomodoroSession const* const session, std::map<PomodoroState, qint64> const& checks,
            int line_number = 0, const char* const additional_message = "") {
        int cn = -1;
        for (auto const& x : checks) {
            ++ cn;
            ASSERT_EQ(session->get_total_elapsed_time_of_kind(x.first), x.second)
                                    << additional_message << " Check: " << cn
                                    << (line_number > 0 ? " Line: " + std::to_string(line_number) : "");
        }
    }
}