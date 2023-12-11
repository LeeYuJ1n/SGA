#include "TestScene.h"

TestScene::TestScene(HWND _hWnd)
{
    //this : "현재 생성된 이 인스턴스의"
    this->hWnd = _hWnd;
    hdc = GetDC(_hWnd);

    text_x = 100;
    text_y = 100;
}

void TestScene::GetInput(WPARAM _wParam)
{
    switch (_wParam)
    {
        //화살표키 입력을 받았다면 어떻게 할 것인가
    case VK_UP:
        //이동을 막는 기본 원리는 이중배열에서의 이동 때와 같습니다.
        //위치가 0보다 클 때만 이동을 허용해주면 됩니다.
        //위치가 0보다 작아질 상황이면 보정을 해주면 됩니다.

        if (textArea.top > 10) //여기서 10 : 이 사각형이 이동했을 때 이동할 간격
        {
            //->아래 코드 : 이동할 간격이 아직 넉넉히 남았을 때
            textArea.top -= 10;
            textArea.bottom -= 10;
        }
        else if (textArea.top > 0 && textArea.top <= 10)
        {
            //이동할 간격이 빡빡할 때 (딱 맞거나, 이동하기에 살짝 모자라거나)
            textArea.top = 0; //탑을 0으로 맞춥니다.
            textArea.bottom = textArea.top + 50; //50 : 헤더에서 지정된 렉트의 아래쪽 경계
            //위처럼 렉트의 top 크기를 미리 기준으로 정해주면 상대적으로 안정된 렉트를 유지할 수 있습니다
        }
        else //0이거나 음수이거나... (웬만하면 안 그러는 게 좋지만 혹시 이런 경우가 발생했다면)
        {
            //현재는 위와 할 행동이 같으므로 코드를 복붙해줍니다.
            //할 행동이 똑같은데 행동을 나눈 이유 : 나중에 "영역을 벗어났을 때" 일어나야 할 행동이 달라질 수도 있으니까
            // 예 : "아무것도 안 하기" =이동불가, 혹은 죽기, 혹은 안 보이게 되기 등등
            textArea.top = 0;
            textArea.bottom = textArea.top + 50;
        }

        
        //text_y -= 10;
        break;

    case VK_DOWN:

        //아래쪽도 위쪽과 원리가 같습니다
        // 사각형의 바닥이... 윈도우를 넘으면 안 된다면
        // 그 윈도우의 바닥은 우리가 어떻게 알죠???
        // -> 윈도우가 만들어질 때, 크기를 정해서 그 위치를 불러오거나,
        // -> 혹은 윈도우가 현재 가진 크기를 구하는 함수를 알아내서 쓰거나,
        // -> 혹은 윈도우의 현재 크기를 구할 매크로를 사전에 정의해서 호출하거나,
        // : 셋 중 한 가지 방법은 써야 됩니다. 또 그렇게 하면 됩니다.

        // * 윈도우 설정에 따라... API에서 지정한 윈도우 크기와 눈에 보이는 윈도우 크기가 다를 수 있습니다.

        if (textArea.bottom < 600 - 10) // 여기서 600 : 수동으로 지정한 윈도우의 세로 크기
        {
            textArea.top += 10;
            textArea.bottom += 10;
        }
        else if (textArea.bottom < 600 && textArea.bottom >= 600 - 10) // 연산에 사용된 10 : 이동 간격
        {
            textArea.bottom = 600; //기준이 되어야 할 텍스트의 바닥을 먼저 정하고
            textArea.top = textArea.bottom - 50; //바닥을 기준으로 해서 위쪽 선분의 위치를 조정
        }
        else
        {
            textArea.bottom = 600; //기준이 되어야 할 텍스트의 바닥을 먼저 정하고
            textArea.top = textArea.bottom - 50; //바닥을 기준으로 해서 위쪽 선분의 위치를 조정
        }
        //text_y += 10;
        break;

    case VK_LEFT:
        //사각형이 움직이려면 어떻게 해야 될까?
        // 1. 이 사각형이 "위치"와 "크기"를 가진 경우라면? -> 위치만 바꾸면 되겠지만
        // 2. 이 사각형이 "왼쪽"과 "오른쪽"을 가진 경우라면? -> 양쪽을 다 바꿔줘야 한다!
        // 현재 API에서 쓰는 직사각형 = 2번

        if (textArea.left > 10)
        {
            textArea.left -= 10;
            textArea.right -= 10;
        }
        else if (textArea.left > 0 && textArea.left <= 10)
        {
            textArea.left = 0;
            textArea.right = textArea.left + 150; // 120 : 렉트의 가로 크기
        }
        else
        {
            textArea.left = 0;
            textArea.right = textArea.left + 150;
        }        
        //text_x -= 10;
        break;

    case VK_RIGHT:

        if (textArea.right < 600 - 10)
        {
            textArea.left += 10;
            textArea.right += 10;
        }
        else if (textArea.right < 600 && textArea.right >= 600 - 10)
        {
            textArea.right = 600;
            textArea.left = textArea.right - 150;
        }
        else
        {
            textArea.right = 600;
            textArea.left = textArea.right - 150;
        }        
        //text_x += 10;
        break;
    }
    //입력에 의한 정보 갱신을 반영하고, 오래된 화면 무효화
    InvalidateRect(hWnd, NULL, true);
}

void TestScene::Render()
{
    //TextOut(hdc, text_x, text_y, L"헬로 월드!", 6);

    //직사각형 (렉탱글)
    //Rectangle(hdc, rect1.left, rect1.top, rect1.right, rect1.bottom);
    //매개변수 : 차례대로 어디에(hdc), 각 꼭지점의 위치
    
    //타원 (일립스)
    //Ellipse(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);

    //직사각형 데이터를 메모장처럼 사용하는 "그려진 문자열"
    //DrawText(hdc, L"안녕하세요!", -1, &rect3, 0);
    //매개변수 : 어디에 (hdc)
    //          문자열 (안녕하세요!)
    //          문자열의 길이 (여기서 -1은 클래스로 관리된 배열의 "현재 최대 크기")
    //          사각형의 데이터 참조내용 (rect3의 위치에 있는 값들!)
    //          마지막의 0 : 서식 설정. 0은 서식 지정이 없다는 뜻

    //과제 확인용 텍스트 출력
    DrawText(hdc, L"움직이는 텍스트", 8, &textArea, DT_CENTER | DT_NOCLIP);
    //마지막 매개변수에서 쓰인 매크로 : 중앙 정렬, 그리고 (영역 안인 한) 문자열 최대한 자르지 않기 (허용 공백 무시)
    //텍스트가 출력됐으니, 이걸 움직이려면? -> 키보드에서 입력받을 때 지금 쓴 렉트를 조작하면 된다!

    // -----------------------------------------------------------------------

    // 8월 10일 알아볼 부분 : 그림에 색을 입히기

    // 윈도우가 화면을 출력하는 방식
    // 윈도우가 그림을 그릴 때는 생각보다 복잡한 구조를 거친다

    // 1. "어디에 그릴 건가?"를 따지고 (hdc 받기)
    // 2. "무엇으로 그릴 건가?"를 따진다
    //    (윈도우는 모니터에 출력을 할 때마다 "출력도구"라는 가상의 객체를 선택한다)
    // 3. 해당 도구를 사용해서 "무엇을 그릴 건가"를 수행하는데...
    // 4. 이 도구는(출력도구) 개발자가 중간에 바꿔줄 수가 있다.

    // 따라서 그림에 색을 입힌다는 것은
    // "어떤 색으로, 어떤 스타일로" 그릴 건지를 먼저 지정을 해주고
    // -> 그 다음에 그림을 그리라고 코드를 짜는 것

    // 윈도우가 winAPI에서 사용하는 그림 도구 (중에서 가장 대중적인 것)

    // HPEN : 선을 그리는 도구 (펜)
    HPEN pen = CreatePen(PS_SOLID, 10, RGB(0, 255, 16));
    //윈도우가 그림을 그릴 때 선택할 수 있도록 새로운 출력도구(펜)를 만든다
    // CreatePen : 새로운 펜 데이터를 만들어내는 함수 (생성자와 같다고 보면 된다)
    // 매개변수로 쓰인 것들
    // PS_SOLID : solid, 실선. dash(점선) 등 스타일도 있다. PS_(펜 스타일) 접두사로 확인 가능
    // 3 : 선의 굵기
    // RGB(n, n, n) : (우리가 아는) 적녹청 색상표. 255, 0, 0은 빨간색 원색이란 뜻

    //도구를 만든 다음, 다른 곳에 미리 백업을 해둔다 (이유는 조금 뒤에)
    //HGDIOBJ : 펜, 혹은 다른 출력 도구 등을 포함하는 전체 오브젝트
    HGDIOBJ oldPen = SelectObject(hdc, pen);
    //SelectObject : 새로운 도구를 윈도우에게 배정함과 동시에, 원래 있었던 도구를 반환받는다
    //               -> 백업과 동시에 새 출력도구가 선택까지 끝난 상황

    //----------------------------------------------------

    //펜과 더불어, 도형에 색을 입히는 출력도구
    // "브러시" : 그림판의 페인트와 유사

    HBRUSH brush = CreateSolidBrush(RGB(255, 255, 0));
    //CreateSolidBrush : 색을 단색으로 빈틈없이(solid) 채우는 브러시를 생성하는 함수
    //                   매개변수 : RGB

    //HBRUSH brush = CreateHatchBrush(HS_CROSS, RGB(1, 1, 1));
    //CreateHatchBrush : (윈도우 과거 기본 스타일이 지정된) 양식화 색칠 브러시를 생성하는 함수
    //                   매개변수 : 서식 지정 변수 (int, 매크로 일부 있음) + RGB

    HGDIOBJ oldBrush = SelectObject(hdc, brush); //선택 및 백업

    //----------------------------------------------------
    //도구 생성, 기존 도구 백업, 그 다음에 그림을 그리면 된다
    // 준비 기간이 너무 길어서 귀찮을 수도 있지만....

    //텍스트 영역을 (재)사용한 직사각형 출력
    Rectangle(hdc, textArea.left, textArea.top, textArea.right, textArea.bottom);

    //같은 출력도구를 써서 그림을 다른 곳에 또 그린다면??
    Ellipse(hdc, 100, 100, 300, 300);

    //또 그린다면??
    Rectangle(hdc, 300, 100, 400, 200);

    // 한 번 선택된 출력도구로 계속 그림을 그려나갈 수 있다
    // 출력도구가 바뀌기 전에는 모든 그림이 같은 속성을 부여받는다
    // -> 컴퓨터 입장에서는 많은 그림을 그릴수록 더 이런 방식이 효율적이다!

    // 그림을 다 그리고 나면 그 다음에 해줘야 하는 것
    // -> 펜 삭제 (그림을 그리는 과정에서 그림 도구 데이터가 계속 생성되기 때문에)
    // -> 가장 좋은 것 : 펜을 다 쓰면 바로 지우는 것

    //아까 백업해둔 기존의 출력도구를 윈도우에게 다시 돌려주자
    SelectObject(hdc, oldPen); //아까 백업된 기본 출력도구 반환.
    // "백업"을 하려는 게 아니기 때문에 다른 곳에 반환을 저장할 필요 없음

    //delete pen;// <-펜 삭제....를 위한 가장 단순한 방법 (C++ 방식)
    
    //winAPI에서는 기본적으로도 winAPI 내에서 쓰이는 데이터들을 지우기 위한
    //더 좋은 함수들을 기본적으로 부분 제공

    DeleteObject(pen); //<-출력도구를 지우기 위한 더 좋은 함수
    //처음에 만든 출력도구 pen을 지우자 (포인터라서 최초 메모리가 지워지면 다 자유)

    //브러시 복구와 삭제
    SelectObject(hdc, oldBrush);
    DeleteObject(brush);

    //요약 : winAPI에서 그림을 그리는 과정
    // 1. 출력도구 생성
    // 2. 출력도구 선택 (겸 백업)
    // 3. ** 그리기 ** (본론)
    // 4. 출력도구 원래대로 되돌리기
    // 5. 만든 출력도구 삭제

    //---------------------------------------------

    // 출력 도구를 써서 서식 있는 그림을 그리고....
    
    // 그 다음에 출력 도구를 바꿔서 더 그리면?

    HPEN pen2 = CreatePen(PS_SOLID, 10, RGB(0, 255, 255));
    HGDIOBJ oldPen2 = SelectObject(hdc, pen2);

    Ellipse(hdc, 400, 400, 500, 500);

    SelectObject(hdc, oldPen2);
    DeleteObject(pen2);

    //----------------------------------------------

    // 사각형, 타원에 이어서 윈API에서 사용할 수 있는 다른 그림 함수

    // (사실) 생각보다 좀 더 많은 그림 표현 방법이 있는데.....
    // 그 중에서 실제로 자주 쓰이는 부분은 (사각, 타원 빼고) 두셋 정도

    // 다시 그 중에서, 오늘 배워볼 부분 : 자유 직선

    // 윈 API에서 자유 직선의 원리

    // 1. 윈API의 (가상 출력 도구의) 현재 위치를 새로 지정해준다 (거기가 직선의 시작)
    // 2. 해당 시작 지점을 염두에 두고, 어디까지 직선이 가야 할지를 코드로 지정해준다

    // 작성 사례

    MoveToEx(hdc, 100, 200, NULL);
    // MoveToEx : (가상 도구의 좌표를) 목적 좌표(Ex)까지 움직이는(Move to) 함수
    // 매개변수 : hdc = "이 윈도우에서"
    //           100, 200 = x, y 좌표 위치
    //           0 혹은 NULL = "원래 좌표가 어디였는지"를 나타내는 거지만...
    //           굳이 알 필요가 없어서 0으로 지정한 것

    //위 함수가 실행되면 윈도우의 출력 도구의 좌표가 100, 200으로 바뀐다
    
    // 코드로 다른 좌표를 지정해주면, 위에서 지정된 100, 200 위치에서 새 목적지로
    // 도구가 가면서 직선을 그려주는 것

    LineTo(hdc, 300, 300);
    //LineTo : (현재 지정된 좌표에서) 지정된 새 좌표로 이동하면서 직선을 그리는(남기는) 함수
    //         hdc = "이 윈도우에서"
    //         300, 300 = x, y 좌표 위치

    // 여기서 중요한 것 : 직선을 그림과 동시에 출력 도구의 좌표도 새로 지정된 곳으로 갔다!
    // 그래서 LineTo를 계속해서 반복하면 끊기지 않는(대신에 꺾이는) 직선을 그리는 것이 가능

    LineTo(hdc, 400, 300);

    LineTo(hdc, 400, 200);

    LineTo(hdc, 100, 200);

    // 직선 그리기에도 펜 도구 적용이 가능 (색깔 있는 선 그리기)

    HPEN pen3 = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
    HGDIOBJ oldPen3 = SelectObject(hdc, pen3);

    LineTo(hdc, 100, 400);

    SelectObject(hdc, oldPen3);
    DeleteObject(pen3);
}

void TestScene::Update()
{

}