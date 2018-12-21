//
// Created by Domen on 20. 12. 2018.
//

#pragma once

#include <External/cpplogger/include/plog/Log.h>
#include <PomodoroTimerApp/utils/app_directories.h>
#include <External/cpplogger/include/plog/Appenders/ConsoleAppender.h>

#pragma once
inline void setup_logger(const QString& filename = "log.txt", const plog::Severity level = plog::info) {

    if (plog::get()) {
        return;
    }
	auto appender_file_name = app_directories::getDefaultLogFilePath(filename); //.toStdString();
	static plog::RollingFileAppender<plog::TxtFormatter> fileAppender(
            appender_file_name.toStdString().c_str() , 8000, 2); // Create the 1st appender.
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender; // Create the 2nd appender.

	plog::init(level, &fileAppender).addAppender(&consoleAppender);
}