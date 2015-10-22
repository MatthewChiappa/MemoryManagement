#include "nextfit.h"

// init
NextFit::NextFit()
{
}

// second init
NextFit::NextFit(std::list<Partition> parts2, std::list<Job> jobs2)
{
   parts = parts2;
   jobs = jobs2;
   begin();
}

// returns the list of partitions
std::list<Partition> NextFit::getParts()
{
    return parts;
}

// returns the list of jobs
std::list<Job> NextFit::getJobs()
{
    return jobs;
}

// starts the next fit algorithm
void NextFit::begin()
{
    // assign the current partition to be check to the beginning
    std::list<Partition>::iterator currIt = parts.begin();

    // for every job go through every partition
    std::list<Job>::iterator iterator;
    for (iterator = jobs.begin(); iterator != jobs.end(); ++iterator) {
        Job tempJ = *iterator;

        std::list<Partition>::iterator iterator2;
        for (iterator2 = currIt; iterator2 != parts.end(); ++iterator2) {
            Partition tempP = *iterator2;

            // if the partition is not busy, it fits, and the job is not already running,
            // start the job and assign the current partition to the next partition
            if(!tempP.isBusy() && tempJ.getSize() <= tempP.getSize() && !tempJ.isRunning()){
                tempP.add(tempJ);
                tempJ.setRunning(tempP.getPartNum());
                currIt = iterator2;
            }

            if (iterator2 == parts.end()){
                currIt = parts.begin();
            }

            *iterator2 = tempP;
        }

        // if the job hasn't ran yet assign it to next partition with
        // hole size of 0
        if(!tempJ.isRunning()){
            std::list<Partition>::iterator iterator3;
            for (iterator3 = parts.begin(); iterator3 != parts.end(); ++iterator3) {
                Partition tempP = *iterator3;

                // if the partition is not busy, it fits, and the job is not already running,
                // assign the job to the partition
                if(!tempP.isBusy() && tempJ.getSize() <= tempP.getSize() && !tempJ.isRunning()){
                    tempP.add(tempJ);
                    tempJ.setRunning(tempP.getPartNum());
                }
                *iterator3 = tempP;
            }

        }

        *iterator = tempJ;
    }

}
