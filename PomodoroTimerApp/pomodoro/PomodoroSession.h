//
// Created by domen on 23. 11. 2018.
//
#pragma once

#include "../application/Session.h"

class PomodoroSession : public Session {

	const qint64 TIME_WORK = 1000 * 60 * 25;
	const qint64 TIME_PAUSE = 1000 * 60 * 5;
	const qint64 TIME_LONG_PAUSE = 1000 * 60 * 15;

	void startNewPomodoro();

public:
	void initialize() override;
	qint64 getMainTimerValue() override;
	QString saveState() override;
	void restore(const QString &state) override;
};


