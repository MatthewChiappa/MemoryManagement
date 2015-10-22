#include "firstfit.h"

// init
FirstFit::FirstFit()
{
}

// second init
FirstFit::FirstFit(std::list<Partition> parts2, std::list<Job> jobs2)
{
   parts = parts2;
   jobs = jobs2;
   begin();
}

// returns list of partitions
std::list<Partition> FirstFit::getParts()
{
    return parts;
}

// returns list of jobs
std::list<Job> FirstFit::getJobs()
{
    return jobs;
}

// starts the first fit algorithm
void FirstFit::begin()
{
    // for every job search every partition
    std::list<Job>::iterator iterator;
    for (iterator = jobs.begin(); iterator != jobs.end(); ++iterator) {
        Job tempJ = *iterator;

        std::list<Partition>::iterator iterator2;
        for (iterator2 = parts.begin(); iterator2 != parts.end(); ++iterator2) {
            Partition tempP = *iterator2;

            // if the partition is not busy, it fits, and the job is not already running,
            // assign the job to the partition
            if(!tempP.isBusy() && tempJ.getSize() <= tempP.getSize() && !tempJ.isRunning()){
                tempP.add(tempJ);
                tempJ.setRunning(tempP.getPartNum());
            }
            *iterator2 = tempP;
        }

        *iterator = tempJ;
    }
}
