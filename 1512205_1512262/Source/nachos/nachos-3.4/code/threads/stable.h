// stable.h
#ifndef STABLE_H
#define STABLE_H

#include "sem.h"
#include "bitmap.h"

#define MAX_SEMAPHORE 10

class STable {
private:
    BitMap* _bm;
    Sem* _semTab[MAX_SEMAPHORE];
public:
    STable();
    ~STable();
    int Create(char *name, int init);
    int Wait(char *name);
    int Signal(char *name);
};
#endif
