#ifndef PTABLE_H
#define PTABLE_H

#include "bitmap.h"
#include "pcb.h"
#include "synch.h"

#define MAX_PROCESS 10

class PTable {
private:
    BitMap *_bm;
    Semaphore *_bmsem;
    PCB *_pcb[MAX_PROCESS];
public:
    PTable();
    ~PTable();
    int ExecUpdate(char *filename);    //create and execute a new thread. return 0 if success and -1 if failure
    int ExitUpdate(int ec);
    int JoinUpdate(int processID);     //join process. return 0 if success and -1 if failure
};
#endif
