#pragma once
#include <Windows.h>
#include <math.h>
#include <string>

#define PHI 3.1415926f

class ClockScene
{
    //�ð�!

public:
    ClockScene(HWND _hWnd);
    void GetInput(WPARAM _wParam); // �Է� �ޱ�
    void GetPoint(LPARAM _lParam); // "����Ʈ" �ޱ�
    // �� �Լ��� �̹��� ���� ������, �ε��� ���� �ۼ� (��ǻ��� �������̽�)
    void Render();
    void Update();

private:

    //�Է� (���� ���� ������...)
    WPARAM wParam;
    LPARAM lParam;

    //���
    HWND hWnd;
    HDC hdc;

    //�ð� ������
    SYSTEMTIME systemTime;
    std::wstring timeText = L""; //�ð� ǥ�ÿ� �ؽ�Ʈ
    std::wstring dateText = L""; //(�ɼ�) ��¥��

    //�ð迡 ���� ���ڵ�
    // 12, 3, 6, 9�� ���� �ϴ� ������� (�����ϰ�)
    std::wstring cha12 = L"12";
    std::wstring cha3 = L"3";
    std::wstring cha6 = L"6";
    std::wstring cha9 = L"9";

    //�ð� �ؽ�Ʈ ���� �簢�� ������
    RECT rect12;
    RECT rect3;
    RECT rect6;
    RECT rect9;

    RECT timeRect; // �ð� �ؽ�Ʈ ǥ�ÿ�
    RECT dateRect; // ��¥ �ؽ�Ʈ ǥ�ÿ�

    //�ð� �׸��� ������
    long charDistance = 200; // �������� ���ڱ����� ũ��, �ð��� ũ��
    float lengthHour = 120;   // ��ħ ����
    float lengthMinute = 180; // ��ħ ����
    float lengthSecond = 150; // ��ħ ����

    //x, y. ���������� ����ϱ� ����
    float x;
    float y;

    //����. ���������� ����ϱ� ����
    float angle;

    //"����"�̶�� �̸��� ����(����ü) : �ð��� �߽�, Ȥ�� ��ġ
    // (�׸���� ��ǥ�� ����ü�� ���� �Ǵµ�...
    //  ���߿� ������ �� ���Ƽ�)
    POINT origin; //location point


    //���� �Լ��� (cpp�� ���� �� ������ ���� ���ǻ� �����)

    // ȣ�� ���ϱ� (������ ������ ��ǻ�͸� ���� ȣ���� ���ɴϴ�)
    float GetRadian(float degree)
    {
        return ((PHI / 180) * degree);

        // * �� ������ ���ؼ� �׸��� �׸��� (�۵��ϸ�)
        //   1. ���ؼ��� ���� : �����̴� (�ð�� 12�� ������ ���ؼ��ε�)
        //   2. ������ ���� : �ﰢ�Լ� �۵��� �⺻�� "��"�ð����

        // �� �� ������ �ϳ��� ���� ��������, �ٸ� �ϳ��� �ﰢ�Լ� ������ ��ȭ�� �ذ�
    }

    // ���ؼ��� ���� (���� ����) �ذ��
    // �����̴� ������ ���������� �ٲٱ�
    float GetClockAngle(float angle)
    {
        //1ȣ�� = ������(...�� ���̸�ŭ�� ȣ ����)
        //1ȣ�� * PHI = �ݿ� = 180��
        //PHI / 2 = ����!  (1�� ������)

        return angle += PHI / 2; // <- ���� ������ 90�� ���սô�
    }

    std::wstring Get12HourText(WORD hour)
    {
        std::wstring result = L"";
        if (hour >= 0 && hour < 24) //���� ������ ���
        {
            if (hour < 12) result = L"���� " + std::to_wstring(hour);
            else if (hour == 12) result = L"���� " + std::to_wstring(hour);
            else result = L"���� " + std::to_wstring(hour - 12);
        }
        return result;
    }

    std::wstring DayofWeek(WORD day)
        // (�ɼ�) ���� ǥ�ÿ�
    {
        std::wstring result = L"";

        switch (day)
        {
        case 0: result = L"�Ͽ���"; break;
        case 1: result = L"������"; break;
        case 2: result = L"ȭ����"; break;
        case 3: result = L"������"; break;
        case 4: result = L"�����"; break;
        case 5: result = L"�ݿ���"; break;
        case 6: result = L"�����"; break;
        }
        return result;
    }


    //-----------------------------------------------------------

    // �ɼ� �Լ�, �� �ε巯�� �ð� �������� ����� �ʹٸ�
    
    void GetAngleForHour(); //���� ���� �Ƴ��α� �ð� ���� ��ħ ������
    void GetAngleForMintue(); //���� ���� �Ƴ��α� �ð� ���� ��ħ ������

    void GetAngleForHourSmooth(); //���� ���� �ε巯�� �ð� ���� ��ħ ������
    void GetAngleForMinuteSmooth(); //���� ���� �ε巯�� �ð� ���� ��ħ ������
    void GetAngleForSecondSmooth(); //���� ���� �ε巯�� �ð� ���� ��ħ ������


    //���� �� �ִ� �ð踦 ����� �ʹٸ�

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

    void ReadyFullHour() //���� ���ǻ� ���⼭ �ٷ� �ۼ��մϴ�.
    {
        //�����ڿ��� ȣ���� �Լ�

        //��ġ ���� (���ؿ�)
        POINT loc;
        
        //1�� = 30���� �����ؼ� ȣ���� ���ϰ�,
        //�ش� ȣ���� ���߾� ���� ��ġ�� ���մϴ�.
        //��, �ð� ����, �ð� ������ ��������.

        float locAngle = GetClockAngle(GetRadian(30));
        loc.x = origin.x + (-cos(locAngle)) * charDistance;
        loc.y = origin.y + (-sin(locAngle)) * charDistance;
        rect1 = { loc.x - 10, loc.y - 10, loc.x + 10, loc.y + 10 };
        
        // �̰� 2��(60��), 4��(120��)....� ��� �����մϴ�.

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
        //�������� ȣ���� �Լ�

        //�غ��� ���ڸ� �� ��Ʈ���� ����
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
