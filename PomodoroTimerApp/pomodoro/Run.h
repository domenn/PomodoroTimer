//
// Created by domen on 31/10/18.
//

#ifndef POMODOROTIMER_RUN_H
#define POMODOROTIMER_RUN_H

#include <QtCore/QDateTime>
#include <QtCore/QElapsedTimer>
#include "PomodoroState.h"

class Run {

    qint64 startTime;
    QElapsedTimer timer;
    const PomodoroState state;
    qint64 plannedWorkTime;
    qint64 actualWorkTime;

public:
    const PomodoroState & getState() const {return state;}
    explicit Run(const PomodoroState & pomodoroState, qint64 remainingTime = -1);
    qint64 remainingTimeMs() const;
    void finish();

    qint64 defaultRemainingTime(const PomodoroState &state) const;
};


#endif //POMODOROTIMER_RUN_H
