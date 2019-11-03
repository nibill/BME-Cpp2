#include "ex4.h"
#include <iostream>
#include <vector>

using namespace std;

void ex4::ex4_3()
{
    ThreadLogFile log;
    LogToFile(log,1);
    vector <thread> myThreads;
    myThreads.clear();
    for (unsigned int i=0 ; i < 10*thread::hardware_concurrency();i++)
    {
        myThreads.push_back(thread(LogToFile,std::ref(log),i));
    }
    for (auto &it :myThreads)
    {
        it.join();
    }
}

void ex4::ex4_4()
{
    ThreadLogFileSafe logEx4_4;
    vector <thread> myThreads;
    myThreads.clear();
    for (unsigned int i=0 ; i < 10*thread::hardware_concurrency();i++)
    {
        myThreads.push_back(thread(LogToFileSafe,std::ref(logEx4_4),i));
    }
    for (auto &it :myThreads)
    {
        it.join();
    }
}

void ex4::LogToFile(ThreadLogFile &log, int value)
{
    log.print(std::this_thread::get_id(),value);
}

void ex4::LogToFileSafe(ThreadLogFileSafe &log ,int value)
{
    log.print(std::this_thread::get_id(),value);
}
