#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <fstream>
#include <iostream>

//basic
static TCHAR szWindowClass[] = _T("pnc");
static TCHAR szTitle[] = _T("Prime number calculator");
HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


//func
static void Reflesh(HWND hwnd)
{
    std::ifstream read;
    read.open("result.txt", std::ios::in);
    if (!read) {
        MessageBox(NULL, 
            _T("Failed to read result.txt"),
            _T("Prime number calculator"),
            MB_ICONERROR);
    }
    std::string text(
        (std::istreambuf_iterator<char>(read)),
        std::istreambuf_iterator<char>()
    );
    read.close();
    int len = MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, NULL, 0);
    std::wstring wtext(len, 0);
    MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, &wtext[0], len);
    SetWindowText(hwnd, wtext.c_str());
}

static void pnc(int a, int b,HWND hwnd)
{
    std::ofstream output;
    output.open("result.txt", std::ios::out);
    if (!output)
    {
        MessageBox(NULL,
            _T("Failed to open result.txt"),
            _T("Prime number calculator"),
            MB_ICONERROR);
    }

    output << "###BEGIN###\r\n";
    for (int i = a; i <= b - a + 1; i++)
    {
        if(i==2) output << "2" ;
        else if (i==3) output << " 3 " ;
        int j = 0;
        for (int k = 2; k < i - 1; k++)
        {
            if (i % k == 0) break;
            else j++;
            if (j == i - 3)
            {
                output << " " << i;
                break;
            }
        }
    }
    output << "\r\n###FINISH###" << std::endl;
    Reflesh(hwnd);
    output.close();
}

static HWND hOutput = NULL;

//main
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    // window config
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Prime number calculator"),
            MB_ICONERROR);
        return 1;
    }


    //window&control create HERE
    hInst = hInstance;
    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,szTitle,
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 
        CW_USEDEFAULT, CW_USEDEFAULT,
        530, 560, NULL,NULL,
        hInstance, NULL
    );
     if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Prime number calculator"),
            NULL);
        return 1;
    }
     
     HWND hLabel = CreateWindow(
         L"STATIC",  L"Left                 Right",    
         WS_VISIBLE | WS_CHILD,  
        30,55,200,40,
         hWnd, NULL, 
         (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
     );

     HWND hwndWriteL = CreateWindow(
         L"EDIT", NULL,
         WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL | ES_LEFT | ES_NUMBER,
         30,80, 60, 35,
         hWnd, (HMENU)2001,
         (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
     );
     HWND hwndWriteR = CreateWindow(
         L"EDIT", NULL,
         WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_AUTOHSCROLL | ES_LEFT | ES_NUMBER,
         120, 80, 60, 35,
         hWnd, (HMENU)2002,
         (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
     );
     HWND hwndButton = CreateWindow(
         L"BUTTON", L"compute",
         WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
         260 ,60, 100, 50,
         hWnd, (HMENU)1001,
         (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
     );

     hOutput = CreateWindow(
         L"EDIT", NULL,
         WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_READONLY | WS_VSCROLL,
         30, 170, 450, 300,
         hWnd, (HMENU)3001,
         (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL
     );
     
     if (!hwndWriteL || !hwndButton || !hwndWriteR) {
         MessageBox(NULL, _T("Control creating failed!"), szTitle, MB_ICONERROR);
         return 1;
     }

    // vision_able
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    //loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

// funcion HERE
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("by xksyu2021");

    switch (message)
    {
    
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        TextOut(hdc,
            5, 5,
            greeting, _tcslen(greeting));

        EndPaint(hWnd, &ps);
        break;

    case WM_COMMAND:
    {
        WORD wmId = LOWORD(wParam);
        switch (wmId)
        {
        case 1001: 

            TCHAR leftText[32], rightText[32];
            int left,right;
            GetWindowText(GetDlgItem(hWnd, 2001), leftText, 32);
            GetWindowText(GetDlgItem(hWnd, 2002), rightText, 32);

            left = _ttoi(leftText);
            right = _ttoi(rightText);

            if ((left == 0  || left < 2 ) && leftText[0] != '0') 
            {
                MessageBox(hWnd, _T("Please enter a valid number in the left box."), _T("Error"), MB_ICONERROR);
                break;
            }
             if ( (right == 0 || right < 2 || right < left) && rightText[0] != '0')
             {
                MessageBox(hWnd, _T("Please enter a valid number in the right box."), _T("Error"), MB_ICONERROR);
                break;
            }
             if (right - left > 200000 )
             {
                 MessageBox(hWnd, _T("OUT OF MEMORY!"), _T("Error"), MB_ICONERROR);
                 break;
             }

             pnc(left, right,hOutput);

            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
     return 0;
}