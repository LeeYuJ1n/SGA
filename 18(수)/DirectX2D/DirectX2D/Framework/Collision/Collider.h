#pragma once

// 윈API에서 우리가 썼던 "겹치면 판별한다"는 기능을 DX 2D로 재적용한 것

// 공통 기능 : 콜라이더 구현
// DX에는 물체가 겹치면 알아보는 제공된 함수가 있긴 하다
// -> 그런데 3D용. (DX 2D라고 하는 별도의 환경은 원래 없었다)

// 2D에서 도형이 서로 겹쳤을 때, 해당 데이터를 확인하기 위해서는
// 필연적으로 "도형이 겹쳤다"라는 경우의 수를 만들어둘 필요가 있다

class Collider : public Transform
{
protected:
    enum class Type //충돌된 도형의 타입
    {
        RECT, CIRCLE
    };

public:
    Collider();
    ~Collider();

    void Update();

    void Render(); //콜라이더 전용 렌더

    bool IsCollision(Collider* collider); //부딪쳤는가?

    // 점이 / 렉트가 / 서클이 나하고 부딪쳤는가?
    // 여기서는 아래 함수들이 추상 함수로 만들어져 있다
    virtual bool IsPointCollision(Vector2 point) = 0;
    virtual bool IsRectCollision(class RectCollider* rect, Vector2* overlap = nullptr) = 0;
    virtual bool IsCircleCollision(class CircleCollider* circle) = 0;

    // 색 구하기
    Float4& GetColor() { return colorBuffer->Get(); }

protected:
    Type type;

    // 도형의 정보를 (비트맵이 아니니) 메모리에 등록하기 위한 (등록된 메모리를 받기 위한) 변수
    // -> winAPI의 도형 정보를 DX용으로 다시 받기
    VertexBuffer* vertexBuffer;
    vector<VertexPos> vertices;

private:

    //셰이더 : 렌더용
    VertexShader* vertexShader;
    PixelShader* pixelShader;

    //위치 크기 회전과 색깔
    MatrixBuffer* worldBuffer;
    ColorBuffer* colorBuffer;
};