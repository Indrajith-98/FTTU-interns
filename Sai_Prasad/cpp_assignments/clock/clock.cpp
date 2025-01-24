#include<iostream>
#include<unistd.h>
#include<ctime>

using namespace std;


void setAlarm();
void setStopwatch();
void setTimer();

int main(){
    int choice;

    while(true){
        cout<< "----Welcome to clock application----\n";
        cout<< "Choices for each mode:\n";

        cout << "1. Alarm \n";
        cout << "2. Stopwatch \n";
        cout << "3. Timer \n";
        cout << "4. Exit \n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            setAlarm();
            break;
        
        case 2:
            setStopwatch();
            break;
        
        case 3:
            setTimer();
            break;

        case 4:
            cout << "Exiting now. Thank You \n";
            exit(0);
        
        default:
            cout << "Invalid choice. Select a valid choice. \n";
            break;
        }
    }

    return 0;
}

void setAlarm(){

    int hour, minute;

    time_t now;

    tm *current_time;

    cout << "Enter time to set alarm in HH MM : ";
    cin >> hour >> minute;

    pid_t pid = fork();

    if(pid == 0){

        timespec sleepDuration;

        sleepDuration.tv_sec=1;
        sleepDuration.tv_nsec=0;
        

        while(true){

            time(&now);
            current_time =  localtime(&now);

            if(current_time->tm_hour == hour && current_time->tm_min == minute){
                cout << "Alarm is on : Time's up. It is" << hour << ":" << minute << "now! \n";
                exit(0);
            }

            nanosleep(&sleepDuration,NULL);

        }
    }
    else{
        cout << "Alarm is set at " << hour << ":" << minute << "\n";
    }

}

void setStopwatch(){

    char start_stop;


    time_t startTime, stopTime;

    cout << "Press S to start the stopwatch \n";
    cin >> start_stop;

    if(start_stop == 'S'){

        time(&startTime);

        cout << "Press E to stop the stopwatch \n";
        cin >> start_stop;

        if(start_stop == 'E'){

            time(&stopTime);

            int totalSeconds=difftime(stopTime, startTime);

            int hours = totalSeconds / 3600;
            int minutes = (totalSeconds % 3600) / 60;
            int seconds = totalSeconds % 60;

            cout << "Stopwatch is stopped. Total elapsed time (h m s) is " << hours <<"h " << minutes << "m " << seconds<< "s \n";
        }
        else{
            cout << "Invalid enter. Stopwatch is stopped because of inproper choice.\n";
        }
    }
    else{
        cout << "Invalid enter. Stopwatch is not started try again.\n";
    }
}

void setTimer(){

    timespec sleepDuration;

    sleepDuration.tv_sec=1;
    sleepDuration.tv_nsec=0;

    int timerHours, timerMinutes, TimerSeconds;

    cout << "Enter the duration of timer in (HH MM SS) : ";
    cin >> timerHours >> timerMinutes >> TimerSeconds;

    int totalDuration = (timerHours * 3600) + (timerMinutes * 60) + TimerSeconds;

    while(totalDuration>0){

        nanosleep(&sleepDuration,NULL);
        totalDuration--;

    }

    cout << "Your timer's up! \n";
}