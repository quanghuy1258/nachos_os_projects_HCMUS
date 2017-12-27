/*voinuoc program*/
#include "syscall.h"

int
main()
{
    int n, v1, v2;
    OpenFileID vn, res;
    char c[1];
    CreateF("result.txt");
    res = OpenF("result.txt", 0);
    n = -1;
    v1 = v2 = 0;
    while (1) {
        if (n == 0) break;
        Wait("voinuoc");
        vn = OpenF("voinuoc.txt", 1);
        n = 0;
        while (1) {
            if (ReadF(c, 1, vn) == 0) break;
            if (c[0] >= '0' && c[0] <= '9') n = 10*n + c[0] - '0';
            else break;
        }
        CloseF(vn);
        if (n != 0) {
            if (v1 <= v2) {
                v1 += n;
                if (res != -1) 
                    WriteF("1 ", 2, res);
            } else {
                v2 += n;
                if (res != -1)
                    WriteF("2 ", 2, res);
            }
        }
        Signal("sinhvien");
    }
    if (res != -1) {
        WriteF("\n", 1, res);
        CloseF(res);
    }
    ExitProc(0);
}
