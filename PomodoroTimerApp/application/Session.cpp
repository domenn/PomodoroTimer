//
// Created by domen on 31/10/18.
//

#include <PomodoroTimerApp/utils/millisecondsToTimer.h>
#include <PomodoroTimerApp/pomodoro/PomodoroSession.h>
#include "Session.h"

Session::Session() {
}

void Session::beginWork() {

    run_history.emplace_back(PomodoroState::WORK);
    current_run = &run_history.back();
}

void Session::interrupt() {

}

QString Session::decide() {
    // REFACTOR: find a way to handle return values .. strings
    if (current_run == nullptr){
        beginWorkInitial();
        return "Pause";
    }
    switch (current_run->getState()){
        case PomodoroState::WORK:
            interrupt();
            return "Resume";
        case PomodoroState::INTERRUPTED:
            resumeInterrupt();
            return "Pause";
        case PomodoroState::LONG_PAUSE:
        case PomodoroState::PAUSE:
            return "Pause";
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

QString Session::reset() {
    return "Not Implemented";
}

QString Session::saveState() {
    return "Not Implemented";
}

void Session::restore(const QString &state) {

}

Session *const Session::create(const ApplicationMode &mode) {
    switch (mode){
        case ApplicationMode ::POMODORO_TIMER:
            return new PomodoroSession;
        case ApplicationMode::STOPWATCH:
            throw std::logic_error("Stopwatch mode not implemented");
    }
}