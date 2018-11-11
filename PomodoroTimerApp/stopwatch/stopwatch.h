//
// Created by domen on 05/11/18.
//

#ifndef POMODOROTIMER_STOPWATCH_H
#define POMODOROTIMER_STOPWATCH_H


#include <PomodoroTimerApp/pomodoro/Session.h>

class stopwatch : public Session {

    PomodoroState state;

    qint64 start_time;
    qint64 pause_start_time;
    qint64 total_pause;
    qint64 pause_display_timestamp;

public:
    stopwatch();


    qint64 getTaskTimeMs() const override;

    QString decide() override;

    QString reset() override;

    QString saveState() override;

    void restore(const QString &state) override;

    void beginPause() override;
};


#endif //POMODOROTIMER_STOPWATCH_H
