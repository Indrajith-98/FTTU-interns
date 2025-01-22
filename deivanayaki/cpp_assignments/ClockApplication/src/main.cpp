#include <iostream>
#include <iomanip>
#include <ctime>
#include <thread>
#include <chrono>
#include <vector>

void print_time(const std::tm* time_info) {
    char buffer[100];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", time_info);
    std::cout << buffer;
}

void alarm_worker(std::time_t alarm_time) {
    std::time_t current_time;
    do {
        current_time = std::time(nullptr);
        std::this_thread::sleep_for(std::chrono::seconds(1));  
    } while (current_time < alarm_time);

    std::cout << "**************************\n";
    std::cout << "\nALARM! TIME'S UP! IT'S ";
    print_time(std::localtime(&alarm_time));
    std::cout << std::endl;
    std::cout << "**************************\n";
}

void set_alarm(int hours, int minutes) {
    std::time_t current_time = std::time(nullptr);
    std::tm* alarm_tm = std::localtime(&current_time);
    alarm_tm->tm_hour = hours;
    alarm_tm->tm_min = minutes;
    alarm_tm->tm_sec = 0;

    std::time_t alarm_time = std::mktime(alarm_tm);
    if (alarm_time <= current_time) {
        alarm_time += 24 * 60 * 60;
    }

    std::cout << "\nALARM SET FOR : ";
    print_time(std::localtime(&alarm_time));
    std::cout << std::endl;

    std::thread(alarm_worker, alarm_time).detach();
}

void display_time(int hours, int minutes, int seconds) {
    std::cout << "\rTime Remaining: ";
    std::cout << std::setfill('0') << std::setw(2) << hours << ":"
              << std::setw(2) << minutes << ":"
              << std::setw(2) << seconds << std::flush;
}

void timer_worker(int hours, int minutes, int seconds) {
    while (hours > 0 || minutes > 0 || seconds > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if (seconds == 0) {
            if (minutes == 0) {
                if (hours > 0) {
                    hours--;
                    minutes = 59;
                    seconds = 59;
                }
            } else {
                minutes--;
                seconds = 59;
            }
        } else {
            seconds--;
        }
    }

    std::cout << "**************************\n";
    std::cout << "\nTIMER DONE! Time's up!" << std::endl;
    std::cout << "**************************\n";
    
}

void set_timer(int hours, int minutes, int seconds) {
    std::cout << "\nTIMER SET FOR : ";
    display_time(hours, minutes, seconds);
    std::cout << std::endl;
    std::thread(timer_worker, hours, minutes, seconds).detach();
}

void stopwatch_worker(bool& running) {
    int hours = 0, minutes = 0, seconds = 0;

    while (true) {
        if (running) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            seconds++;

            if (seconds == 60) {
                seconds = 0;
                minutes++;
            }

            if (minutes == 60) {
                minutes = 0;
                hours++;
            }

            std::cout << "\rStopwatch: ";
            std::cout << std::setfill('0') << std::setw(2) << hours << ":"
                      << std::setw(2) << minutes << ":"
                      << std::setw(2) << seconds << std::flush;
        }
    }
}

int main() {
    int hours, minutes, choice, seconds;
    bool stopwatch_running = false;

    while (true) {
        std::cout << "\n---------------------------------------\n";
        std::cout << "...........CLOCK APPLICATION...........\n";
        std::cout << "---------------------------------------\n";
        std::cout << "1. ALARM\n2. STOPWATCH\n3. TIMER\n4. EXIT\n";
        std::cout << "---------------------------------------\n";
        std::cout << "YOUR CHOICE : ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "ENTER HOUR FOR ALARM (24HR FORMAT) : ";
                std::cin >> hours;
                std::cout << "ENTER MINUTE FOR ALARM : ";
                std::cin >> minutes;

                if (hours < 0 || hours >= 24 || minutes < 0 || minutes >= 60) {
                    std::cout << "INVALID TIME ENTERED!! PLEASE TRY AGAIN!!\n";
                }
                set_alarm(hours, minutes);
                break;

            case 2:
                if (!stopwatch_running) {
                    std::cout << "Starting Stopwatch...\n";
                    stopwatch_running = true;
                    std::thread(stopwatch_worker, std::ref(stopwatch_running)).detach();
                } else {
                    std::cout << "Stopwatch is already running. Stopping stopwatch...\n";
                    stopwatch_running = false;
                }
                break;

            case 3:
                std::cout << "ENTER HOURS FOR TIMER : ";
                std::cin >> hours;
                std::cout << "ENTER MINUTES FOR TIMER : ";
                std::cin >> minutes;
                std::cout << "ENTER SECONDS FOR TIMER : ";
                std::cin >> seconds;

                if (hours < 0 || minutes < 0 || seconds < 0 || minutes >= 60 || seconds >= 60) {
                    std::cout << "INVALID TIME ENTERED!! PLEASE TRY AGAIN!!\n";
                } else {
                    set_timer(hours, minutes, seconds);
                }
                break;

            case 4:
                std::cout << "CLOSING CLOCK APP...\n";
                return 0;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
    }
    return 0;
}
