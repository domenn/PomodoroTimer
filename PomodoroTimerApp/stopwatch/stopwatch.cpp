//
// Created by domen on 05/11/18.
//

//#include <QJsonObject>
//#include <QJsonDocument>
//#include "stopwatch.h"
//
//QString stopwatch::fireAction() {
//    // REFACTOR better return value handling
//    if (state == PomodoroState::PAUSE) {
//        total_pause += (dt::currentTimeMs() - pause_start_time);
//        state = PomodoroState::WORK;
//        return "Pause";
//    } else {
//        beginPause();
//        return "Resume";
//    }
//}
//
//stopwatch::stopwatch() : state(PomodoroState::PAUSE),
//                         total_pause(0),
//                         start_time(dt::currentTimeMs()),
//                         pause_start_time(dt::currentTimeMs()) {}
//
//qint64 stopwatch::getTaskTimeMs() const {
//    if (state == PomodoroState::WORK) {
//        return dt::currentTimeMs() - start_time - total_pause;
//    } else {
//        return pause_display_timestamp;
//    }
//}
//
//QString stopwatch::reset() {
//    state = PomodoroState::PAUSE;
//    start_time = dt::currentTimeMs();
//    total_pause = 0;
//    pause_display_timestamp = 0;
//    pause_start_time = start_time;
//    return "Start";
//}
//
//QString stopwatch::saveState() {
//    if (state == PomodoroState::WORK) {
//        fireAction();
//    }
//    if (getTaskTimeMs() == 0) {
//        return {};
//    }
//    QJsonObject stopwatchState{{"start_time",              start_time},
//                               {"total_pause",             total_pause},
//                               {"pause_display_timestamp", pause_display_timestamp},
//                               {"pause_start_time",        pause_start_time}};
//    return QJsonDocument(stopwatchState).toJson(QJsonDocument::Compact);
//}
//
//void stopwatch::restore(const QString &state) {
//
//    this->state = PomodoroState::PAUSE;
//    fireAction();
//    fireAction();
//
//    QJsonDocument doc = QJsonDocument::fromJson(state.toUtf8());
//    const QJsonObject &obj = doc.object();
//    start_time = obj["start_time"].toString().toLongLong();
//    total_pause = obj["total_pause"].toString().toLongLong();
//    pause_display_timestamp = obj["pause_display_timestamp"].toString().toLongLong();
//    pause_start_time = obj["pause_start_time"].toString().toLongLong();
//}
//
//void stopwatch::beginPause() {
//    pause_display_timestamp = getTaskTimeMs();
//    pause_start_time = dt::currentTimeMs();
//    state = PomodoroState::PAUSE;
//}
