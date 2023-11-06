#include "PrintJob.h"

PrintJob::PrintJob(int setP, int setJ, int numP)
    : priority(setP), jobNumber(setJ), numPages(numP) {}

PrintJob::PrintJob(PrintJob *cpy)
    : priority(cpy.getPriority()),
      jobNumber(cpy.getJobNumber(), numPages(cpy.getPages())) {}

// TODO Not sure how to write a destructor
PrintJob::~PrintJob() : priority(0), jobNumber(0), numPages(0) {}

int PrintJob::getPriority() { return priority; }

int PrintJob::getJobNumber() { return jobNumber; }

int PrintJob::getPages() { return numPages; }
