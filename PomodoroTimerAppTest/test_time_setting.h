//
// Created by domen on 30.11.2018.
//

#pragma once
#include <PomodoroTimerApp/application/application_settings/time_setting.h>
#include <QtWidgets/QLineEdit>
#include "test_util/tests_h_common.h"

#include <iostream>

// Underlying functionality is subject to change, this test might become irelevant.
TEST(timeSettingObject, getValue) {
    char* argv1[]{(char*) "app", (char*) "--stopwatch"};
    int argc = 2;
    QApplication a(argc, argv1);

    TimeSetting setting;

    QTime tm(1, 3, 44, 331);
    setting.create_widget("1:03:44:331");
    ASSERT_EQ(tm.msecsSinceStartOfDay(), setting.widget_to_value());
    auto widg_polymorphic = setting.create_widget(tm.msecsSinceStartOfDay());
    auto widg = dynamic_cast<QLineEdit*>(widg_polymorphic);
    ASSERT_EQ("01:03:44:331", widg->text());

    widg->setText("1:3:44:331");

    ASSERT_EQ(tm.msecsSinceStartOfDay(), setting.widget_to_value());
//
    // mm:ss:xxx
    tm.setHMS(0, 16, 44, 31);
    widg->setText("16:44:031");
    ASSERT_EQ(tm.msecsSinceStartOfDay(), setting.widget_to_value());

    delete widg;
    widg = dynamic_cast<QLineEdit*>(setting.create_widget(tm.msecsSinceStartOfDay()));
    ASSERT_EQ("16:44:031", widg->text());

    // mm:ss
    tm.setHMS(0, 2, 7);
    widg->setText("2:7");
    ASSERT_EQ(tm.msecsSinceStartOfDay(), setting.widget_to_value());

    delete widg;
    widg = dynamic_cast<QLineEdit*>(setting.create_widget(tm.msecsSinceStartOfDay()));
    ASSERT_EQ("02:07", widg->text());

    // hh:mm:ss
    widg->setText("16:44:31");
    tm.setHMS(16, 44, 31, 0);
    ASSERT_EQ(tm.msecsSinceStartOfDay(), setting.widget_to_value());

    delete widg;
    widg = dynamic_cast<QLineEdit*>(setting.create_widget(tm.msecsSinceStartOfDay()));
    ASSERT_EQ("16:44:31", widg->text());
//
    // AssumeMinutes
    widg->setText("211");
    tm.setHMS(3, 31, 0, 0);
    ASSERT_EQ(tm.msecsSinceStartOfDay(), setting.widget_to_value());

    delete widg;
    widg = dynamic_cast<QLineEdit*>(setting.create_widget(tm.msecsSinceStartOfDay()));
    ASSERT_EQ("03:31:00", widg->text());


    // OnlyDisplayMinutes
    widg->setText("39");
    tm.setHMS(0, 39, 0, 0);
    ASSERT_EQ(tm.msecsSinceStartOfDay(), setting.widget_to_value());

    delete widg;
    widg = dynamic_cast<QLineEdit*>(setting.create_widget(tm.msecsSinceStartOfDay()));
    ASSERT_EQ("39", widg->text());
}