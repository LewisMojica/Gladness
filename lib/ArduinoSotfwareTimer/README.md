# ArduinoSotfwareTimer


| Function name  | Description |
| ------------- | ------------- |
| `Timer(unsigned long interval)` | _Constructor_. **interval** represents the time that has to pass form the timer was started to be activated |
| `void init()` | The Timer starts counting|
|`void initOn()`| The Timer starts counting, but it starts like the interval has already passed|
|`void end()`| The Timer stop counting|
|`boolean isRunning()` | return `true` if the Timer is counting, if not, return `false`|
|`void reset()`| the Timer start counting from 0|
|`boolean read()`| if the interval has passed return `true` and start counting from 0, else return `false`|
|`bool check()` | if the interval has passed return `true` and **do not start counting from 0**, else return `false`|


https://github.com/LewisMojica/ArduinoSotfwareTimer
