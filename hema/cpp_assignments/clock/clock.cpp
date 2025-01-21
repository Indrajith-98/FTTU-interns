#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <ctime>
#include <csignal>

using namespace std;

atomic<bool> alarm_active(false);

void alarm_function(int alarm_hour, int alarm_minute) {
    while (alarm_active) {
        time_t now = time(0);
        tm *local_time = localtime(&now);

        if (local_time->tm_hour == alarm_hour && local_time->tm_min == alarm_minute) {
            cout << "\nTime reached! The alarm is ringing!" << endl;
            break;
        }

        this_thread::sleep_for(chrono::seconds(1)); 
    }
    alarm_active = false;
}

void set_alarm(){
    int hour, minute;
    cout << "Set Alarm (24-hour format):\n";
    cout << "Enter hour: ";
    cin >> hour;
    cout << "Enter minute: ";
    cin >> minute;

    alarm_active = true;
    thread alarm_thread(alarm_function, hour, minute);
    alarm_thread.detach(); 
    cout << "Alarm set for " << hour << ":" << (minute < 10 ? "0" : "") << minute << endl;

}

void start_stopwatch(){
    cout<< "Press enter to start the stopwatch\n";
    cin.ignore();
    cin.get();
    auto start_time = chrono::steady_clock::now();
    cout << "Stopwatch started. Press Enter to stop.\n";
    cin.get(); 

    auto end_time = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time);
    cout << "Stopwatch stopped. Duration: " << duration.count() << " seconds.\n";

}

void start_timer(){
    int seconds;
    cout<<"Enter the number of seconds:\n";
    cin>> seconds;
    cout << "Timer started for " << seconds << " seconds.\n";
    for (int i = seconds; i > 0; --i) {
        cout << "\rTime remaining: " << i << " seconds." << flush;
        this_thread::sleep_for(chrono::seconds(1));
    }

    cout << "\nTime's up!\n";
}

void display_menu(){
    cout << "\nClock Application\n";
    cout << "1. Set Alarm\n";
    cout << "2. Start Stopwatch\n";
    cout << "3. Start Timer\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

int main(){
    int choice;
    while(true){
        display_menu();
        cin >>choice;
        switch (choice)
        {
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
            cout<< "Exit";
            alarm_active = false; // Stop the alarm thread if running
            return 0;
        default:
            cout<<"Invalid input\n";
            break;
        }
    }
    return 0;
}