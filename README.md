# Christmas lights

This project is about how to make christmas lights (or other devices) turning on/off automatically.\
The program automatically calculates dates when the lights should on. Here has been used RTC Timer (DS1307 this case, but it may be any - have to define in the code) to get current time.\
The lights turn on every day between 24.12 and 06.12. After that date thay turn on only in weekends (Saturdays and Sundays) before 02.02 - then are on for the last time, even if this is not weekend.
\
\
Debugging with UATR:
* RTC commands: _time_ - prints current time & date, _start time debug_ - prints time every second, _stop time debug_ - ends printing,
* relay state command: _state_ - prints ON or OFF,
* generated calendar: _schedule_ - prints dates in the schedule.
\
\
![1640961329791](https://user-images.githubusercontent.com/79938517/147828988-128335fd-c6b5-4211-b972-8eed73cbf561.jpg)
