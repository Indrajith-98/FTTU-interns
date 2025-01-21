#include <iostream>
#include "Alarm.cpp"
#include "Stopwatch.cpp"
#include "Timer.cpp"

using namespace std;

int main()
{
    int choice;
    Alarm alarm;
    Stopwatch stopwatch;
    Timer timer;

    while (true)
    {
        cout << "\n|| CLOCK APPLICATION ||\n";

        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm *localTime = std::localtime(&now_time);
        cout << "Current Time: " << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec << endl;

        cout << "1. ALARM\n";
        cout << "2. STOPWATCH\n";
        cout << "3. TIMER\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int hour, minute;
            cout << "\n\nPlease enter the Alarm time (HH MM seperated by blank-space): ";
            cin >> hour >> minute;
            alarm.setAlarm(hour, minute);
            alarm.start();
            break;
        }
        case 2:
            stopwatch.start();
            break;
        case 3:
        {
            int seconds;
            cout << "\nPlease enter the timer duration in seconds: ";
            cin >> seconds;
            timer.setDuration(seconds);
            timer.start();
            break;
        }
        case 0:
            cout << "\n--------------- Thank You ---------------" << endl;
            return 0;
        default:
            cout << "\nInvalid choice. Try again." << endl;
        }
    }
}
