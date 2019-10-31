#ifndef THREADLOGFILESAFE_H
#define THREADLOGFILESAFE_H

#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

class ThreadLogFileSafe
{
public:
    ThreadLogFileSafe(){
        in.open("threadLogSafe.txt", ifstream::in | ifstream::out);
    }
    ~ThreadLogFileSafe(){
        if (in){in.close();}
    }
    void print(thread::id thread_id,int value){

        std::call_once(header,[&](){in<<" HEADER "<<std::endl<<"------------"<<std::endl;});
        std::lock_guard<std::mutex> guard(mutexLogToFile);
        std::cout<<"Log from thread: "<<thread_id<<" with value: "<<value<<std::endl;
        in<<"Log from thread: "<<thread_id<<" with value: "<<value<<std::endl;
    }
private:
    fstream in;
    once_flag header;
    mutex mutexLogToFile;
};

#endif // THREADLOGFILESAFE_H
