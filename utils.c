//.\gcc -shared -m32 utils.c -o utils.dll -mwindows

#include <windows.h>
#include <stdio.h>
#include <string.h>
#define ID_EDIT   101
#define ID_BUTTON 102

static char g_text[256];
static HWND g_edit;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
        {
            CreateWindow("STATIC", "Enter text:",
                WS_VISIBLE | WS_CHILD,
                10, 10, 260, 20,
                hwnd, NULL, NULL, NULL);

            g_edit = CreateWindow("EDIT", "",
                WS_VISIBLE | WS_CHILD | WS_BORDER,
                10, 35, 260, 25,
                hwnd, (HMENU)ID_EDIT, NULL, NULL);

            CreateWindow("BUTTON", "OK",
                WS_VISIBLE | WS_CHILD,
                100, 70, 80, 30,
                hwnd, (HMENU)ID_BUTTON, NULL, NULL);

            SetFocus(g_edit);
        }
        break;

        case WM_COMMAND:
        {
            if(LOWORD(wParam) == ID_BUTTON)
            {
                GetWindowText(g_edit, g_text, sizeof(g_text));
                DestroyWindow(hwnd);
            }
        }
        break;

        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


__declspec(dllexport)
void ShowInputBox(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow)
{
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hinst;
    wc.lpszClassName = "MyInputBoxClass";

    RegisterClass(&wc);

    HWND hWnd = CreateWindow(
        "MyInputBoxClass",
        "InputBox DLL",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        300, 150,
        NULL, NULL, hinst, NULL);

    ShowWindow(hWnd, SW_SHOW);

    // Se rundll32 passou texto inicial, coloca no edit
    if(lpszCmdLine && lpszCmdLine[0] != 0)
    {
        SetWindowText(g_edit, lpszCmdLine);
    }

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    //MessageBox(NULL, g_text, "You typed:", MB_OK | MB_ICONINFORMATION);
    FILE *f = fopen("result.txt", "w");
    if (f) {
        fprintf(f, "%s\n", g_text);
        fclose(f);
    }

    
}
__declspec(dllexport)
void msgbox(HWND hwnd, HINSTANCE hinst, LPSTR cmd, int show)
{
    MessageBox(NULL, cmd, "msg", MB_OK);
}