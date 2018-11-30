//
// Created by domen on 30.11.2018.
//

#include <QtWidgets/QLineEdit>
#include "integer_setting.h"



QWidget* const IntegerSetting::create_widget(const qint64 number) {
    return create_widget(QString::number(number, 10));
}

QWidget* const IntegerSetting::create_widget(QString const& string) {
    widget = new QLineEdit(string);
    return widget;
}

IntegerSetting::IntegerSetting(const QString& gui_text, const QString& options_key)
        :ApplicationSetting(gui_text, options_key) { }

qint64 IntegerSetting::widget_to_value() {
    if (!widget) {
        return value = 0;
    }
    auto widg = dynamic_cast<QLineEdit*> (widget);
    auto input = widg->text();
    bool conv_ok = false;
    auto number = input.toInt(&conv_ok);
    if (conv_ok) {
        // Single number -- assume minutes
        return value = number;
    }
    return value = 0;
}


