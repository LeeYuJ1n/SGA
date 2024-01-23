#include "Framework.h"

ProgressBar::ProgressBar()
{
    //기본 텍스처를 사용한 쿼드 생성
    image = new Quad(L"Textures/yellow.png");

    Adjust();
}

ProgressBar::ProgressBar(wstring file) //매개변수가 있을 때는 멤버변수에 그대로 토스
{
    image = new Quad(file);

    Adjust();
}

ProgressBar::~ProgressBar()
{
    delete image;
}

void ProgressBar::Update()
{
    Transform::UpdateWorld();
    image->Update();
}

void ProgressBar::Render()
{
    image->Render();
}

// 아래 두 함수의 역할
// 1. 자기 자신은 미리 왼쪽으로 살짝 이동
// 2. 보여져야 할 실제 그림 텍스처를 다시 오른쪽으로 이동

// -> 그림은 원래 그 자리에 그대로 있지만 부모 트랜스폼(움직임의 중심)은 왼쪽으로 이동한 상태
// -> 사실상 축이 이동한 것이나 다름없다

void ProgressBar::Adjust()
{
    //생성시 진행바 위치를 조정하기 위한 것
    
    // 텍스처에 부모 트랜스폼을 줘야 한다(바로 이 클래스)
    image->SetParent(this);
    
    // 텍스처를 본래의 위치(0, 0)=부모의 위치에서 오른쪽으로 밀어낸다
    image->Pos() = { image->Half().x, 0 };
}

void ProgressBar::SetPosition(Vector2 pos)
{
    localPosition = { pos.x - image->Half().x, pos.y };
}