#ifndef __PRINTJOB_H
#define __PRINTJOB_H

using namespace std;

class PrintJob {
private:
  int priority;
  int jobNumber;
  int numPages;

public:
  PrintJob(int, int, int);
  PrintJob(PrintJob *);
  int getPriority();
  int getJobNumber();
  int getPages();
};
#endif
