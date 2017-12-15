// stable.cc
#include "stable.h"

STable::STable() {
    for (int i = 0; i < MAX_SEMAPHORE; ++i)
        _semTab[i] = NULL;
    _bm = new BitMap(MAX_SEMAPHORE);
}

STable::~STable() {
    for (int i = 0; i < MAX_SEMAPHORE; ++i) {
        if (_semTab[i] == NULL) continue;
        delete _semTab[i];
    }
    delete _bm;
}

int STable::Create(char *name, int init) {
    if (name == NULL || init < 0) return -1;
    int id;
    for (id = 0; id < MAX_SEMAPHORE; ++id) {
        if (_semTab[id] == NULL) continue;
        if (strncmp(_semTab[id]->GetName(), name, SEM_MAXNAMESIZE-1) == 0) return -1;
    }
    id = _bm->Find();
    if (id == -1) return -1;
    _semTab[id] = new Sem();
    int ret = _semTab[id]->Create(name, init);
    if (ret == -1) {
        _bm->Clear(id);
        return -1;
    } else return 0;
}

int STable::Wait(char *name) {
    if (name == NULL) return -1;
    for (int i = 0; i < MAX_SEMAPHORE; ++i) {
        if (_semTab[i] == NULL) continue;
        if (strncmp(_semTab[i]->GetName(), name, SEM_MAXNAMESIZE-1) == 0) {
            _semTab[i]->Wait();
            return 0;
        }
    }
    return -1;
}

int STable::Signal(char *name) {
    if (name == NULL) return -1;
    for (int i = 0; i < MAX_SEMAPHORE; ++i) {
        if (_semTab[i] == NULL) continue;
        if (strncmp(_semTab[i]->GetName(), name, SEM_MAXNAMESIZE-1) == 0) {
            _semTab[i]->Signal();
            return 0;
        }
    }
    return -1;
}
