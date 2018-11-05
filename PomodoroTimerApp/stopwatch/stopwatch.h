//
// Created by domen on 05/11/18.
//

#ifndef POMODOROTIMER_STOPWATCH_H
#define POMODOROTIMER_STOPWATCH_H


#include <PomodoroTimerApp/pomodoro/Session.h>

class stopwatch : public Session {

    PomodoroState state;

public:
    stopwatch();

    void decide() override;
};


#endif //POMODOROTIMER_STOPWATCH_H
