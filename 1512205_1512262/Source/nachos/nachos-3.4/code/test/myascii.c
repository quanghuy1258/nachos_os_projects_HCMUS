/*ascii program*/
#include "syscall.h"

int
main()
{
    int c;
    PrintChar('\n');
    PrintString("SORT - PROJECT 1 - OS\n");
    PrintChar('\n');
    PrintString("All printable ascii characters:\n");
    for (c = 32; c < 127; c++) {
        PrintChar(c);
        PrintChar(':');
        PrintInt(c);
        PrintChar('\n');
    }
    Halt();
}
