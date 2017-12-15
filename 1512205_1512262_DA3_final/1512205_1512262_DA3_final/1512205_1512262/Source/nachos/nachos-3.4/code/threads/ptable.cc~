// ptable.cc
#include "system.h"
#include "ptable.h"

PTable::PTable() {
    _bm = new BitMap(MAX_PROCESS);
    _bmsem = new Semaphore("bmsem", 1);
    for (int i = 0; i < MAX_PROCESS; ++i)
        _pcb[i] = NULL;
}

PTable::~PTable() {
    delete _bm;
    delete _bmsem;
    for (int i = 0; i < MAX_PROCESS; ++i) {
        if (_pcb[i] == NULL) continue;
        delete _pcb[i];
    }
}

int PTable::ExecUpdate(char *filename) {
    _bmsem->P();
    if (filename == NULL) {
        _bmsem->V();
        return -1;
    }
    OpenFile *executable = fileSystem->Open(filename);
    if (executable == NULL) {
        _bmsem->V();
        return -1;
    }
    delete executable;
    int parentID = -1;
    int processID;
    if (_bm->NumClear() == MAX_PROCESS) {
        processID = 0;
        _bm->Mark(processID);
    } else {
        if (strncmp(currentThread->getName(), filename, PCB_MAXNAMESIZE-1) == 0) {
            _bmsem->V();
            return -1;
        }
        for (int i = 0; i < MAX_PROCESS; ++i) {
            if (_pcb[i] == NULL) continue;
            if (_pcb[i]->GetThread() == currentThread) {
                parentID = i;
                break;
            }
        }
        if (parentID == -1) {
            _bmsem->V();
            return -1;
        }
        processID = _bm->Find();
        if (processID == -1) {
            _bmsem->V();
            return -1;
        }
    }
    _pcb[processID] = new PCB();
    int ret = _pcb[processID]->Exec(filename, processID, parentID);
    if (ret == -1) {
        _bm->Clear(processID);
        delete _pcb[processID];
        _bmsem->V();
        return -1;
    }
    _bmsem->V();
    return processID;
}

int PTable::ExitUpdate(int ec) {
    int processID = -1;
    for (int i = 0; i < MAX_PROCESS; ++i) {
        if (_pcb[i] == NULL) continue;
        if (_pcb[i]->GetThread() == currentThread) {
            processID = i;
            break;
        }
    }
    if (processID == -1) return -1;
    int parentID = _pcb[processID]->GetParentID();
    if (parentID == -1) {
        interrupt->Halt();
        return 0;
    } else {
        _pcb[parentID]->JoinRelease(processID, ec);
        delete _pcb[processID];
        _pcb[processID] = NULL;
        _bm->Clear(processID);
        delete currentThread->space;
        currentThread->Finish();
    }
}

int PTable::JoinUpdate(int id) {
    if (id < 0 || id >= MAX_PROCESS) return -1;
    if (_bm->Test(id) == 0) return -1;
    int processID = -1;
    for (int i = 0; i < MAX_PROCESS; ++i) {
        if (_pcb[i] == NULL) continue;
        if (_pcb[i]->GetThread() == currentThread) {
            processID = i;
            break;
        }
    }
    if (processID == -1) return -1;
    if (_pcb[id]->GetParentID() != processID) return -1;
    _pcb[processID]->JoinWait(id);
    int ec = _pcb[processID]->GetJoinExitCode();
    return ec;
}
