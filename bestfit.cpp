#include "bestfit.h"
#include <limits>

// init
BestFit::BestFit()
{
}

// second init
BestFit::BestFit(std::list<Partition> parts2, std::list<Job> jobs2)
{
   parts = parts2;
   jobs = jobs2;
   begin();
}

// returns list of partitions
std::list<Partition> BestFit::getParts()
{
    return parts;
}

// returns list of jobs
std::list<Job> BestFit::getJobs()
{
    return jobs;
}

// starts the best fit algorithm
void BestFit::begin()
{
    // variable to track smallest hole
    double minMemWaste = std::numeric_limits<double>::max();

    // for every job go through the partitons
    std::list<Job>::iterator iterator;
    for (iterator = jobs.begin(); iterator != jobs.end(); ++iterator) {
        Job tempJ = *iterator;

        std::list<Partition>::iterator iterator2;
        for (iterator2 = parts.begin(); iterator2 != parts.end(); ++iterator2) {
            Partition tempP = *iterator2;

            // if the partition is not busy, it fits, and the job is not already running
            if(!tempP.isBusy() && tempJ.getSize() <= tempP.getSize() && !tempJ.isRunning()){
                // if this is the smallest hole, set smallest hole double to value
                if(minMemWaste > (tempP.getSize() - tempJ.getSize())) {
                    minMemWaste = tempP.getSize() - tempJ.getSize();
                }
            }
            *iterator2 = tempP;
        }

        // run through partitions again to identify which partition had the smallest hold
        // then assign job to partition
        std::list<Partition>::iterator iterator3;
        for (iterator3 = parts.begin(); iterator3 != parts.end(); ++iterator3) {
            Partition tempP2 = *iterator3;

            if(!tempP2.isBusy() && tempJ.getSize() <= tempP2.getSize() && !tempJ.isRunning()){
                if(minMemWaste == (tempP2.getSize() - tempJ.getSize())) {
                    tempP2.add(tempJ);
                    tempJ.setRunning(tempP2.getPartNum());
                }
            }
            *iterator3 = tempP2;
        }

        minMemWaste = std::numeric_limits<double>::max();
        *iterator = tempJ;
    }
}
