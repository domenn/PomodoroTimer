
Session contains times for all individual items. Those are:
* Work
* Legal pause
* Illegal pause / interruptions

Time is stored for start of session. Whenever it changes, milliseconds get stored and added to totals for that category.
There is also Run, which means pomodoro .. That will contain info for individual run. Should store time-point for all ...
start, end, pause, interruption.


How do we handle pauses and interrupts?
If Pomodoro allowed pause time (the value that is default 5/15 minutes) runs out, instead of pause time this is counted as pause buffer.
Pause buffer can go below or above zero.

Other features
* Count interrupted pomodori
* Count overtime pauses (more than 1 minute is supposed to be overtime)