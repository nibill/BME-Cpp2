#ifndef THREADLOGFILE_H
#define THREADLOGFILE_H
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

class ThreadLogFile
{
public:
    ThreadLogFile()
    {
        in.open("threadLog.txt", ifstream::in | ifstream::out);
    }

    ~ThreadLogFile()
    {
        if(in)
        {
            in.close();
        }
    }

    void print(thread::id thread_id,int value)
    {
        cout << "Log from thread:" << thread_id << " with value: " << value << endl;
        in<<"Log from thread: "<<thread_id<<" with value: "<<value<<std::endl;
    }

private:
    fstream in;
};

#endif // THREADLOGFILE_H
