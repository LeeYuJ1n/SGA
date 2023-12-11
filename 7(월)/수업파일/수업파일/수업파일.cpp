// 수업파일.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "수업파일.h"

#include <stdlib.h>

#define MAX_LOADSTRING 100

// 진짜 윈도우 제목
#define WINTITLE L"진짜 제목"

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING] = WINTITLE;                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
// 위 함수의 이름 : 윈도우 프로시저 (윈도우 진행 절차 정의)
//                 혹은 "윈도우에서 돌아가는 무한반복문"
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
// 별도로 추가 메시지가 들어오면 처리해주는 대기형 함수

// 아래는 윈도우용 메인함수
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    srand(GetTickCount64());

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    // 위 함수 : 앱 실행 시에 커맨드라인으로 뭔가 입력을 했을 경우
    //           해당 커맨드라인을 앱에서 볼 수 있는 형태로 만들어주는 것

    // 커맨드라인 : 앱 실행 시에 파일 이름 뒤에 붙여서 앱 실행의 조건을 제한해주는 추가 명령어
    //             (예 : -w, /p 같은 추가 키워드)

    // TODO: 여기에 코드를 입력합니다. ( + 커맨드라인이 있을 경우 처리해줘야 하니까)

    // 아래로는 윈도우를 만들고 실제 앱을 실행하는 과정

    // 전역 문자열을 초기화합니다.
    // 만들어진 전역변수를 재가공해서 앱에서 쓰도록 준비
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance); // 재가공된 문자열을 사용해서 클래스를 인스턴스로 만들고 등록( = 준비)

    // 애플리케이션 초기화를 수행합니다: ( = 윈도우를 만든다)
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

    MSG msg; // 윈도우 메시지 구조체 (혹은 클래스) : 사용자가 윈도우에 입력한 내용들을 코드화한 것

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0)) // 위 메시지가 틀리지 않은 한 ("오류"가 입력되지 않는 한 = 입력이 옮바르거나, 없거나 하는 한)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg); // 컴퓨터가 알 수 있게 메시지를 재번역
            DispatchMessage(&msg); // 그 메시지를 앱의 메모리에 전달
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//  정확히는 창의 스타일을 지정
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW; // 출력방식
    wcex.lpfnWndProc    = WndProc; // 실행할 대기형 함수 (콜백) 등록
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1); // 배경을 "그릴"경우 (연산으로 출력할 경우) 무엇으로 출력할 것인가
                                                    // HBRUSH + 숫자 : 배경색 지정, 다른 코드를 통해서 배경을 지정할 수도(다음 기회에)
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // 등록된 윈도우의 인스턴스 데이터 ( = 스타일 지정)를 컴퓨터에 반환
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, // 세 번째 변수 : 윈도우의 스타일 (나중에 다시 알아볼 것)
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
      // 바로 윗줄 매개변수 왼쪽부터 4개
      // : 각각 왼쪽에서의 위치, 오른쪽에서의 위치
      // 그리고 윈도우의 가로 크기, 윈도우의 세로 크기
      // 왼쪽 위치와 가로 크기가 CW_USEDEFAULT인 경우 운영체제에 맞는 기본 스타일로 나온다
      // 그렇지 않으면, 각 숫자 4개에 지정된 위치와 크기에 따라 윈도우가 출력

      // szTitle 자리에 다른 텍스트를 넣으면? 윈도우 제목을 바꿀 수 있다
      // * 텍스트를 곧 바로 넣으면 에러 : 윈API에서는 각 운영체제에 맞는, 혹은 코드로 지정된 문자 코드를 쓰기 때문
      //   그래서 해당 문자 코드를 이용한 문자열이라는 뜻의 L( = locale)을 문자열 앞에 더해주면 된다

      // szTitle의 값을 그러면 바로 바꾸면 어떨까? 제목이 안 바뀐다
      // 이유 : 전역변수에 초기화 할당한 값을 winMain에서 또 초기화하기 때문에
      // 윈도우 제목 바꾸는 방법 : szTitle의 값을 바꾸기 보다... define을 쓰는 편이 편하다
      // (define으로 진짜 제목을 설정해주고 szTitle 자리에 대신 넣기)

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

int randX, randY;

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
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT: // 닫기 버튼을 누르거나, 다른 식으로 실행하면 연산되는 메시지
                           // 뜻은 "앱 종료"
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 화면 출력
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            // 예시 : 텍스트 출력 ( * 윈API는 글자도 "글자 모양으로 한 그림"이라고 이해하면 편하다)
            TextOut(hdc, randX, randY, L"헬로, 월드!", 7);
            // TextOut : 대중적으로 쓰이는 문자열 출력 함수
            // 매개변수, 차례로 hdc부터
            //hdc : 윗줄에서 변수로 지정된 "디바이스 컨텍스트," DC
            // * 디바이스 컨텍스트 : 출력 기계에 구애받지 않고 데이터를 출력하기 위해서 지정된 데이터 관리용 구조체
            // → 현재 앱이 실행된 환경이 뭐든, 거기에서 TextOut을 연산하겠다는 뜻
            // 두 번째, 세 번째 정수 매개변수 : 문자열의 위치 (윈쪽 위부터의 x값, y값)
            // 네 번째 문자열 매개변수 : 출력할 진짜 문자열
            // 다섯 번째 정수 매개변수 : 방금 받은 문자열의 어디까지 출력할 것인가 (문자열의 크기)
            // * 문자열 크기는 문자코드 전체 ( = 글자 찐 하나)를 1로 친다

            // → 이런 식으로, 여기에서 우리가 코드를 입력하면 앱에서 어떤 화면이든 출력할 수 있다
            //   다만... 실제로는 여기에서 코드를 정말로 작성하는 경우는 거의 없을 것
            //   1. 코드를 여기서 작성하면 너무 어수선하다 (찾아오기도 귀찮다)
            //   2. 윈도우 프로그램은 규모도 큰데 여기서 화면 출력을 모조리 작성하면 꼬이기도 쉽다 (위험하다)

            // 실제로는 어떻게?
            // (다른 클래스에서 출력 함수를 미리 다 만들어놓고) 여기서는 출력 호출만

            // 예 : instance->Render();

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_INPUT: // 입력 처리
        // 여기에서 입력의 결과를 처리 (연산 부분을)
        // → 화면의 출력은? 위의 화면이 달라질 수 있도록 연산만 바꾸게 될 것
        // → 그러면 WM_PAINT에서 화면 출력이 그 결과를 반영해줄 것
        // 입력을 별도 메시지로 처리할 수도 있고, WM_COMMAND의 일부에서 처리하는 것도 가능

        // → 결과적으론, 입력도 여기에서 코드를 일일이 작성하는 경우는 드물 것
        // → 다른 클래세에서 입력을 받는 함수를 만들고, WndProc에서 호출만 할 것
        // 예 : instance->ManageInput();

        break;

    case WM_KEYDOWN: // 입력처리의 다른 방법 ("키를 눌렀을 때"라는 구체적인 경우)
        if (wParam == VK_SPACE) // wParam : 윈도우 메시지 구성요소 중 하나, "무엇을"에 해당하는 데이터를 코드화한 것
        // 스페이스를 누른 경우 (VK : 가상 키보드, 하드웨어 및 문자코드에 무관하게 "스페이스바")
        {
            // 전역변수 설정 및 winMain 맨 앞에 srand 호출 있음
            randX = rand() % 200;
            randY = rand() % 100;
        }
        else if (wParam == VK_UP)
        {
            randY--;
        }
        else if (wParam == VK_DOWN)
        {
            randY++;
        }
        else if (wParam == VK_LEFT)
        {
            randX--;
        }
        else if (wParam == VK_RIGHT)
        {
            randX++;
        }

        // 아래 코드 : 화면에 갱신 상황이 생길 경우, 이전의 화면 데이터를 지워달라는 코드
        // → 기존 화면 (기존 직사각형 영역) 무효화 함수 *Rect : rectangle(직사각형)의 약자
        InvalidateRect(hWnd, NULL, true);

        break;

    case WM_DESTROY: // EXIT와 같이 윈도우 종료
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
// → 창 입력이나 다른 앱을 통해서 추가로 받는 메시지가 있으면 처리
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
