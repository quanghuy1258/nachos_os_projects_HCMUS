/*copy program*/
#include "syscall.h"

int
main()
{
    char s[128];
    int chk, ret;
    OpenFileID inpf, outf;
    WriteF("Input file name: ", 18, ConsoleOutput);
    ret = ReadF(s, 9, ConsoleInput);
    s[ret] = 0;
    inpf = OpenF(s, 1);
    if (inpf != -1) {
        WriteF("Output file name: ", 19, ConsoleOutput);
        ret = ReadF(s, 9, ConsoleInput);
        s[ret] = 0;
        chk = CreateF(s);
        if (chk == 0) {
            outf = OpenF(s, 0);
            while (1) {
                ret = ReadF(s, 128, inpf);
                if (ret <= 0) break;
                WriteF(s, ret, outf);
            }
            CloseF(outf);
            WriteF("Copy file: Success\n", 20, ConsoleOutput);
        } else WriteF("Cannot create file to copy\n", 28, ConsoleOutput);
        CloseF(inpf);
    } else WriteF("Input file not exist\n", 16, ConsoleOutput);
    Halt();
}
