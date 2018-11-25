//
// Created by domen on 31/10/18.
//

#pragma once

// Note: Do not put empty lines or comment lines into following code.
constexpr auto M_PomodoroState_START_ITM = __LINE__;
enum class PomodoroState {
    WORK,
    PAUSE,
    LONG_PAUSE,
    INTERRUPTED
};
constexpr auto POMODORO_STATE_NUM_ELEMENTS = __LINE__ - M_PomodoroState_START_ITM - 3;
// Note: No-empty-line restriction ends here