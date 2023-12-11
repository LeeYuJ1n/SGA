// 수업파일(WinAPI).cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

// 경우에 따라서는 개발자가 직접 헤더 관리용 최상위 헤더를 정의할 때도 있습니다
#include "stdafx.h" // ← 대중적으로 매우 자주 선택되는 최상위 헤더의 명칭 (표준 접두정의 헤더)

// 자동완성으로 API 앱을 만들 경우 아래에 프레임워크 헤더가 만들어져서 추가됩니다
// 호환성이나 범용성을 중시하는 개발에서는 stdafx 대신 아래 프레임워크 헤더에 각 기능을 바로 추가히기도 합니다
// 여기서는 편의상 프레임워크 헤더를 이용하도록 하겠습니다
#include "framework.h"         // 우리가 만든 헤더는 여기서 등록!
#include "수업파일(WinAPI).h"

#define MAX_LOADSTRING 100
#define TITLE L"도화가"

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, TITLE, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 600, 600, nullptr, nullptr, hInstance, nullptr);
      // CW_USEDEFAULT : 윈도우 크기 

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// 시간을 담을 변수
SYSTEMTIME systemTime;

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: // 윈도우가 만들어 질 때
        // 만들어질 때 한 번, 게임 매니저를 초기화
        GameManager::Get()->Init(hWnd);

        SetTimer(hWnd, 0, 1000, NULL);
        // SetTimer : 윈도우에 내장된 타이머 기능을 앱에서 작동시키는 함수
        //            매개변수 : hWnd = 이 윈도우
        //            0 : 어떤 이벤트와 연동할 것인가? - 0은 그냥 실행한다
        //               = 어떤 절차에서, 혹은 어떤 포트에서 이 타이머를 돌리려는가?
        //               = 다른 말로, "이 타이머의 ID는 뭐냐? (타이머의 수, 혹은 이 앱의 사전 연결된 이벤트가 여러 개일 때 의미)
        //                  → 이 앱에서 "0번 타이머"라고 부르면 지금 세팅된 타이머가 불려온다
        //            1000 : 타이머가 얼마마다 작동할 것인가? = 작동 간격
        //                 단위는 밀리초 (1000분의 1초), 1000 = 1초마다 타이머 작동
        //            NULL : 어떤 이벤트를 호출할 것인가? (함수 포인터로 호출할 함수 연동 가능)
        //                   단, 안 적어도 괜찮다. 안 적었을 경우 (값을 0으로 줄 경우)
        //                   이 윈도우 앱에 WM_TIMER라는 메시지를 전달한다 (기본 내장 호출 이벤트가 있는 것)

        break;

    case WM_TIMER:
        // 시간이 지날 때마다 앱 업데이트 
        // 업데이트를 어떻게 호출할까? 원칙적으론 개발자 마음이지만
        // 이번 경우에는 만들어진 함수가 하나 있다
        GameManager::Get()->Update(); // 업데이트 함수를 여기서 사용!
        break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 윈도우가 시각적으로 갱신될 때
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            GameManager::Get()->Render();

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_KEYDOWN: // 키를 눌렀을 때

        // 바로 게임매니저에 입력을 전달
        GameManager::Get()->GetInput(wParam);

        // 위 코드로 게임매니저 초기화 / 입력 / 출력  / 갱신 중 3개를 불러왔습니다
        // 갱신은 현재 딱히 부를 곳이 없어서 아직 안 부릅니다
    break;

    case WM_MOUSEMOVE: // 마우스를 움직였을 때
        // 바로 게임매니저에 (마우슬 받은) 좌표를 전달
        GameManager::Get()->GetPoint(lParam);
        break;

    case WM_DESTROY:
        // 타이머를 만들면, 윈도우가 끝날 때도 타이머를 해제해주면 좋다
        KillTimer(hWnd, 0);
        // KillTimer : 세팅했던 타이머를 해제하는 함수
        //             매개변수 : hWnd = 이 윈도우
        //                       0 : = 타이머에 연도했던 사전 이벤트, 혹은 "타이머의 ID"
        //                       → 여기 있는 ID와 위에 만들 때 ID는 같아야 한다

        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
