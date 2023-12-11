#pragma once

class Landscape
{
public:
    Landscape(wstring file, bool autoPlay);
    ~Landscape();

    void Update();
    void Render(HDC hdc);

    void SetSpeed(float speed) { bgSpeed = speed; }

    float GetPixelHeight(Vector2& pos); // 텍스처 내에 투명값이 지정된 경우
    float GetPixelHeight(Vector2& pos, COLORREF exColor); // 투명값 (제외값) 수동 입력

    HDC GetMemDC(Vector2& pos);

    float OffsetX() { return offsetX / offsetGl; }
    float OffsetY() { return 0; } // 임시

private:
    vector<ImageRect*> bgs;

    float bgSpeed = 0;
    bool autoScroll = false;

    void InitSpeed();

    // 지도가 스크롤했을 경우 좌표를 맞추기 위한 보정 변수
    float offsetX = 0;  // x좌표 (y가 있으면 y도 만듭시다)
    float offsetGl = 2; // 그림이 느리거나 크거나... 해서 1:1 비율이 안 맞을 때 맞추기 위한 
};