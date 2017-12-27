// pcb.cc

#include "pcb.h"
#include "system.h"

PCB::PCB() {
    memset(_filename, 0, PCB_MAXNAMESIZE);
    _thread = NULL;
    _parentID = -1;
    _processID = -1;
    _joinsem = new Semaphore("joinsem", 0);
    _exitsem = new Semaphore("exitsem", 0);
    _mutex = new Semaphore("mutex", 1);
    _joinid = -1;
    _joinexitcode = 0;
    _numwait = 0;
    _isExit = 0;
}

PCB::~PCB() {
    delete _joinsem;
    delete _exitsem;
    delete _mutex; 
}

void exec_func(int) {
    currentThread->space->InitRegisters();		
    currentThread->space->RestoreState();		
    machine->Run();
} 

int PCB::Exec(char *filename, int processID, int parentID) {
    _mutex->P();
    if (filename == NULL || processID < 0 || _thread != NULL) {
        _mutex->V();
        return -1;
    }
    OpenFile *executable = fileSystem->Open(filename);
    if (executable == NULL) {
        _mutex->V();
        return -1;
    }
    _processID = processID;
    _parentID = parentID;
    strncpy(_filename, filename, PCB_MAXNAMESIZE-1);
    _thread = new Thread(_filename);    
    _thread->space = new AddrSpace(executable);
    delete executable;
    if (_parentID == -1) {
        Thread *tmpthread = currentThread;
        currentThread = _thread;
        currentThread->setStatus(RUNNING);
        delete tmpthread;
        _thread->space->InitRegisters();
        _thread->space->RestoreState();
    }
    else _thread->Fork(exec_func, 0);
    _mutex->V();
    return 0;
}

void PCB::JoinWait(int joinid) {
    if (_joinid != -1) return;
    _joinid = joinid;
    _joinsem->P();
}

void PCB::JoinRelease(int joinid, int joinexitcode) {
    if (_joinid != joinid) return;
    _joinid = -1;
    _joinexitcode = joinexitcode;
    _joinsem->V();
}

void PCB::ExitWait() {
    if (_numwait > 0) {
        _isExit = 1;
        _exitsem->P();
    }
}

void PCB::ExitRelease() {
    if (_numwait == 0 && _isExit == 1)
        _exitsem->V();
}

void PCB::IncNumWait() {
    ++_numwait;
}

void PCB::DecNumWait() {
    if (_numwait > 0)
        --_numwait;
}

int PCB::GetParentID() {
    return _parentID;
}

int PCB::GetProcessID() {
    return _processID;
}

int PCB::GetJoinID() {
    return _joinid;
}

int PCB::GetJoinExitCode() {
    return _joinexitcode;
}

char* PCB::GetFileName() {
    return _filename;
}

Thread* PCB::GetThread() {
    return _thread;
}
