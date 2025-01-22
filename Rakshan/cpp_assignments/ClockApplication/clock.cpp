#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <iomanip>
#include <ctime>
#include <unistd.h>
#include <csignal>

std::atomic<bool> alarm_triggered(false);
std::atomic<bool> stop_alarm_thread(false);
std::atomic<bool> timer_triggered(false);
std::atomic<bool> stop_timer_thread(false);

// Alarm thread function
void alarm_thread_function(int hour, int minute) {
    while (!stop_alarm_thread) {
        // Get the current time
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        struct tm *local_time = std::localtime(&now_time);

        if (local_time->tm_hour == hour && local_time->tm_min == minute && !alarm_triggered) {
            alarm_triggered = true;
            std::cout << "\n[ALARM] Alarm Time Reached!\n";
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Timer thread function
void timer_thread_function(int duration) {
    std::this_thread::sleep_for(std::chrono::seconds(duration));
    if (!stop_timer_thread) {
        timer_triggered = true;
        std::cout << "\n[TIMER] Time's up!\n";
    }
}

void set_alarm() {
    int hour, minute;
    std::cout << "Set Alarm Time (HH MM): ";
    std::cin >> hour >> minute;

    alarm_triggered = false;
    stop_alarm_thread = false;
    std::thread(alarm_thread_function, hour, minute).detach();

    std::cout << "Alarm is set for " << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << minute << "\n";
}

void stopwatch() {
    auto start_time = std::chrono::steady_clock::now();
    std::cout << "Stopwatch started. Press Enter to stop...\n";
    std::cin.ignore(); // To ignore previous newline

    std::thread input_thread([]() {
        std::cin.get();
        stop_timer_thread = true;
    });

    while (!stop_timer_thread) {
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
        std::cout << "\r[STOP WATCH]Elapsed time: " << elapsed << " seconds" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    input_thread.join();
    auto end_time = std::chrono::steady_clock::now();
    auto total_elapsed = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
    std::cout << "\nTotal elapsed time: " << total_elapsed << " seconds\n";
    stop_timer_thread = false; // Reset for future use
}

void timer() {
    int duration;
    std::cout << "Set Timer Duration (in seconds): ";
    std::cin >> duration;

    timer_triggered = false;
    stop_timer_thread = false;
    std::thread(timer_thread_function, duration).detach();

    std::cout << "Timer started for " << duration << " seconds.\n";
}

int main() {
    int choice;

    std::cout << "Clock Application\n";
    std::cout << "1. Set Alarm\n";
    std::cout << "2. Stopwatch\n";
    std::cout << "3. Timer\n";
    std::cout << "4. Exit\n";

    do {
        std::cout << "\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                set_alarm();
                break;

            case 2:
                stopwatch();
                break;

            case 3:
                timer();
                break;

            case 4:
                std::cout << "Exiting...\n";
                stop_alarm_thread = true;
                stop_timer_thread = true;
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
