/*cat program*/
#include "syscall.h"

int
main()
{
    char s[128];
    int chk, ret;
    OpenFileID f;
    WriteF("Input file name: ", 18, ConsoleOutput);
    ret = ReadF(s, 9, ConsoleInput);
    s[ret] = 0;
    f = OpenF(s, 1);
    if (f != -1) {
        while (1) {
            ret = ReadF(s, 128, f);
            if (ret <= 0) break;
            WriteF(s, ret, ConsoleOutput);
        }
        CloseF(f);
    } else WriteF("File not exist\n", 16, ConsoleOutput);
    Halt();
}
