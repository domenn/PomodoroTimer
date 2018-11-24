//
// Created by domen on 24.11.2018.
//

#pragma once

namespace am{

    inline void _test_app_time_(Application& app, int t_min, int s, int ms){
        QTime expectedTime(0, t_min, s, ms);
        auto actualTime = con::as_qtime(app.getMainTimerValue());
        ASSERT_EQ(expectedTime, actualTime);
    }

    inline void advance_mins_and_test(Application& app, int min, int t_min, int s = 0, int ms = 0){
        MockDateTime::addMinutes(min);
        _test_app_time_(app, t_min, s, ms);
    }

    inline void advance_seconds_and_test(Application& app, int s, int t_min, int t_s = 0, int t_ms = 0){
        MockDateTime::addSeconds(s);
        _test_app_time_(app, t_min, t_s, t_ms);
    }
}