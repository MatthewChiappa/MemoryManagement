#ifndef FIRSTFIT_H
#define FIRSTFIT_H
#include <list>
#include "partition.h"
#include "job.h"

class FirstFit
{
public:
    FirstFit();
    FirstFit(std::list<Partition> parts, std::list<Job> jobs);
    std::list<Partition> getParts();
    std::list<Job> getJobs();
private:
    std::list<Partition> parts;
    std::list<Job> jobs;
    void begin();
};

#endif // FIRSTFIT_H
