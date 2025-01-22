#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
using namespace std;

void alarm(int hours, int minutes) {
    time_t now;
    struct tm *currentTime;
    while (true) {
        now = time(nullptr);
        currentTime = localtime(&now);

        cout << "Current time: " << currentTime->tm_hour << ":" << currentTime->tm_min << endl;

        if (currentTime->tm_hour == hours && currentTime->tm_min == minutes) {
            cout << "ALARM! Time: " << hours << ":" << minutes << endl;
            break; 
        }

        this_thread::sleep_for(chrono::seconds(1));
    }
}
void stopwatch(){
    chrono::high_resolution_clock::time_point start_time, end_time;
    char a;
    cout<<"Please enter s to start the stop watch"<<endl;
    cin>>a;
    start_time = std::chrono::high_resolution_clock::now();
    char b;
    while (true){
        cout<<endl<<"If you want to see the timer the press w"<<endl<<"If you want to stop the watch the press p"<<endl;
        cin>>b;
        if (b=='w'){
            end_time = std::chrono::high_resolution_clock::now();
            int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
            cout<<(int)(elapsed_seconds/3600)<<":"<<(int)((elapsed_seconds%3600)/60)<<":"<<(elapsed_seconds%3600)%60<<endl;
            cout.flush();
        }
        else if(b=='p'){
            end_time = std::chrono::high_resolution_clock::now();
            int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();
            cout<<(int)(elapsed_seconds/3600)<<":"<<(int)((elapsed_seconds%3600)/60)<<":"<<(elapsed_seconds%3600)%60<<endl;
            cout.flush();
            break;
        }
    }
    cout<<"Hence the program finished";
}

void timer(){
    int hour, minute, second;
    cout << "Please give the hours, minutes, and seconds one by one for which the timer should run:" << endl;
    cin >> hour >> minute >> second;

    char a;
    cout << endl << "The timer was set. Press 's' to start:" << endl;
    cin >> a;

    int total_seconds = (hour * 3600) + (minute * 60) + second;
    int elapsed_seconds = 0;

    while (elapsed_seconds <= total_seconds) {
        int remaining_seconds = total_seconds - elapsed_seconds;
        int hours = remaining_seconds / 3600;
        int minutes = (remaining_seconds % 3600) / 60;
        int seconds = (remaining_seconds % 3600) % 60;

        cout << hours << ":" << minutes << ":" << seconds << "\r";
        cout.flush();

        if (remaining_seconds == 0) {
            cout << endl << "The timer had reached the time!" << endl;
            break;
        }

        this_thread::sleep_for(chrono::seconds(1));
        elapsed_seconds++;
    }

}

int main() {
    char mode;
    cout << "Enter 's' to set the alarm or 'c' to continue with other tasks: ";
    cin >> mode;

    if (mode == 's') {
        int hours, minutes;
        cout << "Enter the alarm time (hours minutes): ";
        cin >> hours >> minutes;

        thread alarmThread(alarm, hours, minutes);

        cout << "Main thread continues with other tasks..." << endl;

        for (int i = 0; i < 5; ++i) {
            cout << "Main task #" << i + 1 << endl;
            this_thread::sleep_for(chrono::seconds(1));  
        }

        //alarmThread.join();
        while (true){
            cout<<"Enter the choice"<<endl<<"1.Timer"<<endl<<"2.Stopwatch"<<endl<<"3.exit"<<endl;
            int n;
            cin>>n;
            if (n>=3){
                break;
            }
            else{
                switch(n){
                    case 1:
                        timer();
                        break;
                    case 2:
                        stopwatch();
                        break;

                }
            }
        }
    
    alarmThread.join();
    }
    else{
        while (true){
            cout<<"Enter the choice"<<endl<<"1.Timer"<<endl<<"2.Stopwatch"<<endl<<"3.exit"<<endl;
            int n;
            cin>>n;
            if (n>=3){
                break;
            }
            else{
                switch(n){
                    case 1:
                        timer();
                        break;
                    case 2:
                        stopwatch();
                        break;

                }
            }
        }
    } 
        
    return 0;
}