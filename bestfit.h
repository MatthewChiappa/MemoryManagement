#ifndef BESTFIT_H
#define BESTFIT_H
#include <list>
#include "partition.h"
#include "job.h"

class BestFit
{
public:
    BestFit();
    BestFit(std::list<Partition> parts, std::list<Job> jobs);
    std::list<Partition> getParts();
    std::list<Job> getJobs();
private:
    std::list<Partition> parts;
    std::list<Job> jobs;
    void begin();
};

#endif // BESTFIT_H
