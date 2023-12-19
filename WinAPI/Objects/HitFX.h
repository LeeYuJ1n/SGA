#pragma once
class HitFX : public Rect
{
public:
    HitFX();
    HitFX(Vector2 pos, Vector2 size) :Rect(pos, size) {}
    HitFX(float left, float top, float right, float bottom)
        : Rect(left, top, right, bottom) {}

    //공개용 함수
    void Start(Rect* source, bool isLeft)
    {
        //위치를 지정 (만들어진 프라이빗 함수에 매개변수를 토스)
        SetPosition(source, isLeft);
        isActive = true;
    }

    //업데이트 호출용 함수
    void UpdateThis() //"업데이트"라는 이름은 공유, 다른 업데이트와는 달라서 "독립됐다"는 것을 표현
    {
        if (isActive) currentTime += DELTA; //누적시간 더하기

        if (currentTime > timeSpan)
        {
            currentTime = 0; //시간리셋
            isActive = false;
        }
    }

private:

    float currentTime = 0; //현재 이 FX가 가진 시간
    float timeSpan = 1;    //FX가 가진 "시간주기" = 이 span에 위의 시간 값이 도달하면 변화가 일어난다

    //active -> 상속받은 것을 이용

    //똑같은 위치 지정이지만 매개변수가 조금 다른...
    void SetPosition(Rect* source, bool isLeft)
    {
        // 원본 렉트로부터 "기준 위치"를 받고,
        // 왼쪽이면 왼쪽 일정 거리에, 오른쪽이면 오른쪽 일정 거리에 위치를 시키기

        float originX = source->Pos().x;
        float originY = source->Pos().y;

        //새 변수 : 원점에서의 거리 = 목적지
        float destX = isLeft ? originX - 100 : originX + 100;
        // 100 : 임시로 정한 렉트의 원점에서의 거리

        this->Pos().x = destX; //목적지 X 좌표
        this->Pos().y = originY; //현재는 원본과 높이 차이를 많이 안 둬도 될 것 같아서

        // * 만약 타격FX가 원본과 Y 좌표도 달라야 한다면 위 연산에도 수정이 가해져야 할 것
    }

};

