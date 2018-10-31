//
// Created by domen on 31/10/18.
//

#include <PomodoroTimerApp/utils/millisecondsToTimer.h>
#include "Session.h"

Session::Session() {
}

void Session::beginWork() {

    run_history.emplace_back(PomodoroState::WORK);
    current_run = &run_history.back();
}

void Session::interrupt() {

}

void Session::decide() {
    if (current_run == nullptr){
        beginWorkInitial();
        return;
    }
    switch (current_run->getState()){
        case PomodoroState::WORK:
            interrupt();
            break;
        case PomodoroState::INTERRUPTED:
            resumeInterrupt();
            break;
        case PomodoroState::LONG_PAUSE:
        case PomodoroState::PAUSE:
            beginWork();
    }
}

void Session::beginWorkInitial() {
    run_history.emplace_back(PomodoroState::WORK);
    current_run = &run_history.back();
}

void Session::resumeInterrupt() {

}

void Session::beginPause() {

}

void Session::beginLongPause() {

}

qint64 Session::getTaskTimeMs() const {
    return current_run->remainingTimeMs();
}
