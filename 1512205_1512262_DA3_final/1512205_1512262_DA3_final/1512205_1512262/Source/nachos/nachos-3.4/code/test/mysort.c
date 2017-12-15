/*sort program*/
#include "syscall.h"

int
main()
{
    int N, i, j, tmp;
    int a[100];
    PrintChar('\n');
    PrintString("SORT - PROJECT 1 - OS\n");
    PrintChar('\n');
    PrintString("Input N = ");
    N = ReadInt();
    if (N < 1 || N > 100) {
        PrintString("Invalid Number. 1 <= N <= 100 \n");    
        Halt();
    }
    for (i = 0; i < N; i++) {
        a[i] = 0;
        PrintString("a[");
        PrintInt(i);
        PrintString("] = ");
        a[i] = ReadInt();
    }
    for (i = 0; i < N-1; i++) {
        for (j = N-1; j > i; j--) {
            if (a[j-1] > a[j]) {
                tmp = a[j];
                a[j] = a[j-1];
                a[j-1] = tmp;
            }
        }
    }
    PrintString("Sorted array:");
    for (i = 0; i < N; i++) {   
        PrintChar(' ');
        PrintInt(a[i]);
    }
    PrintChar('\n');
    Halt();
}
