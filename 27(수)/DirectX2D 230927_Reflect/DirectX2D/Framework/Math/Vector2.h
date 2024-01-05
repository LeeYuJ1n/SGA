#pragma once

struct Vector2
{
    float x = 0.0f;
    float y = 0.0f;

    Vector2() = default;
    Vector2(float x, float y) : x(x), y(y) {};
    Vector2(POINT point) : x(point.x), y(point.y) {};
    Vector2(Float2 point) : x(point.x), y(point.y) {};

    Vector2 operator+(const Vector2& value) const
    {
        return Vector2(x + value.x, y + value.y);
    }
    Vector2 operator-(const Vector2& value) const
    {
        return Vector2(x - value.x, y - value.y);
    }
    Vector2 operator*(const Vector2& value) const
    {
        return Vector2(x * value.x, y * value.y);
    }
    Vector2 operator/(const Vector2& value) const
    {
        return Vector2(x / value.x, y / value.y);
    }
    Vector2 operator*(const float& value) const
    {
        return Vector2(x * value, y * value);
    }
    Vector2 operator/(const float& value) const
    {
        return Vector2(x / value, y / value);
    }

    void operator+=(const Vector2& value)
    {
        x += value.x;
        y += value.y;
    }
    void operator-=(const Vector2& value)
    {
        x -= value.x;
        y -= value.y;
    }
    void operator*=(const float& value)
    {
        x *= value;
        y *= value;
    }
    void operator/=(const float& value)
    {
        x /= value;
        y /= value;
    }

    float Length() const
    {
        return sqrt(x * x + y * y);
    }

    void Normalize()
    {
        float length = Length();

        x /= length;
        y /= length;
    }

    Vector2 GetNormalized() const
    {
        float length = Length();

        return Vector2(x / length, y / length);        
    }

    float Angle() const
    {
        return atan2(y, x);
    }


    //벡터와 행렬의 계산을 추가하자
    
    // 함수 오버라이드의 다른 형태 : 언어에 제공된 기능 중에서도 가장 원시적인... 연산자를 오버라이드하는 것
    // -> 연산자 오버라이드
    Vector2 operator* (const Matrix& value) const
    {
        Float2 coord(x, y); //x와 y라는 멤버로 명명되는 Float2 생성
        // 사칙연산에서 int result 만들고 그 result를 return 했던 것과 같은 방식

        XMVECTOR tmp = XMLoadFloat2(&coord); //다이렉트x용 벡터로 변환

        tmp = XMVector2TransformCoord(tmp, value); // 행렬에서 벡터가 가질 좌표값을 다시 벡터로 피드백

        //coord에 tmp 내용을 재반영
        XMStoreFloat2(&coord, tmp);

        return coord; //해당 Float2의 정보를 Vector2로 다시 반환
    }

    // 만든 김에... 누적연산자도?
    void operator*= (const Matrix& value)
    {
        Float2 coord(x, y);
        XMVECTOR tmp = XMLoadFloat2(&coord);
        tmp = XMVector2TransformCoord(tmp, value);

        XMStoreFloat2(&coord, tmp);

        //명명되고 만들어졌던 x, y 위치(연산 전 원본)에 새 결과(연산 결과) 할당
        x = coord.x;
        y = coord.y;
    }


    // 법선(수직으로 만나는 선)과 점곱(두 벡터 비율을 숫자로 표현한 것, 내적) 작성

    // 법선
    // 노멀 벡터라고도 한다 (위에 있는 정규화와 헷갈리면 안 된다)
    Vector2 Normal()
    {
        return Vector2(-y, x); //x의 좌표는 y로 가고, y의 좌표는 뒤집혀서 x로 간다
    }

    //점곱(내적)
    float Dot(Vector2 input) const
    {
        return (x * input.x) + (y * input.y);

        // 원래는 삼각함수 혹은 행렬식을 이용한 곱하기 계산이 나와야 하지만...
        // 다이렉트 x에서는 점곱의 대상이 되어야 할 방향벡터가 정규화가 이미 되어 있다
        // = 길이가 1, x y 좌표는 이미 삼각함수에서 코사인 사인에 대응하는 좌표가 되어 있다
        // 그렇기 때문에 input만 미리 정규화를 해두면 곱하는 과정에서 자동으로 각도에 대한 부분까지 계산이 끝난다
    }
};