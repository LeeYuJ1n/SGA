#include "TimeAndCoord.h"
#include <math.h>

TimeAndCoord::TimeAndCoord(HWND _hWnd)
{
    this->hWnd = _hWnd; // 출력할 윈도우(앱)
    hdc = GetDC(_hWnd); // 출력할 장소(하드웨어)

    number = 0;
}

void TimeAndCoord::GetInput(WPARAM _wParam)
{

}

void TimeAndCoord::GetPoint(LPARAM _lParam)
{
    //게임매니저를 통해서 윈도우의 l-매개변수 (=long, 긴 형태의 매개변수 메시지) 받자

    //좌표
    pointX = (float)LOWORD(_lParam);
    pointY = (float)HIWORD(_lParam);

    // 위 코드의 의미 : lParam은 윈도우에서 각 메시지가 발생했을 때
    //                 매개변수를 처리하는 "큰 용량" 담당 데이터를 총칭 (long)
    //                 마우스 입력에도 이 매개변수가 쓰이는데, 마우스가 어디에 있는지
    //                 드래그를 했으면 드래그가 지금 어떤 모양인지 등을 안에 담는다
    //                 (반대로 "작은 용량" 즉 키 입력, 마우스 1회 클릭 등은 wParam) (w는 word)

    // 마우스 입력을 받을 때는 다시 이렇게 받은 "롱" 패러미터를 분석해서
    // 앞부분("낮은 자리")을 x로, 뒷부분을 y로 이해한다
    // 그런데 WORD의 진짜 자료형이 int이므로 계산 중에 오차를 줄이려고 float으로 형변환

    //이 포인트를 써서 좌표출력을 해봅시다

    //텍스트를 처음부터 조립을 하려니 string 자료형이 자유롭지 않으면 제약이 있다
    // -> 그냥 곧바로 변수를 통짜 복사


    //******************************************************
    //lstrcpy(lstr, TEXT("X : %f, Y : %f", pointX, pointY));
    // lstrcpy : c++ 및 c에서 사용했던 문자열 복사 함수의 확장. 2 혹은 3바이트 문자코드에 대응하기 위함
    // TEXT : char 혹은 wchar 문자열을 현 프로젝트에 맞는 문자코드 문자열로 바꿔주는 매크로
    // %f : (%d, %s 등과 마찬가지로) 여기에 실제 데이터를 대입한다는 의미의 서식문자. f는 소수

    //lstrcpy는 c의 str 함수나 printf와 달리, 서식문자에 의한 변수 반영이 되지 않는다고 합니다. 참고합시다...ㅠ
    //******************************************************

    //대신 스트링 자료형을 사용해서 그냥 C++의 확장된 문자열 기능을 적극 사용하도록 하겠습니다.

    logCoord = L"X좌표 : " + std::to_wstring(pointX) + L", Y좌표 : " + std::to_wstring(pointY);
    //std::to_wstring(매개변수) : 매개변수를 문자열로 바꿔주는, 스트링 클래스 내의 문자열.
    // 문자코드가 적용된 서식 가능한 문자열로 바꾸려고 wstring으로 바꾸도록 했습니다.


    //클릭한 곳이 중심인 사각형 설정
    rect2.left = pointX - 10;
    rect2.right = pointX + 10;
    rect2.top = pointY - 10;
    rect2.bottom = pointY + 10;


    //출력할 데이터가 만들어졌으니 화면 무효화 (새로 고침)
    InvalidateRect(hWnd, NULL, true);
}

void TimeAndCoord::Render()
{
    //그릴 데이터가 있으니 그릴 차례
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    DrawText(hdc, logCoord.c_str(), -1, &rect, 0);
    //스트링 자료형 변수 + c_str() 함수 = 스트링 자료형을 문자코드에 의한 문자열(wchar, chat_t)로 바꿔줍니다.

    //클릭한 곳이 중심인 사각형 출력
    Rectangle(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);

    //1초마다 갱신된 숫자
    DrawText(hdc, logTime.c_str(), -1, &rect3, 0);


    //1초마다 갱신되는 직선 그리기
    x0 = 300;
    y0 = 300;

    x2 = x0 + (cos(GetRadian(st.wSecond * 6)) * 50);
    y2 = y0 + (-sin(GetRadian(st.wSecond * 6)) * 50);

    MoveToEx(hdc, x0, y0, NULL);
    LineTo(hdc, x2, y2);
}

void TimeAndCoord::Update()
{
    // 1초마다 여기서 업데이트 함수 실행
    number++;
    
    GetLocalTime(&st); // 현재시간을 불러와서 변수에 저장을 해준다
    //이 구조체에서 볼 수 있는 자료
    st.wYear; // 해
    st.wMonth; // 달
    st.wDay; // 날짜
    st.wHour; // 시간
    st.wMinute; // 분
    st.wSecond; // 초
    // 위 자료를 WORD, 즉 int로 확인 가능

    //문자열 (스트링) 정리
    logTime = std::to_wstring(st.wYear) + L"년 "
        + std::to_wstring(st.wMonth) + L"월 "
        + std::to_wstring(st.wDay) + L"일 "
        + std::to_wstring(st.wHour) + L"시 "
        + std::to_wstring(st.wMinute) + L"분 "
        + std::to_wstring(st.wSecond) + L"초"
        + std::to_wstring(st.wMilliseconds) + L"밀리초";


    //렌더는 위 함수에서

    //여기서도 화면 무효화
    InvalidateRect(hWnd, NULL, true);
}