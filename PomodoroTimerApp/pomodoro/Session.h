//
// Created by domen on 31/10/18.
//

#ifndef POMODOROTIMER_SESSION_H
#define POMODOROTIMER_SESSION_H

#include <vector>
#include "Run.h"

class Session {

    Run* current_run{};
    std::vector <Run> run_history;


public:

    Session();

    void interrupt();
    void resumeInterrupt();
    void beginPause();
    void beginLongPause();
    void beginWork();
    void beginWorkInitial();
    void decide();

    qint64 getTaskTimeMs() const;
};


#endif //POMODOROTIMER_SESSION_H
