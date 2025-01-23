#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>
#include <atomic>
#include <cstdlib>

using namespace std;

class Clock
{
private:
    int hours, minutes, seconds;
    atomic<bool> alarmRunning;

    // Timer function
    void timer_fun()
    {
        while (seconds > 0 || minutes > 0 || hours > 0)
        {
            cout << "\rTime remaining: "
                 << (hours < 10 ? "0" : "") << hours << ":"
                 << (minutes < 10 ? "0" : "") << minutes << ":"
                 << (seconds < 10 ? "0" : "") << seconds << flush;

            this_thread::sleep_for(chrono::seconds(1));

            if (seconds > 0)
            {
                seconds--;
            }
            else if (minutes > 0)
            {
                minutes--;
                seconds = 59;
            }
            else if (hours > 0)
            {
                hours--;
                minutes = 59;
                seconds = 59;
            }
        }
        system("mpg123 -q /mnt/c/Users/prasa/OneDrive/Desktop/c++_project/learningc-/Alarm_clock/alarm.wav.mp3 &");
        this_thread::sleep_for(chrono::seconds(10));
        cout << "\nTimer completed!" << endl;
    }

    // Stopwatch function
    void stopwatch()
    {
        int hours = 0, minutes = 0, seconds = 0;
        while (true)
        {

            cout << "\rStopwatch: "
                 << (hours < 10 ? "0" : "") << hours << ":"
                 << (minutes < 10 ? "0" : "") << minutes << ":"
                 << (seconds < 10 ? "0" : "") << seconds << flush;

            this_thread::sleep_for(chrono::seconds(1));
            seconds++;

            if (seconds >= 60)
            {
                seconds = 0;
                minutes++;
            }
            if (minutes >= 60)
            {
                minutes = 0;
                hours++;
            }
        }
    }

    // Alarm function
    void alarm()
    {
        cout << "Alarm set for: "
             << (hours < 10 ? "0" : "") << hours << ":"
             << (minutes < 10 ? "0" : "") << minutes << ":"
             << (seconds < 10 ? "0" : "") << seconds << endl;

        while (alarmRunning)
        {
            auto now = chrono::system_clock::now();
            time_t currentTime = chrono::system_clock::to_time_t(now);
            tm *ltm = localtime(&currentTime);

            // Adjust for time zone (example: India Standard Time)
            ltm->tm_hour += 5;
            ltm->tm_min += 30;

            if (ltm->tm_min >= 60)
            {
                ltm->tm_min -= 60;
                ltm->tm_hour += 1;
            }
            if (ltm->tm_hour >= 24)
            {
                ltm->tm_hour -= 24;
            }

            cout << "\rCurrent time: "
                 << (ltm->tm_hour < 10 ? "0" : "") << ltm->tm_hour << ":"
                 << (ltm->tm_min < 10 ? "0" : "") << ltm->tm_min << ":"
                 << (ltm->tm_sec < 10 ? "0" : "") << ltm->tm_sec << flush;

            if (ltm->tm_hour == hours && ltm->tm_min == minutes && ltm->tm_sec == seconds)
            {
                cout << "\nALARM! Time's up!" << endl;

                // Play the alarm sound using a Linux utility
                system("mpg123 -q /mnt/c/Users/prasa/OneDrive/Desktop/c++_project/learningc-/Alarm_clock/alarm.wav.mp3 &");

                this_thread::sleep_for(chrono::seconds(10)); // Let the alarm sound play for 10 seconds
                alarmRunning = false;                        // Stop the alarm thread
                break;
            }

            this_thread::sleep_for(chrono::seconds(1));
        }
    }

public:
    Clock() : alarmRunning(false) {}

    void displayMenu()
    {
        cout << "Enter the below status:" << endl;
        cout << "1. Alarm" << endl;
        cout << "2. Timer" << endl;
        cout << "3. Stopwatch" << endl;
        cout << "4. Exit" << endl;
    }

    void executeChoice(int choice)
    {
        if (choice == 1)
        {
            cout << "Enter the Alarm time (HH MM SS): ";
            cin >> hours >> minutes >> seconds;
            alarmRunning = true;
            thread alarmThread(&Clock::alarm, this);
            alarmThread.detach(); // Detach the thread to run in the background
            cout << "Press Enter to stop the alarm.\n";
            cin.ignore(); // Clear the input buffer
            cin.get();    // Wait for user input to stop the alarm
            stopAlarm();
        }
        else if (choice == 2)
        {
            cout << "Enter the Timer time (HH MM SS): ";
            cin >> hours >> minutes >> seconds;
            timer_fun();
        }
        else if (choice == 3)
        {
            cout << "Stopwatch started. Press Ctrl+C to stop." << endl;
            stopwatch();
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }

    void stopAlarm()
    {
        alarmRunning = false; // Stop the alarm
        cout << "\nAlarm stopped." << endl;

        // Stop any ongoing sound (if necessary)
        system("pkill mpg123");
    }
};

int main()
{
    Clock clockApplication;
    while (true)
    {
        clockApplication.displayMenu();

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 4)
        {
            cout << "Exiting the application." << endl;
            break;
        }

        clockApplication.executeChoice(choice);
    }
    return 0;
}
