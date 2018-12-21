//
// Created by domen on 30.11.2018.
//

#include <QtWidgets/QLineEdit>
#include <PomodoroTimerApp/utils/date_time_format_converter.h>
#include "time_setting.h"

QWidget* const TimeSetting::create_widget(const qint64 millis) {
    auto str_repr = con::interval_to_ms_string(millis, ":");
    if (str_repr.startsWith ("00:")){
        str_repr.remove(0, 3);
    }
    if (str_repr.length() == 5 && str_repr.endsWith(":00")) {
        str_repr.remove(2, 3);
    }
    return create_widget(str_repr);
}

TimeSetting::TimeSetting(const QString& gui_text, const QString& options_key, const QString& tooltip_text)
        :ApplicationSetting(gui_text, options_key, tooltip_text) { }

qint64 TimeSetting::widget_to_value() {
    if (!widget) {
        return value = 0;
    }
    auto widg = dynamic_cast<QLineEdit*> (widget);
    auto input = widg->text();
    bool conv_ok = false;
    auto number = input.toInt(&conv_ok);
    if (conv_ok) {
        // Single number -- assume minutes
        return value = con::items_to_ms(0, number, 0, 0);
    }
    auto pieces = input.split(":");
    if (pieces.size() == 4) {
        return value = con::items_to_ms(pieces[0].toInt(), pieces[1].toInt(), pieces[2].toInt(), pieces[3].toInt());
    }
    if (pieces.size() == 3) {
        if (pieces[2].size() == 3) {
            return value = con::items_to_ms(0, pieces[0].toInt(), pieces[1].toInt(), pieces[2].toInt());
        } else {
            return value = con::items_to_ms(pieces[0].toInt(), pieces[1].toInt(), pieces[2].toInt(), 0);
        }
    }
    if (pieces.size() == 2) {
        return value = con::items_to_ms(0, pieces[0].toInt(), pieces[1].toInt(), 0);
    }
    return value = 0;
}

QWidget* const TimeSetting::create_widget(QString const& string) {
    widget = new QLineEdit(string);
    return widget;
}

TimeSetting::TimeSetting() = default;
