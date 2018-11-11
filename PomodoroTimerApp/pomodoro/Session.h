//
// Created by domen on 31/10/18.
//

#ifndef POMODOROTIMER_SESSION_H
#define POMODOROTIMER_SESSION_H

#include <vector>
#include "Run.h"

class Session {

protected:
    Run* current_run{};
    std::vector <Run> run_history;


public:

    Session();

    void interrupt();
    void resumeInterrupt();

    virtual void beginPause();
    void beginLongPause();
    void beginWork();
    void beginWorkInitial();
    virtual QString decide();

    virtual qint64 getTaskTimeMs() const;

    virtual QString reset();

    virtual QString saveState();

    virtual void restore(const QString &state);
};


#endif //POMODOROTIMER_SESSION_H
