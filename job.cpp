#include "job.h"

// init
Job::Job()
{
    name = "";
    size = 0;
    running = false;
}

// second init
Job::Job(std::string name2, double size2)
{
    name = name2;
    size = size2;
    running = false;
}

// returns the name of the job
std::string Job::getName()
{
    return name;
}

// returns the size of the job
double Job::getSize()
{
    return size;
}

// return if the job is running
bool Job::isRunning()
{
    return running;
}

// returns the partition number the job is assgined
int Job::getPartNum()
{
    return partNum;
}

// starts job to partition
void Job::setRunning(int num)
{
    running = true;
    partNum = num;
}
