# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PomodoroTimerQtTesting
TEMPLATE = app

CONFIG += c++1z
# QMAKE_CXXFLAGS += -std=c++17

HEADERS = \
   $$PWD/PomodoroTimerApp/application/application_settings/application_setting.h \
   $$PWD/PomodoroTimerApp/application/application_settings/integer_setting.h \
   $$PWD/PomodoroTimerApp/application/application_settings/time_setting.h \
   $$PWD/PomodoroTimerApp/application/ApplicationMode.h \
   $$PWD/PomodoroTimerApp/application/Session.h \
   $$PWD/PomodoroTimerApp/gui/main_window.h \
   $$PWD/PomodoroTimerApp/gui/main_window_gui_builder.h \
   $$PWD/PomodoroTimerApp/gui/settings_dialog.h \
   $$PWD/PomodoroTimerApp/pomodoro/Pomodoro.h \
   $$PWD/PomodoroTimerApp/pomodoro/PomodoroSession.h \
   $$PWD/PomodoroTimerApp/pomodoro/PomodoroState.h \
   $$PWD/PomodoroTimerApp/stopwatch/stopwatch.h \
   $$PWD/PomodoroTimerApp/utils/app_directories.h \
   $$PWD/PomodoroTimerApp/utils/date_format_converter.h \
   $$PWD/PomodoroTimerApp/utils/millisecondsToTimer.h \
   $$PWD/PomodoroTimerApp/utils/mockable_datetime.h \
   $$PWD/PomodoroTimerApp/utils/PomodoroAppCommandLine.h

SOURCES = \
   $$PWD/PomodoroTimerApp/application/application_settings/application_setting.cpp \
   $$PWD/PomodoroTimerApp/application/application_settings/integer_setting.cpp \
   $$PWD/PomodoroTimerApp/application/application_settings/time_setting.cpp \
   $$PWD/PomodoroTimerApp/application/Session.cpp \
   $$PWD/PomodoroTimerApp/gui/main_window.cpp \
   $$PWD/PomodoroTimerApp/gui/main_window_gui_builder.cpp \
   $$PWD/PomodoroTimerApp/gui/settings_dialog.cpp \
   $$PWD/PomodoroTimerApp/pomodoro/Pomodoro.cpp \
   $$PWD/PomodoroTimerApp/pomodoro/PomodoroSession.cpp \
   $$PWD/PomodoroTimerApp/stopwatch/stopwatch.cpp \
   $$PWD/PomodoroTimerApp/utils/millisecondsToTimer.cpp \
   $$PWD/PomodoroTimerApp/utils/PomodoroAppCommandLine.cpp \
   $$PWD/PomodoroTimerApp/main.cpp

INCLUDEPATH = \
    $$PWD \
    $$PWD/External/cpplogger/include
