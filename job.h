#ifndef JOB_H
#define JOB_H
#include <string.h>
#include <iostream>

class Job
{
public:
    Job();
    Job(std::string name2, double size2);
    std::string getName();
    double getSize();
    bool isRunning();
    int getPartNum();
    void setRunning(int num);
private:
    std::string name;
    double size;
    bool running;
    int partNum;
};

#endif // JOBS_H
