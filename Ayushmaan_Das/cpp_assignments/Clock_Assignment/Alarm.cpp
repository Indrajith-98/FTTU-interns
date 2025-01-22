#include <iostream>
#include <thread>
#include <chrono>

class Alarm
{
private:
    int alarmHour, alarmMinute;
    bool running;

    void alarmHandler()
    {
        while (running)
        {
            auto now = std::chrono::system_clock::now();
            std::time_t now_time = std::chrono::system_clock::to_time_t(now);
            std::tm *localTime = std::localtime(&now_time);

            if (localTime->tm_hour == alarmHour && localTime->tm_min == alarmMinute)
            {
                std::cout << "\n<< Alarm is ringing! >>\nTime: " << alarmHour << ":" << alarmMinute << std::endl;
                break;
            }

            std::this_thread::sleep_for(std::chrono::seconds(30));
        }
    }

public:
    Alarm() : running(false) {}

    void setAlarm(int hour, int minute)
    {
        alarmHour = hour;
        alarmMinute = minute;
        std::cout << "Alarm set for " << alarmHour << ":" << alarmMinute << std::endl;
    }

    void start()
    {
        running = true;
        std::thread alarmThread(&Alarm::alarmHandler, this);
        alarmThread.detach();
    }

    void stop()
    {
        running = false;
    }
};