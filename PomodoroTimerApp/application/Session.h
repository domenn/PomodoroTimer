//
// Created by domen on 31/10/18.
//

#pragma once

#include <QtCore>

#include <vector>
#include <PomodoroTimerApp/pomodoro/PomodoroState.h>
#include "ApplicationMode.h"

class Session {
protected:
    qint64 current_phase_start_timestamp_;
    qint64 work_start_timestamp_;

public:
    /**
     * Resets values to zero and starts the timer. Shall be used when starting the timer for the first time.
    */
    virtual void initialize() = 0;

    /**
    * Returns the main timer in ms. For Pomodoro timer this is the current timer.
    */
    virtual qint64 getMainTimerValue() = 0;

    /*void interrupt();
    void resumeInterrupt();

    virtual void beginPause();
    void beginLongPause();
    void beginWork();
    void beginWorkInitial();
    virtual QString fireAction();

    virtual qint64 getTaskTimeMs() const;

    virtual QString reset();*/


    /**
     * Returns JSON string that can be used to save state before exit.
     */
    virtual QString saveState() = 0;

    /**
     * Restores the session after reopening the app.
     * @param state the state in JSON format
    */
    virtual void restore(const QString& state) = 0;

    /**
     * Returns raw pointer to heap .. Can cause memory leak, but is only used once.
     * @param mode What mode do we use our app in
     * @return Pointer to session on heap. Can be freed with delete.
     */
    template <typename settings_type>
    static Session* const create(const ApplicationMode& mode, settings_type const * settings_structure);

    static Session* const create(const ApplicationMode& mode);

    /**
     * The function is basically play/pause handler. Decides what to do: play, pause, and if pause, decides which thing to pause. Returns string for a button.
     * @return String that represents state, should be written to button.
     */
    virtual void fireAction() = 0;

    virtual qint64 get_total_elapsed_time_of_kind(PomodoroState kind) const = 0;

    /**
     * Adds together time of long pause and normal pause and returns the value.
     * @return Total pause, including long and normal
     */
    virtual qint64 get_total_pause() const = 0;

    /**
     * @return Total elapsed time in this session, all parts added together
     */
    virtual qint64 get_total_time() const = 0;

    virtual PomodoroState get_current_state() const = 0;
};
