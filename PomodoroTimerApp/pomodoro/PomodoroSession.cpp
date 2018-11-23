//
// Created by domen on 23. 11. 2018.
//

#include "PomodoroSession.h"

void PomodoroSession::startNewPomodoro()
{
	current_phase_start_timestamp = QDateTime::currentMSecsSinceEpoch();
}

void PomodoroSession::initialize()
{
	work_start_timestamp = QDateTime::currentMSecsSinceEpoch();
	startNewPomodoro();
}

qint64 PomodoroSession::getMainTimerValue()
{
	// We have phase .. start time for phase. We use currentTime - startTime. That gives elapsed.
	// I do predicted - elapsed to get the timer.
	
	// TODO: Currently hardcoded for the work mode. Should add decision for other .. pause and stuff.

	auto timeForTask = QDateTime::currentMSecsSinceEpoch() - current_phase_start_timestamp;
	return TIME_WORK - timeForTask;
}

QString PomodoroSession::saveState() {
    return QString();
}

void PomodoroSession::restore(const QString &state) {

}
