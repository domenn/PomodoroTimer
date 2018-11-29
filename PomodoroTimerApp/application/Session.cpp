//
// Created by domen on 31/10/18.
//

#include <PomodoroTimerApp/pomodoro/PomodoroSession.h>
#include "Session.h"

Session* const Session::create(const ApplicationMode& mode) {
	return create<PomodoroSessionSettings>(mode, nullptr);
}