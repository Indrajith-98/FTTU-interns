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
#include <map>

using namespace std;

vector<pair<int, int>> alarm_times;
vector<string> alarm_names;
vector<shared_ptr<std::thread>> alarm_threads;
vector<pair<int, int>> saved_alarms;
atomic<bool> stopwatch_running(false);
atomic<bool> timer_active(false);

void print_color(const string &str, const string &color) {
    if (color == "red") cout << "\033[31m" << str << "\033[0m";
    else if (color == "green") cout << "\033[32m" << str << "\033[0m";
    else if (color == "yellow") cout << "\033[33m" << str << "\033[0m";
    else if (color == "blue") cout << "\033[34m" << str << "\033[0m";
    else cout << str;
}

void alarm_function(int alarm_hour, int alarm_minute, const string &alarm_name, int alarm_index) {
    bool alarm_ringing = false;

    while (!alarm_ringing) {
        time_t now = time(0);
        tm *local_time = localtime(&now);

        if (local_time->tm_hour == alarm_hour && local_time->tm_min == alarm_minute) {
            string name_display = alarm_name.empty() ? "" : " (" + alarm_name + ")";
            print_color("\nAlarm " + to_string(alarm_index) + name_display + " is ringing!\n", "red");
            alarm_ringing = true;
            this_thread::sleep_for(chrono::seconds(2));  // Delay to simulate alarm ringing time
            print_color("Alarm " + to_string(alarm_index) + name_display + " stopped.\n", "green");
            break;
        }

        this_thread::sleep_for(chrono::seconds(1));
    }
}

void set_alarm() {
    int hour, minute;
    string alarm_name;
    char use_saved;
    cout << "Do you want to use a saved alarm? (y/n): ";
    cin >> use_saved;

    if (use_saved == 'y' || use_saved == 'Y') {
        if (saved_alarms.empty()) {
            print_color("No saved alarms available.\n", "yellow");
            return;
        } else {
            cout << "Available saved alarms:\n";
            for (size_t i = 0; i < saved_alarms.size(); ++i) {
                cout << i + 1 << ". " << setw(2) << setfill('0') << saved_alarms[i].first << ":"
                     << setw(2) << setfill('0') << saved_alarms[i].second;
                if (i < alarm_names.size()) {
                    cout << " (" << alarm_names[i] << ")";
                }
                cout << "\n";
            }
            int choice;
            cout << "Enter the number of the alarm you want to use: ";
            cin >> choice;

            if (choice >= 1 && choice <= (int)saved_alarms.size()) {
                hour = saved_alarms[choice - 1].first;
                minute = saved_alarms[choice - 1].second;
                alarm_name = alarm_names[choice - 1];  // Set the alarm name from saved alarms
            } else {
                print_color("Invalid choice.\n", "red");
                return;
            }
        }
    } else {
        cout << "Set Alarm (24-hour format):\n";
        cout << "Enter hour: ";
        cin >> hour;
        cout << "Enter minute: ";
        cin >> minute;

        char save_choice;
        cout << "Do you want to save this alarm for future use? (y/n): ";
        cin >> save_choice;

        if (save_choice == 'y' || save_choice == 'Y') {
            saved_alarms.push_back({hour, minute});
            alarm_names.push_back(alarm_name);  // Save the alarm name
            print_color("Alarm saved successfully.\n", "green");
        }
    }

    char set_name;
    cout << "Do you want to set a name for this alarm? (y/n): ";
    cin >> set_name;

    if (set_name == 'y' || set_name == 'Y') {
        cout << "Enter alarm name: ";
        cin.ignore();
        getline(cin, alarm_name);
    }

    alarm_times.push_back({hour, minute});
    alarm_names.push_back(alarm_name);

    int alarm_index = alarm_times.size();
    shared_ptr<std::thread> alarm_thread = make_shared<std::thread>(alarm_function, hour, minute, alarm_name, alarm_index);
    alarm_threads.push_back(alarm_thread);

    string name_display = alarm_name.empty() ? "" : " (" + alarm_name + ")";
    print_color("Alarm " + to_string(alarm_index) + name_display + " set for " +
                to_string(hour) + ":" + (minute < 10 ? "0" : "") + to_string(minute) + "\n", "blue");
}


void start_stopwatch() {
    cout << "Press Enter to start the stopwatch\n";
    cin.ignore();
    cin.get();
    auto start_time = chrono::steady_clock::now();
    stopwatch_running = true;
    cout << "Stopwatch started. Press Enter to stop.\n";

    while (stopwatch_running) {
        this_thread::sleep_for(chrono::milliseconds(100));
        if (cin.peek() != EOF) {
            cin.get();
            stopwatch_running = false;
        }
    }

    auto end_time = chrono::steady_clock::now();
    chrono::duration<double> duration = end_time - start_time;
    print_color("\nStopwatch stopped. Duration: " + to_string(duration.count()) + " seconds.\n", "green");
}

void start_timer() {
    int seconds;
    cout << "Enter the number of seconds:\n";
    cin >> seconds;
    cout << "Timer started for " << seconds << " seconds.\nPress enter to stop the timer.\n";

    timer_active = true;

    shared_ptr<std::thread> input_thread = make_shared<std::thread>([]() {
        cin.ignore();
        cin.get();
        timer_active = false;
    });

    for (int i = seconds; i > 0; --i) {
        if (!timer_active) {
            cout << "\nTimer stopped.\n";
            break;
        }
        cout << "\rTime remaining: " << i << " seconds." << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }

    if (timer_active) {
        cout << "\nTime's up!\n";
    }

    if (input_thread->joinable()) {
        input_thread->join();
    }

    // Return control to the main menu after the timer finishes
    print_color("\nReturning to main menu...\n", "green");
}

void display_menu() {
    cout << "\nWELCOME TO YOUR CLOCK\n";
    cout << "Choose the one that you wanted to use:\n";
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
                            alarm_thread->join();
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
