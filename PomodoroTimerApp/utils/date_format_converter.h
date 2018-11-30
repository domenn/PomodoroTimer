//
// Created by domen on 24.11.2018.
//

#pragma once
#include <QtCore>

namespace con{
    inline qint64 as_minutes(qint64 msecs){
        return msecs / 1000 / 60;
    }

    inline qint64 as_seconds(qint64 msecs){
        return msecs / 1000;
    }

    inline QTime as_qtime(qint64 msecs){
        return QTime::fromMSecsSinceStartOfDay(static_cast<int>(msecs));
    }

    inline qint64 min_to_ms(qint64 mins){
        return mins*60*1000;
    }

    inline qint64 h_to_ms(qint64 h){
        return 3600*1000*h;
    }

    inline qint64 s_to_ms(qint64 s){
        return s*1000;
    }

    inline qint64 items_to_ms(qint64 h, qint64 m, qint64 s, qint64 ms){
        return h_to_ms(h) + min_to_ms(m) + s_to_ms(s) + ms;
    }
};


