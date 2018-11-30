//
// Created by domen on 31/10/18.
//

#include "millisecondsToTimer.h"
#include <QTime>

QString millisecondsToTimer::interval_to_string(qint64 millis) {
    qint64 seconds = (millis / 1000) % 60;
    qint64 minutes = ((millis / (1000 * 60)) % 60);
    qint64 hours = ((millis / (1000 * 60 * 60)) % 24);
    if (hours > 0) {
        return QString("%1:%2:%3").arg(hours, 2, 10, QChar('0'))
                .arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'));
    } else {
        return QString("%1:%2").arg(minutes, 2, 10, QChar('0'))
                .arg(seconds, 2, 10, QChar('0'));
    }

}

QString millisecondsToTimer::interval_to_ms_string(qint64 millis) {
    auto repr1 = interval_to_string(millis);
    qint64 ms = millis % 1000;
    if( ms != 0) {
        repr1 += ":" + QString("%1").arg(ms, 3, 10, QChar('0'));
    }
    return repr1;
}
