/*echo program*/
#include "syscall.h"

int
main()
{
    char s[128];
    int ret;
    while (1) {
        WriteF("Input: ", 8, ConsoleOutput);
        ret = ReadF(s, 128, ConsoleInput);
        if (ret <= 0) break;
        WriteF("Output: ", 9, ConsoleOutput);
        WriteF(s, ret, ConsoleOutput);
        WriteF("\n", 2, ConsoleOutput);
    }
    Halt();
}
