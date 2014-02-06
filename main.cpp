#include <windows.h>
#include <sstream>
#include <string>
#pragma comment(lib, "user32.lib")
using namespace std;
template <typename T>
string NumberToString ( T Number )
{
	ostringstream ss;
	ss << Number;
	return ss.str();
}
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
int PrimeNumb[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157};
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    MSG msg;
    BOOL bQuit = FALSE;
//===========================================================
    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "MainWindowClass";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;
    if (!RegisterClassEx(&wcex)) return 0;
//===========================================================
    /* create main window */
    hwnd = CreateWindowEx(0,
                          "MainWindowClass",
                          "Goldbach's conjecture",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          500,
                          500,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
    ShowWindow(hwnd, nCmdShow);
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }
    /* destroy the window explicitly */
    DestroyWindow(hwnd);
    return msg.wParam;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	string numb_plus_numb;
	switch (uMsg)
	{
		case WM_CLOSE: PostQuitMessage(0); break;
		case WM_DESTROY: return 0;
		case WM_KEYDOWN:
		switch (wParam)
		{
			case VK_ESCAPE:
				PostQuitMessage(0);
			break;
		}
		break;
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			LOGFONT fount_conf;
			memset(&fount_conf,0,sizeof(LOGFONT));
			fount_conf.lfHeight = 16;
			fount_conf.lfWeight = FW_NORMAL;
			fount_conf.lfCharSet = DEFAULT_CHARSET;
			strcpy(fount_conf.lfFaceName,"Arial");
			HFONT font;
			font = CreateFontIndirect(&fount_conf);
			SelectObject(hdc, font);
			for(int i = 0; i < 25; i++)
				for(int j = i; j < 25; j++ )
				{
					numb_plus_numb.clear();
					//numb_plus_numb = "{" + NumberToString(PrimeNumb[i]) + "+" + NumberToString(PrimeNumb[j]) + "}";
					numb_plus_numb = NumberToString(PrimeNumb[i] + PrimeNumb[j]);
					TextOut(hdc, (j+1)*48-48*i-20, (i+1)*20, numb_plus_numb.c_str(), numb_plus_numb.size());
				}
		break;
		default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}



