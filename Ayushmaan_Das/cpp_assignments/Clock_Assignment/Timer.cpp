#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

class Timer
{
private:
    int duration;

public:
    Timer() : duration(0) {}

    void setDuration(int seconds)
    {
        duration = seconds;
        cout << "Timer set for " << duration << " seconds." << endl;
    }

    void start()
    {
        cout << "<< Timer started for " << duration << " seconds. >>" << endl;

        for (int i = duration; i > 0; --i)
        {
            cout << "Time remaining: " << i << " seconds." << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }

        cout << "<< Time's up! >>" << endl;
    }
};
