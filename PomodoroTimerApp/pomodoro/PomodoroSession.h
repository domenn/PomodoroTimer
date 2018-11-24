//
// Created by domen on 23. 11. 2018.
//
#pragma once

#include "../application/Session.h"
#include "PomodoroState.h"
#include "Pomodoro.h"
#include <map>
#include <vector>

class PomodoroSession : public Session {

	const qint64 TIME_WORK = 1000 * 60 * 25;
	const qint64 TIME_PAUSE = 1000 * 60 * 5;
	const qint64 TIME_LONG_PAUSE = 1000 * 60 * 15;
	const qint8 LONG_BREAK_NUMBER = 4;

	// Inherited: qint64 current_phase_start_timestamp;
	// Inherited: qint64 work_start_timestamp;
    PomodoroState state;
    qint8 sessionsForBigPause = 0;
	std::map<PomodoroState, qint64> timeForTask;
	std::vector<Pomodoro> pomodori_;
    Pomodoro* current_pomodoro_;


	void startNewPomodoro();
	bool timerExpired();
	QString selectPause();

public:
	void initialize() override;
	qint64 getMainTimerValue() override;
	QString saveState() override;
	void restore(const QString &state) override;
    QString decide() override;
};


