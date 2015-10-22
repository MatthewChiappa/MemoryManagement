#ifndef WORSTFIT_H
#define WORSTFIT_H
#include <list>
#include "partition.h"
#include "job.h"

class WorstFit
{
public:
    WorstFit();
    WorstFit(std::list<Partition> parts, std::list<Job> jobs);
    std::list<Partition> getParts();
    std::list<Job> getJobs();
private:
    std::list<Partition> parts;
    std::list<Job> jobs;
    void begin();
};

#endif // WORSTFIT_H
