//
// Created by domen on 24.11.2018.
//
#pragma once

#include <QDateTime>

#ifdef RUNNING_POMODORO_TESTS

class MockDateTime {
    static qint64 currentMillisecondsTime; // = QDateTime::currentMSecsSinceEpoch();

public:

    MockDateTime() = delete;
    MockDateTime(MockDateTime&) = delete;

    static void setTime(int hour = 12, int minute = 00, int second = 00, int millisecond = 0, int year = 2010,
            int month = 1, int day = 1) {
        QDate date(year, month, day);
        QTime time(hour, minute, second, millisecond);
        QDateTime dt(date, time, Qt::UTC);
        currentMillisecondsTime = dt.toMSecsSinceEpoch();
    }

    static void addMinutes(int minute) {
        currentMillisecondsTime += minute*60*1000;
    }

    static void addSeconds(int s) {
        currentMillisecondsTime += s*1000;
    }

    static void addMs(int ms) {
        currentMillisecondsTime += ms;
    }

    static void add_min_sec_ms(int m, int s, int ms = 0) {
        addMinutes(m);
        addSeconds(s);
        addMs(ms);
    }

    static qint64 getTime() {
        return currentMillisecondsTime;
    }
};
namespace dt {
    inline qint64 currentTimeMs() {
        return MockDateTime::getTime();
    }
}
#else
namespace dt {
inline qint64 currentTimeMs(){
    return QDateTime::currentMSecsSinceEpoch();
}
}
#endif
