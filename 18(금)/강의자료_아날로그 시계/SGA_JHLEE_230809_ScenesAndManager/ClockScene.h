#pragma once
#include <Windows.h>
#include <math.h>
#include <string>

#define PHI 3.1415926f

class ClockScene
{
    //시계!

public:
    ClockScene(HWND _hWnd);
    void GetInput(WPARAM _wParam); // 입력 받기
    void GetPoint(LPARAM _lParam); // "포인트" 받기
    // 위 함수는 이번에 쓰지 않지만, 로딩을 위해 작성 (사실상의 인터페이스)
    void Render();
    void Update();

private:

    //입력 (쓰진 않을 거지만...)
    WPARAM wParam;
    LPARAM lParam;

    //출력
    HWND hWnd;
    HDC hdc;

    //시간 데이터
    SYSTEMTIME systemTime;
    std::wstring timeText = L""; //시간 표시용 텍스트
    std::wstring dateText = L""; //(옵션) 날짜용

    //시계에 넣을 글자들
    // 12, 3, 6, 9만 먼저 일단 만들었다 (간단하게)
    std::wstring cha12 = L"12";
    std::wstring cha3 = L"3";
    std::wstring cha6 = L"6";
    std::wstring cha9 = L"9";

    //시계 텍스트 넣을 사각형 데이터
    RECT rect12;
    RECT rect3;
    RECT rect6;
    RECT rect9;

    RECT timeRect; // 시간 텍스트 표시용
    RECT dateRect; // 날짜 텍스트 표시용

    //시계 그림용 데이터
    long charDistance = 200; // 원점에서 글자까지의 크기, 시계의 크기
    float lengthHour = 120;   // 시침 길이
    float lengthMinute = 180; // 분침 길이
    float lengthSecond = 150; // 초침 길이

    //x, y. 지점지정에 사용하기 위함
    float x;
    float y;

    //각도. 지점지정에 사용하기 위함
    float angle;

    //"원점"이라는 이름의 지점(구조체) : 시계의 중심, 혹은 위치
    // (그리기용 좌표도 구조체로 만들어도 되는데...
    //  나중에 귀찮을 것 같아서)
    POINT origin; //location point


    //작은 함수들 (cpp에 적는 게 좋지만 강의 편의상 헤더에)

    // 호도 구하기 (각도를 넣으면 컴퓨터를 위한 호도가 나옵니다)
    float GetRadian(float degree)
    {
        return ((PHI / 180) * degree);

        // * 이 각도를 통해서 그림을 그리면 (작도하면)
        //   1. 기준선의 문제 : 수평이다 (시계는 12시 방향이 기준선인데)
        //   2. 방향의 문제 : 삼각함수 작도는 기본이 "반"시계방향

        // → 이 문제를 하나는 가도 조정으로, 다른 하나는 삼각함수 적용의 변화로 해결
    }

    // 기준선의 문제 (각도 문제) 해결용
    // 수평선이던 기준을 수직선으로 바꾸기
    float GetClockAngle(float angle)
    {
        //1호도 = 반지름(...의 길이만큼의 호 길이)
        //1호도 * PHI = 반원 = 180도
        //PHI / 2 = 수직!  (1은 생략됨)

        return angle += PHI / 2; // <- 기준 각도를 90도 더합시다
    }

    std::wstring Get12HourText(WORD hour)
    {
        std::wstring result = L"";
        if (hour >= 0 && hour < 24) //값이 적절할 경우
        {
            if (hour < 12) result = L"오전 " + std::to_wstring(hour);
            else if (hour == 12) result = L"오후 " + std::to_wstring(hour);
            else result = L"오후 " + std::to_wstring(hour - 12);
        }
        return result;
    }

    std::wstring DayofWeek(WORD day)
        // (옵션) 요일 표시용
    {
        std::wstring result = L"";

        switch (day)
        {
        case 0: result = L"일요일"; break;
        case 1: result = L"월요일"; break;
        case 2: result = L"화요일"; break;
        case 3: result = L"수요일"; break;
        case 4: result = L"목요일"; break;
        case 5: result = L"금요일"; break;
        case 6: result = L"토요일"; break;
        }
        return result;
    }


    //-----------------------------------------------------------

    // 옵션 함수, 더 부드러운 시계 움직임을 만들고 싶다면
    
    void GetAngleForHour(); //자주 보는 아날로그 시계 같은 시침 움직임
    void GetAngleForMintue(); //자주 보는 아날로그 시계 같은 분침 움직임

    void GetAngleForHourSmooth(); //가끔 보는 부드러운 시계 같은 시침 움직임
    void GetAngleForMinuteSmooth(); //가끔 보는 부드러운 시계 같은 분침 움직임
    void GetAngleForSecondSmooth(); //가끔 보는 부드러운 시계 같은 초침 움직임


    //글자 다 있는 시계를 만들고 싶다면

    std::wstring cha1 = L"1";
    std::wstring cha2 = L"2";
    std::wstring cha4 = L"4";
    std::wstring cha5 = L"5";
    std::wstring cha7 = L"7";
    std::wstring cha8 = L"8";
    std::wstring cha10 = L"10";
    std::wstring cha11 = L"11";

    RECT rect1;
    RECT rect2;
    RECT rect4;
    RECT rect5;
    RECT rect7;
    RECT rect8;
    RECT rect10;
    RECT rect11;

    void ReadyFullHour() //강의 편의상 여기서 바로 작성합니다.
    {
        //생성자에서 호출할 함수

        //위치 지점 (기준용)
        POINT loc;
        
        //1시 = 30도를 대입해서 호도를 구하고,
        //해당 호도에 맞추어 기준 위치를 구합니다.
        //단, 시계 방향, 시계 각도를 기준으로.

        float locAngle = GetClockAngle(GetRadian(30));
        loc.x = origin.x + (-cos(locAngle)) * charDistance;
        loc.y = origin.y + (-sin(locAngle)) * charDistance;
        rect1 = { loc.x - 10, loc.y - 10, loc.x + 10, loc.y + 10 };
        
        // 이걸 2시(60도), 4시(120도)....등에 모두 대입합니다.

        locAngle = GetClockAngle(GetRadian(60));
        loc.x = origin.x + (-cos(locAngle)) * charDistance;
        loc.y = origin.y + (-sin(locAngle)) * charDistance;
        rect2 = { loc.x - 10, loc.y - 10, loc.x + 10, loc.y + 10 };

        locAngle = GetClockAngle(GetRadian(120));
        loc.x = origin.x + (-cos(locAngle)) * charDistance;
        loc.y = origin.y + (-sin(locAngle)) * charDistance;
        rect4 = { loc.x - 10, loc.y - 10, loc.x + 10, loc.y + 10 };

        locAngle = GetClockAngle(GetRadian(150));
        loc.x = origin.x + (-cos(locAngle)) * charDistance;
        loc.y = origin.y + (-sin(locAngle)) * charDistance;
        rect5 = { loc.x - 10, loc.y - 10, loc.x + 10, loc.y + 10 };

        locAngle = GetClockAngle(GetRadian(210));
        loc.x = origin.x + (-cos(locAngle)) * charDistance;
        loc.y = origin.y + (-sin(locAngle)) * charDistance;
        rect7 = { loc.x - 10, loc.y - 10, loc.x + 10, loc.y + 10 };

        locAngle = GetClockAngle(GetRadian(240));
        loc.x = origin.x + (-cos(locAngle)) * charDistance;
        loc.y = origin.y + (-sin(locAngle)) * charDistance;
        rect8 = { loc.x - 10, loc.y - 10, loc.x + 10, loc.y + 10 };

        locAngle = GetClockAngle(GetRadian(300));
        loc.x = origin.x + (-cos(locAngle)) * charDistance;
        loc.y = origin.y + (-sin(locAngle)) * charDistance;
        rect10 = { loc.x - 10, loc.y - 10, loc.x + 10, loc.y + 10 };

        locAngle = GetClockAngle(GetRadian(330));
        loc.x = origin.x + (-cos(locAngle)) * charDistance;
        loc.y = origin.y + (-sin(locAngle)) * charDistance;
        rect11 = { loc.x - 10, loc.y - 10, loc.x + 10, loc.y + 10 };
    }

    void RenderFullHour()
    {
        //렌더에서 호출할 함수

        //준비한 글자를 각 렉트에서 렌더
        DrawText(hdc, cha1.c_str(), -1, &rect1, DT_NOCLIP);
        DrawText(hdc, cha2.c_str(), -1, &rect2, DT_NOCLIP);
        DrawText(hdc, cha4.c_str(), -1, &rect4, DT_NOCLIP);
        DrawText(hdc, cha5.c_str(), -1, &rect5, DT_NOCLIP);
        DrawText(hdc, cha7.c_str(), -1, &rect7, DT_NOCLIP);
        DrawText(hdc, cha8.c_str(), -1, &rect8, DT_NOCLIP);
        DrawText(hdc, cha10.c_str(), -1, &rect10, DT_NOCLIP);
        DrawText(hdc, cha11.c_str(), -1, &rect11, DT_NOCLIP);
    }
};
