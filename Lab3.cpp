// Lab3.cpp : Определяет точку входа для приложения.
//
#include <Windows.h>
#include <random>


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);



INT RN(INT lBorder,INT rBorder);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
    TCHAR szClassName[] = TEXT("Мой класс");
    HWND hMainWnd;
    MSG msg;
    WNDCLASSEX wc;
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    wc.cbWndExtra = NULL;
    wc.cbClsExtra = NULL;
    wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wc.hInstance = hInst;
    if (!RegisterClassEx(&wc)) {

        MessageBox(NULL, TEXT("Не получилось зарегистрировать класс!"), TEXT("Ошибка"), MB_OK);
        return NULL;
    }
    hMainWnd = CreateWindow(szClassName, TEXT("Лабораторая работа 3"), WS_OVERLAPPEDWINDOW | WS_VSCROLL, CW_USEDEFAULT, NULL, CW_USEDEFAULT, NULL, static_cast<HWND>(NULL), NULL, static_cast<HINSTANCE>(hInst), NULL);
    if (!hMainWnd) {

        MessageBox(NULL, TEXT("Не получилось создать окно!"), TEXT("Ошибка"), MB_OK);
        return NULL;
    }
    ShowWindow(hMainWnd, nCmdShow);

    UpdateWindow(hMainWnd);
    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static BOOL time;
    HDC hDC;
    static RECT rect,rect2;
    static RECT rectOld;
    static HPEN hpen1;
    HBRUSH brush;
    switch (msg)
    {
    case WM_CREATE:
        time = FALSE;
        SetTimer(hWnd, 1, 500, NULL);
        break;
    case WM_SIZE:
        GetClientRect(hWnd, &rectOld);
        break;
    case WM_PAINT:
        
            hpen1 = CreatePen(RN(0, 255), RN(1, 5), RGB(RN(0, 255), RN(0, 255), RN(0, 255)));
            hDC = GetDC(hWnd);
            SelectObject(hDC, hpen1);
            GetClientRect(hWnd, &rect);
            
            Rectangle(hDC, rect2.left, rect2.top, rect2.right, rect2.bottom);
            brush = CreateSolidBrush(RGB(RN(0, 255), RN(0, 255), RN(0, 255)));
            FillRect(hDC, &rect2, brush);
            ReleaseDC(hWnd, hDC);
            time = FALSE;
        
        break;
    case WM_TIMER:
    {
        rect2 = RECT{ RN(0,rectOld.right), RN(0,rectOld.bottom), RN(0,rectOld.right), RN(0,rectOld.bottom) };
        InvalidateRect(hWnd, NULL, TRUE);
        RedrawWindow(hWnd, NULL, NULL, RDW_ERASENOW);
        time = TRUE;
        break;
    }
    case WM_DESTROY:
    {
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}



INT RN(INT lBorder,INT rBorder)
{
    std::random_device rd;
    std::uniform_int_distribution<INT> rand(lBorder, rBorder);
    return rand(rd);
}





