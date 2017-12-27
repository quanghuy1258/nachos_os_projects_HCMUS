// sem.cc
#include "sem.h"

Sem::Sem() {
    memset(_name, 0, SEM_MAXNAMESIZE);
    _sem = NULL;
}

Sem::~Sem() {
    if (_sem != NULL) delete _sem;
}

int Sem::Create(char *name, int semval) {
    if (name == NULL || semval < 0 || _sem != NULL) return -1;
    strncpy(_name, name, SEM_MAXNAMESIZE-1);
    _sem = new Semaphore(_name, semval);
    return 0;
}

void Sem::Delete() {
    if (_sem == NULL) return;
    memset(_name, 0, SEM_MAXNAMESIZE);
    delete _sem;
    _sem = NULL;
}

void Sem::Wait() {
    if (_sem != NULL) _sem->P();
}

void Sem::Signal() {
    if (_sem != NULL) _sem->V();
}

char* Sem::GetName() {
    return _name;
}
