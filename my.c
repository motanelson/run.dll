//.\gcc -shared -o my.dll my.c 

#include <windows.h>

#include <windows.h>

__declspec(dllexport)
void myfunc(HWND hwnd, HINSTANCE hinst, LPSTR cmd, int show)
{
    MessageBox(NULL, cmd, "msg", MB_OK);
}