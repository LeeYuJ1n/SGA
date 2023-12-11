#include "TimeAndCoord.h"
#include <math.h>

TimeAndCoord::TimeAndCoord(HWND _hWnd)
{
    this->hWnd = _hWnd; // ����� ������(��)
    hdc = GetDC(_hWnd); // ����� ���(�ϵ����)

    number = 0;
}

void TimeAndCoord::GetInput(WPARAM _wParam)
{

}

void TimeAndCoord::GetPoint(LPARAM _lParam)
{
    //���ӸŴ����� ���ؼ� �������� l-�Ű����� (=long, �� ������ �Ű����� �޽���) ����

    //��ǥ
    pointX = (float)LOWORD(_lParam);
    pointY = (float)HIWORD(_lParam);

    // �� �ڵ��� �ǹ� : lParam�� �����쿡�� �� �޽����� �߻����� ��
    //                 �Ű������� ó���ϴ� "ū �뷮" ��� �����͸� ��Ī (long)
    //                 ���콺 �Է¿��� �� �Ű������� ���̴µ�, ���콺�� ��� �ִ���
    //                 �巡�׸� ������ �巡�װ� ���� � ������� ���� �ȿ� ��´�
    //                 (�ݴ�� "���� �뷮" �� Ű �Է�, ���콺 1ȸ Ŭ�� ���� wParam) (w�� word)

    // ���콺 �Է��� ���� ���� �ٽ� �̷��� ���� "��" �з����͸� �м��ؼ�
    // �պκ�("���� �ڸ�")�� x��, �޺κ��� y�� �����Ѵ�
    // �׷��� WORD�� ��¥ �ڷ����� int�̹Ƿ� ��� �߿� ������ ���̷��� float���� ����ȯ

    //�� ����Ʈ�� �Ἥ ��ǥ����� �غ��ô�

    //�ؽ�Ʈ�� ó������ ������ �Ϸ��� string �ڷ����� �������� ������ ������ �ִ�
    // -> �׳� ��ٷ� ������ ��¥ ����


    //******************************************************
    //lstrcpy(lstr, TEXT("X : %f, Y : %f", pointX, pointY));
    // lstrcpy : c++ �� c���� ����ߴ� ���ڿ� ���� �Լ��� Ȯ��. 2 Ȥ�� 3����Ʈ �����ڵ忡 �����ϱ� ����
    // TEXT : char Ȥ�� wchar ���ڿ��� �� ������Ʈ�� �´� �����ڵ� ���ڿ��� �ٲ��ִ� ��ũ��
    // %f : (%d, %s ��� ����������) ���⿡ ���� �����͸� �����Ѵٴ� �ǹ��� ���Ĺ���. f�� �Ҽ�

    //lstrcpy�� c�� str �Լ��� printf�� �޸�, ���Ĺ��ڿ� ���� ���� �ݿ��� ���� �ʴ´ٰ� �մϴ�. �����սô�...��
    //******************************************************

    //��� ��Ʈ�� �ڷ����� ����ؼ� �׳� C++�� Ȯ��� ���ڿ� ����� ���� ����ϵ��� �ϰڽ��ϴ�.

    logCoord = L"X��ǥ : " + std::to_wstring(pointX) + L", Y��ǥ : " + std::to_wstring(pointY);
    //std::to_wstring(�Ű�����) : �Ű������� ���ڿ��� �ٲ��ִ�, ��Ʈ�� Ŭ���� ���� ���ڿ�.
    // �����ڵ尡 ����� ���� ������ ���ڿ��� �ٲٷ��� wstring���� �ٲٵ��� �߽��ϴ�.


    //Ŭ���� ���� �߽��� �簢�� ����
    rect2.left = pointX - 10;
    rect2.right = pointX + 10;
    rect2.top = pointY - 10;
    rect2.bottom = pointY + 10;


    //����� �����Ͱ� ����������� ȭ�� ��ȿȭ (���� ��ħ)
    InvalidateRect(hWnd, NULL, true);
}

void TimeAndCoord::Render()
{
    //�׸� �����Ͱ� ������ �׸� ����
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
    DrawText(hdc, logCoord.c_str(), -1, &rect, 0);
    //��Ʈ�� �ڷ��� ���� + c_str() �Լ� = ��Ʈ�� �ڷ����� �����ڵ忡 ���� ���ڿ�(wchar, chat_t)�� �ٲ��ݴϴ�.

    //Ŭ���� ���� �߽��� �簢�� ���
    Rectangle(hdc, rect2.left, rect2.top, rect2.right, rect2.bottom);

    //1�ʸ��� ���ŵ� ����
    DrawText(hdc, logTime.c_str(), -1, &rect3, 0);


    //1�ʸ��� ���ŵǴ� ���� �׸���
    x0 = 300;
    y0 = 300;

    x2 = x0 + (cos(GetRadian(st.wSecond * 6)) * 50);
    y2 = y0 + (-sin(GetRadian(st.wSecond * 6)) * 50);

    MoveToEx(hdc, x0, y0, NULL);
    LineTo(hdc, x2, y2);
}

void TimeAndCoord::Update()
{
    // 1�ʸ��� ���⼭ ������Ʈ �Լ� ����
    number++;
    
    GetLocalTime(&st); // ����ð��� �ҷ��ͼ� ������ ������ ���ش�
    //�� ����ü���� �� �� �ִ� �ڷ�
    st.wYear; // ��
    st.wMonth; // ��
    st.wDay; // ��¥
    st.wHour; // �ð�
    st.wMinute; // ��
    st.wSecond; // ��
    // �� �ڷḦ WORD, �� int�� Ȯ�� ����

    //���ڿ� (��Ʈ��) ����
    logTime = std::to_wstring(st.wYear) + L"�� "
        + std::to_wstring(st.wMonth) + L"�� "
        + std::to_wstring(st.wDay) + L"�� "
        + std::to_wstring(st.wHour) + L"�� "
        + std::to_wstring(st.wMinute) + L"�� "
        + std::to_wstring(st.wSecond) + L"��"
        + std::to_wstring(st.wMilliseconds) + L"�и���";


    //������ �� �Լ�����

    //���⼭�� ȭ�� ��ȿȭ
    InvalidateRect(hWnd, NULL, true);
}