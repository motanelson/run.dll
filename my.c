//.\gcc -shared -m32 my.c -o my.dll -mwindows

#include <windows.h>

#include <windows.h>

__declspec(dllexport)
void myfunc(HWND hwnd, HINSTANCE hinst, LPSTR cmd, int show)
{
    MessageBox(NULL, cmd, "msg", MB_OK);
}