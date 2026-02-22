//.\gcc -shared -m32 utils.c -o utils.dll -mwindows

#include <windows.h>

__declspec(dllexport)
void msgbox(HWND hwnd, HINSTANCE hinst, LPSTR cmd, int show)
{
    MessageBox(NULL, cmd, "msg", MB_OK);
}