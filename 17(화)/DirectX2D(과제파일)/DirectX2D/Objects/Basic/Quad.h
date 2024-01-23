#pragma once

// Quad, 쿼드 : 기본 3D 형태를 프로그래밍에서 지칭하는 이름 중 하나
//              단어의 뜻은 "사변체" 혹은 "사면체"
//              프로그래밍에서는 직사각형 형태의, (렉트에 대응하는) 3D 모델
//              단, 두께가 0인 직사각형. (=2D에도 쓸 수 있거나, 3D에서 단면을 표현하는 데 쓴다)

//              간단히 말하면, 렉트를 3D 방식으로 이름을 바꾼 것

//              * 굳이 이름을 바꿀 필요가 있는가? - 의도의 문제.
//                쿼드라는 이름을 쓰면 이 물체를 2D가 아니라 3D의 문법으로 다루겠다는 의도를 명확히 할 수 있다.

//              * 똑같은 도형을 2D, 3D로 만들 때 차이가 있는가? - 그걸 알아보는 것이 오늘 시간의 목적


// 쿼드의 실제 내용 알아보기
class Quad : public GameObject
{
public:
    Quad(Vector2 size, Vector2 pos = Vector2());
    Quad(wstring file, Vector2 pos = Vector2()); //텍스처 그림으로 쿼드 만들기 (강의 중 추가)
    
    //추가 생성자 : 그림 잘라서 인스턴스 만들기
    Quad(bool useTrim, wstring file, Vector2 startUV = Vector2(), Vector2 endUV = Vector2(1, 1));

    // 여기서 생성자가 기본값에 의해 생략된 형태가 같아지면, 같은 생성자가 존재하는 것처럼 호출 오류
    // -> 해결 방법 : 1. 새 생성자가 이전 생성자와 매개변수 호출이 달라지게 하면 된다 2. 기존 생성자를 지운다
    //               1-b. (꼼수) "쓰지는 않을 거지만 입력은 해야 하는 매개변수"를 지정해주면 된다
    
    ~Quad();

    virtual void Render() override; //상속받은 함수에 +@로 뭔가를 하겠다

    void SetTexture(wstring file);

    // 렉트의 포지션처럼 텍스처에도 중심 좌표 구하기
    Vector2 Half() { return size * 0.5f; }

    Float4& GetColor() { return colorBuffer->Get(); }

private:
    void CreateMesh(Vector2 size, Vector2 pos); //<-"사각형" 생성을 빼냈다
    void CreateMesh(Vector2 size, Vector2 startUV, Vector2 endUV);

    // Mesh : 실체, fit(실제 존재, 크기가 있는, 크기가 맞는 형태)
    // "메시를 만든다" = 사물의 윤곽, 크기, 형태 등을 만든다는 뜻

    // "....그럼, 형태 말고도 사물에서 중요한 게 또 있나?" - 조금 뒤에 알아보겠습니다.

protected: //자식과 공유 가능한 데이터

    Texture* texture = nullptr; // 크기만 있는 색깔 메시와 호환유지를 위해 값 미리 지정

    Vector2 size; // "만들어진 쿼드의 크기"

    ColorBuffer* colorBuffer = nullptr; // 쿼드별 색상 정보
};