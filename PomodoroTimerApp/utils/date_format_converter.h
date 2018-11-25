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
};


