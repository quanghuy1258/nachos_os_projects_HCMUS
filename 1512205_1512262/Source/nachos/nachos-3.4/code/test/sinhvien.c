/*sinhvien program*/
#include "syscall.h"

int
main()
{
    OpenFileID sv, vn;
    SpaceID vnproc;
    char c[1];
    int ret;
    sv = OpenF("sinhvien.txt", 1);
    if (sv == -1) ExitProc(-1);
    vnproc = ExecProc("test/voinuoc");
    if (vnproc == -1) {
        CloseF(sv);
        ExitProc(-1);
    }
    ret = -1;
    while (ret != 0) {
        ret = CreateF("voinuoc.txt");
        if (ret == -1) {
            CloseF(sv);
            ExitProc(-1);
        }
        vn = OpenF("voinuoc.txt", 0);
        if (vn == -1) {
            CloseF(sv);
            ExitProc(-1);
        }
        while (1) {
            if (ReadF(c, 1, sv) == 0) {
                WriteF("0", 1, vn);
                ret = 0;
                break;
            } else ret = -1;
            if (c[0] == ' ' || c[0] == '\n') break;
            WriteF(c, 1, vn);
        }
        CloseF(vn);
        Signal("voinuoc");
        Wait("sinhvien");
    }
    ExitProc(0);
}
