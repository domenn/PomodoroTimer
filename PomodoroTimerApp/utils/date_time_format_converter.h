//
// Created by domen on 24.11.2018.
//

#pragma once

#include <QtCore>

namespace con {
    inline qint64 as_minutes(qint64 msecs) {
        return msecs / 1000 / 60;
    }

    inline qint64 as_seconds(qint64 msecs) {
        return msecs / 1000;
    }

    inline QTime as_qtime(qint64 msecs) {
        return QTime::fromMSecsSinceStartOfDay(static_cast<int>(msecs));
    }

    inline qint64 min_to_ms(qint64 mins) {
        return mins * 60 * 1000;
    }

    inline qint64 h_to_ms(qint64 h) {
        return 3600 * 1000 * h;
    }

    inline qint64 s_to_ms(qint64 s) {
        return s * 1000;
    }

    inline qint64 items_to_ms(qint64 h, qint64 m, qint64 s, qint64 ms) {
        return h_to_ms(h) + min_to_ms(m) + s_to_ms(s) + ms;
    }

    /**
     * Returns interval in format mm:ss or hh:mm:ss if hours are more than 0.
     * @param millis input milliseconds to convert into this format.
     * @param always_add_hours Always return hours, even if they are 0.
     * @return String representation of timestamp (passed in millis).
     */
    QString interval_to_string(qint64 millis, bool always_add_hours = false);

    /**
     * Like other overload interval_to_string, but also includes millisecond part if it is not 0.
     * @param ms_sep Separator between s and ms, by default :
     * @return String representation of timestamp (passed in millis).
     */
    QString interval_to_ms_string(qint64 millis, const QString& ms_sep = ".", bool always_add_hours = false);

//    template <typename return_type>
//    str_type ms_since_epoch_to_datetime_str(qint64 millis, QString );
};


