#include <iostream>
#include <list>
#include <sstream>
#include <fstream>

#include "job.h"
#include "partition.h"
#include "firstfit.h"
#include "bestfit.h"
#include "nextfit.h"
#include "worstfit.h"

using namespace std;

// method declaration
void begin();
bool checkSizes(double memSize, std::list<double> partSizes);
void print(std::list<Partition> parts, std::list<Job> jobs, double memSize);
std::list<Partition> getPartitions(std::list<double> partSizes);
std::list<double> getSizes();
std::list<Job> getJobs();
double totalMemWaste(std::list<Partition> parts);
void printOutput(std::list<Partition> parts, std::list<Job> jobs);

int main()
{
    // start main screen
    begin();

    // while the user is not inputting q, run main screen
    char c;
    do
    {
        cout << "Press c to continue or q to quit. " << endl;
        cin >> c;
        if(c == 'c')
            begin();
        else if(c != 'q' && c != 'c')
            cout << "That is not a correct input." << endl;
    }
    while (c != 'q');

    return 0;
}

// used to input memory size and partition sizes
void begin()
{
    // get total memory size
    double memSize = 0;
    cout << "Create txt file named ""jobs.txt"" for jobs and input total memory size: " << endl;
    cin >> memSize;

    // get sizes of partitions
    cout << "Input size of each partition with a max of 5: " << endl;
    std::list<double> partSizes = getSizes();
    bool exceed = checkSizes(memSize, partSizes);

    // if there are more than 5 partitions or the memory size does not equal
    // total partition size, print error and return to main screen
    if(partSizes.size() > 5 || exceed) {
        cout << endl << "ERROR: Amount of partitions exceed 5 " <<
                "or memory size does not equal patrition size." << endl << endl;
        return;
    }

    // get the sizes of the partitions and jobs
    // and create the partition objects and job objects
    std::list<Partition> parts = getPartitions(partSizes);
    std::list<Job> jobs = getJobs();

    // print the partitions, jobs and memory size to console
    print(parts, jobs, memSize);

    // create objects for each algorithm and print the output
    cout << "First-Fit Algorithm:" << endl;
    FirstFit first = FirstFit(parts, jobs);
    printOutput(first.getParts(), first.getJobs());

    cout << endl << "Best-Fit Algorithm:" << endl;
    BestFit best = BestFit(parts, jobs);
    printOutput(best.getParts(), best.getJobs());

    cout << endl << "Next-Fit Algorithm:" << endl;
    NextFit next = NextFit(parts, jobs);
    printOutput(next.getParts(), next.getJobs());

    cout << endl << "Worst-Fit Algorithm:" << endl;
    WorstFit worst = WorstFit(parts, jobs);
    printOutput(worst.getParts(), worst.getJobs());

}

// checks if the size of the memory equals the total sum of the partitions
bool checkSizes(double memSize, std::list<double> partSizes)
{
    // add up the sum of the parition sizes and compare
    double sum = 0;
    std::list<double>::const_iterator iterator2;
    for (iterator2 = partSizes.begin(); iterator2 != partSizes.end(); ++iterator2) {
        sum += *iterator2;
    }

    if (memSize != sum)
        return true;
    else
        return false;
}

// prints the initial partitions, jobs and memory size
void print(std::list<Partition> part, std::list<Job> jobs, double memSize)
{
    cout << endl << "Total Memory Size: " << memSize << endl;

    cout << endl << "Partitions: " << endl;
    std::list<Partition>::const_iterator iterator2;
    for (iterator2 = part.begin(); iterator2 != part.end(); ++iterator2) {
        Partition temp = *iterator2;
        std::cout <<  temp.getPartNum() << "\t" << temp.getSize() << endl;
    }

    cout << endl << "Jobs: " << endl;
    std::list<Job>::const_iterator iterator;
    for (iterator = jobs.begin(); iterator != jobs.end(); ++iterator) {
        Job temp = *iterator;
        std::cout << temp.getName() << "\t" << temp.getSize() << endl;
    }
    cout << endl;
}

// creates the partition objects from the partition sizes
std::list<Partition> getPartitions(std::list<double> partSizes)
{
    int i = 1;
    std::list<Partition> parts;
    std::list<double>::const_iterator iterator2;
    for (iterator2 = partSizes.begin(); iterator2 != partSizes.end(); ++iterator2) {
        std::string name = "P0" + i;
        Partition temp = Partition(*iterator2, i);
        parts.push_back(temp);
        i++;
    }

    return parts;
}

// converts the input of the partition sizes to a list of doubles
std::list<double> getSizes()
{
    std::list<double> partSizes;
    double temp;
    cin >> temp;
    partSizes.push_back(temp);

    std::string line;
    std::getline(cin, line);
    std::istringstream iss(line);

    while (iss >> temp) {
        partSizes.push_back(temp);
    }

    return partSizes;
}

// gets the file of jobs and returns a list of job objects
std::list<Job> getJobs()
{
    ifstream file;
    file.open ("/home/mchiappa/CSC305_Lab2/jobs.txt");
    std::list<Job> list;

    while (!file.eof()){
        std::string name;
        double size;

        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);

        iss >> name;
        iss >> size;
        if(name != ""){
            Job temp = Job(name, size);
            list.push_back(temp);
        }
    }

    file.close();

    return list;
}

// calculates the total memory waste of all the partitions
double totalMemWaste(std::list<Partition> parts)
{
    double sum = 0;
    std::list<Partition>::const_iterator iterator;
    for (iterator = parts.begin(); iterator != parts.end(); ++iterator) {
        Partition tempP = *iterator;
        sum += tempP.getHoleSize();
        if (!tempP.isBusy())
            sum += tempP.getSize();
    }
    return sum;
}

// prints the final output od the partitions and jobs
void printOutput(std::list<Partition> parts, std::list<Job> jobs)
{
    // print the partition's number, size, status, hole size and total
    // memory waste for the entire set of partitions
    cout << endl << "Partitions: " << endl;
    std::list<Partition>::const_iterator iterator2;
    for (iterator2 = parts.begin(); iterator2 != parts.end(); ++iterator2) {
        Partition temp = *iterator2;
        std::cout <<  temp.getPartNum() << "\t" << temp.getSize() << endl;

        cout << "Status: ";
        if(temp.isBusy())
            cout << "Busy" << "-\t" << temp.getJobName() << endl;
        else
            cout << "Free" << endl;

        cout << "Hole Size: " << temp.getHoleSize() << endl << endl;
    }

    cout << "Total Memory Waste: " << totalMemWaste(parts) << endl;

    // prints the jobs that are waiting to be allocated, if there arent
    // any jobs running, print NONE
    bool oneRunning = false;
    cout << endl << "Waiting Jobs: " << endl;
    std::list<Job>::const_iterator iterator;
    for (iterator = jobs.begin(); iterator != jobs.end(); ++iterator) {
        Job temp = *iterator;
        if(!temp.isRunning()){
            oneRunning = true;
            std::cout << temp.getName() << endl;
        }
    }
    if (!oneRunning)
        cout << "NONE";
    cout << endl;
}
