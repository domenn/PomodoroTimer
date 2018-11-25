//
// Created by domen on 31/10/18.
//

#include <PomodoroTimerApp/utils/millisecondsToTimer.h>
#include <PomodoroTimerApp/pomodoro/PomodoroSession.h>
#include "Session.h"

template <typename settings_type>
Session* const Session::create(const ApplicationMode& mode, settings_type const * const settings_structure) {
	switch (mode) {
	case ApplicationMode::POMODORO_TIMER:
		if (settings_structure != nullptr) {
			return new PomodoroSession(*settings_structure);
		} else {
			return new PomodoroSession;
		}

		//	case ApplicationMode::STOPWATCH:
	default:
		throw std::logic_error("Stopwatch mode not implemented");
	}
}

Session* const Session::create(const ApplicationMode& mode) {
	return create<PomodoroSessionSettings>(mode, nullptr);
}