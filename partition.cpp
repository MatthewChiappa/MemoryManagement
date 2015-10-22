#include "partition.h"

// init
Partition::Partition()
{
    jobName = "";
    size = 0;
    holeSize = 0;
    partNum = 0;
    busy = false;
}

// second init
Partition::Partition(double size2, int partNum2)
{
    jobName = "";
    size = size2;
    partNum = partNum2;
    holeSize = 0;
    busy = false;
}

// return the size of the partition
double Partition::getSize(){
    return size;
}

// returns the hole size of the partition
double Partition::getHoleSize(){
    return holeSize;
}

// returns the partition number
int Partition::getPartNum()
{
    return partNum;
}

// adds a job to the partition
void Partition::add(Job job2){
    busy = true;
    holeSize = size - job2.getSize();
    job = job2;
    jobName = job2.getName();
}

// adds a second job to the partition (used for worst fit)
void Partition::addSecondJob(Job job){
    busy = true;
    holeSize = holeSize - job.getSize();
    job2 = job;
    jobName = jobName + "-" + job.getName();
}

// return if the partition is busy
bool Partition::isBusy(){
    return busy;
}

// returns the job name added to partition
std::string Partition::getJobName(){
    return jobName;
}
