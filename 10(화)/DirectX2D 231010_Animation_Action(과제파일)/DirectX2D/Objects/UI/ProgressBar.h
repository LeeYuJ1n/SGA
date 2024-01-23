#pragma once

class ProgressBar : public Transform
{
public:

    ProgressBar();
    ProgressBar(wstring file);
    ~ProgressBar();

    // 트랜스폼에는 사실 Update가 없다(필요도 없다)
    // 그런데 이 진행바 클래스는 사물처럼 써야 되니까 Update Render도 상속에 상관없이 굳이 만든다
    void Update();
    void Render();
    void PostRender() {} // 지금 쓰려는 건 아니지만 미리 만들어둔다

    void SetPosition(Vector2 pos); // 위치 지정 함수 = Pos() 간편 대체용

private:

    //이 클래스의 존재목적 : 텍스처 (이미지)
    Quad* image;

    void Adjust(); //조정 함수 = 생성시 공통 호출용
};

