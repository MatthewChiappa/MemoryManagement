#ifndef NEXTFIT_H
#define NEXTFIT_H
#include <list>
#include "partition.h"
#include "job.h"

class NextFit
{
public:
    NextFit();
    NextFit(std::list<Partition> parts, std::list<Job> jobs);
    std::list<Partition> getParts();
    std::list<Job> getJobs();
private:
    std::list<Partition> parts;
    std::list<Job> jobs;
    void begin();
};

#endif // NEXTFIT_H
