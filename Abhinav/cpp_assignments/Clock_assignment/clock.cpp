#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <csignal>
#include <atomic>

using namespace std;
atomic<bool> stopwatchRunning(false); // Flag to check if the stopwatch is running
chrono::time_point<chrono::high_resolution_clock> startTime, endTime;

// Alarm function
void alarmThread(int hours, int minutes, int seconds) {
    while (true) {
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);
        tm *localTime = localtime(&currentTime);

        if (localTime->tm_hour == hours && localTime->tm_min == minutes && localTime->tm_sec == seconds) {
            cout << "\n[ALARM] Time's up! The set time has been reached!" << endl;
            break;
        }
        this_thread::sleep_for(1s); // Check every second
    }
}

// Stopwatch function
void stopwatch() {
    cout << "\nStopwatch started. Press Ctrl+C to stop...\n";
    startTime = chrono::high_resolution_clock::now();
    stopwatchRunning = true;

    // Wait until the stopwatch is stopped by a signal
    while (stopwatchRunning) {
        this_thread::sleep_for(100ms); // Polling delay
    }

    endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime);
    cout << "\nStopwatch stopped. Time elapsed: " << duration.count() << " seconds." << endl;
}

// Signal handler for Ctrl+C
void signalHandler(int signal) {
    if (signal == SIGINT && stopwatchRunning) {
        stopwatchRunning = false;
    }
}

// Timer function
void timer(int durationInSeconds) {
    cout << "\nTimer started for " << durationInSeconds << " seconds..." << endl;

    for (int i = durationInSeconds; i > 0; --i) {
        cout << "Time left: " << i << " seconds\r" << flush;
        this_thread::sleep_for(1s);
    }

    cout << "\n[Timer] Time's up!" << endl;
}

int main() {
    // Register signal handler
    signal(SIGINT, signalHandler);

    int choice;
    cout << "Clock Application\n";
    cout << "1. Alarm\n";
    cout << "2. Stopwatch\n";
    cout << "3. Timer\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        int hours, minutes, seconds;
        cout << "\nSet the alarm time (HH MM SS): ";
        cin >> hours >> minutes >> seconds;

        // Start the alarm thread
        thread alarm(alarmThread, hours, minutes, seconds);
        alarm.detach(); // Detach the thread to run in the background

        cout << "Alarm is running in the background. You can use other features.\n";
    } else if (choice == 2) {
        stopwatch();
    } else if (choice == 3) {
        int duration;
        cout << "\nEnter timer duration in seconds: ";
        cin >> duration;
        timer(duration);
    } else {
        cout << "Invalid choice!" << endl;
    }

    // Keep the main thread running to allow detached threads to complete
    cout << "\nPress Enter to exit the application...\n";
    cin.ignore();
    cin.get();

    return 0;
}
