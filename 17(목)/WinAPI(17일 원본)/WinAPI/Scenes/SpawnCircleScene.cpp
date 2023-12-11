#include "Framework.h"
#include "SpawnCircleScene.h"

SpawnCircleScene::SpawnCircleScene()
{
    // 서클 생성
    circle = new Circle(Vector2(CENTER_X, CENTER_Y), 50);

    hBrush = CreateSolidBrush(RGB(0, 255, 0));
    hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
}

SpawnCircleScene::~SpawnCircleScene()
{
    delete rect;
    delete circle;

    DeleteObject(hBrush);
}

void SpawnCircleScene::Update()
{
    int width = WIN_WIDTH;
    int height = WIN_HEIGHT;

    // asdw를 입력하면 움직이게
    if (KEY_PRESS(VK_LEFT))
    {
        circle->Pos() += Vector2(-speed, 0);
    }
    if (KEY_PRESS(VK_DOWN))
    {
        circle->Pos() += Vector2(0, speed);
    }
    if (KEY_PRESS(VK_RIGHT))
    {
        circle->Pos() += Vector2(speed, 0);
    }
    if (KEY_PRESS(VK_UP))
    {
        circle->Pos() += Vector2(0, -speed);
    }

    // 직선 그리는 준비 : 각도와 직선의 성분 설정
    angle = -atan2(mousePos.y - circle->Pos().y, mousePos.x - circle->Pos().x);
    // atan2 : 탄젠트 삼각함수를 통해서 각도를 구해내는 함수를 수행하는 기능의 ver2
    // 삼각함수의 기준(y값 방향)과 모니터 출력 기준(y값 방향을 맞추려면 이쪽도 -1 곱하기
    // 직선의 좌표
    pos.x = circle->Pos().x + cos(angle) * length;
    pos.y = circle->Pos().y + -sin(angle) * length;

    // 지금 직선을 그린 이유 : 하나는 "포탑"을 묘할 간이 그래픽을 그리기 위해
    //                        두 번째는 직선을 다시 그리면서 삼각함수의 속성을 생각하기 위해
    //                        → 결국 직선은 두 점의 관계, 각도는 관계의 방향

    // 여기서 좌클릭 시 "총알" 스폰
    if (KEY_DOWN(VK_LBUTTON))
    {
        bullets.push_back(new Bullet1(circle->Pos(), 10));
        bullets[bullets.size() - 1]->SetStat(angle, 20); // 직선 그리기에 쓴 각도 그대로 주기
        bullets[bullets.size() - 1]->Go();
    }

    // 지금은 여기서 스테이터스를 설정해주지만,
    // 만약 처음부터 클래스 내에 스테이터스가 있었더라면
    // 그 때는 총알을 그냥 "쏘기만"해도(스폰만 호출해도) 바로 움직일 것!!!
}

void SpawnCircleScene::Render(HDC hdc)
{
    SelectObject(hdc, hBrush);
    circle->Render(hdc);

    // 직선 그리기
    SelectObject(hdc, hPen);
    // 원점은 원의 중심
    MoveToEx(hdc, circle->Pos().x, circle->Pos().y, NULL);
    // 직선은 그리려는 위치까지
    LineTo(hdc, pos.x, pos.y);

    // 총알도...
    for (Bullet1* bullet : bullets)
    {
        bullet->RefreshLocation();
        bullet->Render(hdc);
    }
}
