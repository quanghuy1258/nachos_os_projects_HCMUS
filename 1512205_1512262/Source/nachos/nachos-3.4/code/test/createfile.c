/*createfile program*/
#include "syscall.h"

int
main()
{
    int chk;
    chk = CreateF("text.txt");
    if (chk == 0) WriteF("Create text.txt: Successful\n", 29, ConsoleOutput);
    else if (chk == -1) WriteF("Create text.txt: Failed\n", 25, ConsoleOutput);
    else WriteF("Create text.txt: Unknown\n", 26, ConsoleOutput);
    Halt();
}
