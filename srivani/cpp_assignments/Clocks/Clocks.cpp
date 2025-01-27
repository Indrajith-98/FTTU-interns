#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <ctime>
#include <csignal>
#include <vector>
#include <sstream>
#include <iomanip>
#include <memory>

using namespace std;

vector<pair<int, int>> alarm_times;  // Store multiple alarm times
vector<shared_ptr<std::thread>> alarm_threads;  // Store alarm threads
atomic<bool> stopwatch_running(false);
atomic<bool> timer_active(false);

void print_color(const string &str, const string &color) {
    if (color == "red") cout << "\033[31m" << str << "\033[0m";
    else if (color == "green") cout << "\033[32m" << str << "\033[0m";
    else if (color == "yellow") cout << "\033[33m" << str << "\033[0m";
    else if (color == "blue") cout << "\033[34m" << str << "\033[0m";
    else cout << str;
}

void alarm_function(int alarm_hour, int alarm_minute, int alarm_index) {
    while (true) {
        time_t now = time(0);
        tm *local_time = localtime(&now);

        if (local_time->tm_hour == alarm_hour && local_time->tm_min == alarm_minute) {
            print_color("\nAlarm " + to_string(alarm_index) + " is ringing!\n", "red");
            this_thread::sleep_for(chrono::seconds(2)); // Simulate alarm ringing for 2 seconds
            print_color("\nAlarm " + to_string(alarm_index) + " stopped.\n", "green");
            break;  // Stop after alarm rings
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void set_alarm() {
    int hour, minute;
    cout << "Set Alarm (24-hour format):\n";
    cout << "Enter hour: ";
    cin >> hour;
    cout << "Enter minute: ";
    cin >> minute;

    alarm_times.push_back({hour, minute});

    int alarm_index = alarm_times.size();  // Alarm number based on its position
    // Start a new thread for the alarm function
    shared_ptr<std::thread> alarm_thread = make_shared<std::thread>(alarm_function, hour, minute, alarm_index);
    alarm_threads.push_back(alarm_thread);  // Store the thread in the vector

    print_color("Alarm " + to_string(alarm_index) + " set for " + to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute) + "\n", "blue");
}

void start_stopwatch() {
    cout << "Press Enter to start the stopwatch\n";
    cin.ignore();
    cin.get();
    auto start_time = chrono::steady_clock::now();
    stopwatch_running = true;
    cout << "Stopwatch started. Press Enter to stop.\n";

    while (stopwatch_running) {
        chrono::duration<double> elapsed = chrono::steady_clock::now() - start_time;
        // cout << "\rElapsed Time: " << fixed << setprecision(2) << elapsed.count() << " seconds." << flush;
        this_thread::sleep_for(chrono::milliseconds(100));
        if (cin.peek() != EOF) {  // Check if a key is pressed
            cin.get();  // Consume the input (pressing Enter)
            stopwatch_running = false;  // Stop the stopwatch
        }

        this_thread::sleep_for(chrono::milliseconds(100));
    }

    auto end_time = chrono::steady_clock::now();
    chrono::duration<double> duration = end_time - start_time;
    print_color("\nStopwatch stopped. Duration: " + to_string(duration.count()) + " seconds.\n", "green");
}

void start_timer() {
    int seconds;
    cout << "Enter the number of seconds:\n";
    cin >> seconds;
    cout << "Timer started for " << seconds << " seconds.\n" << "Press enter to stop the timer.\n";
    
    timer_active = true;  // Set timer_active to true when the timer starts

    // Create a thread to listen for "Enter" key press
    shared_ptr<std::thread> input_thread = make_shared<std::thread>([]() {
        cin.ignore();  // Ignore any leftover input
        cin.get();  // Wait for the user to press Enter
        timer_active = false;  // Stop the timer
    });
    
    for (int i = seconds; i > 0; --i) {
        if (!timer_active) {  // Check if the timer has been stopped
            cout << "\nTimer stopped.\n";
            break;
        }
        cout << "\rTime remaining: " << i << " seconds." << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }

    if (timer_active) {
        cout << "\nTime's up!\n";
    }

    // Join the input thread before continuing
    if (input_thread->joinable()) {
        input_thread->join();
    }
}



void display_menu() {
    cout << "\nWELCOME TO YOUR CLOCK\n\n";
    cout << "Follow the instructions and you can play with the time :)\n";
    cout << "1. Set Alarm\n";
    cout << "2. Start Stopwatch\n";
    cout << "3. Start Timer\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

bool confirm_exit() {
    char choice;
    print_color("\nAre you sure you want to exit? (y/n): ", "yellow");
    cin >> choice;
    return (choice == 'y' || choice == 'Y');
}

int main() {
    int choice;
    while (true) {
        display_menu();
        cin >> choice;
        switch (choice) {
            case 1:
                set_alarm();
                break;
            case 2:
                start_stopwatch();
                break;
            case 3:
                start_timer();
                break;
            case 4:
                if (confirm_exit()) {
                    print_color("Exiting program...\n", "red");
                    for (auto &alarm_thread : alarm_threads) {
                        if (alarm_thread->joinable()) {
                            alarm_thread->join();  // Ensure all alarm threads finish before exit
                        }
                    }
                    return 0;
                }
                break;
            default:
                print_color("Invalid input, please try again.\n", "red");
                break;
        }
    }
    return 0;
}
