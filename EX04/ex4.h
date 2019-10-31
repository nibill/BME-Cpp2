#ifndef EX4_H
#define EX4_H

#include "threadLogFile.h"
#include "threadLogFileSafe.h"

class ex4
{
public:
    void ex4_3();
    void ex4_4();
    void LogToFile(ThreadLogFile &log ,int value);
    void LogToFileSafe(ThreadLogFileSafe &log ,int value);
};

#endif // EX4_H
