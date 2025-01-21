#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

class Stopwatch
{
private:
    chrono::time_point<chrono::system_clock> startTime;
    bool running;

public:
    Stopwatch() : running(false) {}

    void start()
    {
        running = true;
        startTime = chrono::system_clock::now();
        cout << "\n<< Stopwatch has been started >>\nPress 'q' to stop......." << endl;

        char input;
        while (running)
        {
            cin >> input;
            if (input == 'q' || input == 'Q')
            {
                stop();
            }
        }
    }

    void stop()
    {
        if (running)
        {
            auto endTime = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = endTime - startTime;
            running = false;
            cout << "<< Stopwatch stopped >>\nElapsed time: " << elapsed_seconds.count() << " secs." << endl;
        }
    }
};