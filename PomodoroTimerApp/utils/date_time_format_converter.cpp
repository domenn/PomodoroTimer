//
// Created by Domen on 3. 12. 2018.
//

#include "date_time_format_converter.h"
#include <QTime>

QString con::interval_to_string(qint64 millis, bool const always_add_hours) {
    qint64 seconds = (millis / 1000) % 60;
    qint64 minutes = ((millis / (1000 * 60)) % 60);
    qint64 hours = ((millis / (1000 * 60 * 60)) % 24);
    if (always_add_hours || hours > 0) {
        return QString("%1:%2:%3").arg(hours, 2, 10, QChar('0'))
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'));
    } else {
        return QString("%1:%2").arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'));
    }

}

QString con::interval_to_ms_string(qint64 millis, const QString& ms_sep, bool const always_add_hours) {
    auto repr1 = interval_to_string(millis, always_add_hours);
    qint64 ms = millis % 1000;
    if (ms != 0) {
        repr1 += ms_sep + QString("%1").arg(ms, 3, 10, QChar('0'));
    }
    return repr1;
}
