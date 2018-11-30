//
// Created by domen on 30.11.2018.
//

#pragma once

#include "application_setting.h"

class IntegerSetting : public ApplicationSetting {

public:
    qint64 widget_to_value() override;
    QWidget* const create_widget(qint64 time_str) override;
    QWidget* const create_widget(QString const& string) override;

    IntegerSetting(const QString& gui_text, const QString& options_key);
};


