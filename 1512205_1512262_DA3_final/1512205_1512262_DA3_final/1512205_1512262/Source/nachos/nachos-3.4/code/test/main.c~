// main.c
#include "syscall.h"

int
main()
{
    OpenFileID inp, sv, out, res;
    char c[1];
    int n, ret;
    SpaceID svproc;
    ret = CreateF("output.txt");
    if (ret == -1) ExitProc(-1);
    ret = CreateSemaphore("sinhvien", 0);
    if (ret == -1) ExitProc(-1);
    ret = CreateSemaphore("voinuoc", 0);
    if (ret == -1) ExitProc(-1);
    inp = OpenF("input.txt", 1);
    if (inp == -1) ExitProc(-1);
    out = OpenF("output.txt", 0);
    if (out == -1) {
        CloseF(inp);
        ExitProc(-1);
    } 
    n = 0;
    while (1) {
        if (ReadF(c, 1, inp) == 0) break;
        if (c[0] >= '0' && c[0] <= '9') n = 10*n + c[0] - '0';
        else if (c[0] == '\n') break;
    }
    while (n--) {
        ret = CreateF("sinhvien.txt");
        if (ret == -1) {
            CloseF(inp);
            ExitProc(-1);
        }
        sv = OpenF("sinhvien.txt", 0);
        if (sv == -1) {
            CloseF(inp);
            ExitProc(-1);
        }
        while (1) {
            if (ReadF(c, 1, inp) == 0) break;
            WriteF(c, 1, sv);
            if (c[0] == '\n') break;
        }
        CloseF(sv);
        svproc = ExecProc("test/sinhvien");
        if (svproc != -1) ret = JoinProc(svproc);
        if (ret == -1) {
            CloseF(inp);
            CloseF(out);
            ExitProc(-1);
        }
        res = OpenF("result.txt", 0);
        if (res == -1) {
            CloseF(inp);
            CloseF(out);
            ExitProc(-1);
        }
        while (ReadF(c, 1, res) != 0)
            WriteF(c, 1, out);
        CloseF(res);
    }
    ExitProc(0);
}
