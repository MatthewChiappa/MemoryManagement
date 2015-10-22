#ifndef PARTITION_H
#define PARTITION_H
#include <string.h>
#include <iostream>
#include "job.h"

class Partition
{
public:
    Partition();
    Partition(double size2, int partNum);
    double getSize();
    double getHoleSize();
    int getPartNum();
    void add(Job job2);
    void addSecondJob(Job job2);
    bool isBusy();
    std::string getJobName();
private:
    Job job;
    Job job2;
    double size;
    int partNum;
    bool busy;
    double holeSize;
    std::string jobName;
};

#endif // PARTITION_H
