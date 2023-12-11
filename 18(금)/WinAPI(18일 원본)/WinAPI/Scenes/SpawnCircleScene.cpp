#include "Framework.h"
#include "SpawnCircleScene.h"

SpawnCircleScene::SpawnCircleScene()
{
    srand(GetTickCount64());

    // 총알을 미리 생성
    bullets.resize(500);

    // for each 사용
    for (Bullet1*& bullet : bullets)
    {
        bullet = new Bullet1(Vector2(), bulletSize); 
        // 위치, 원점. 크기, 미리 정해진 대로

        // 액티브도 끄고, 멈추기
        bullet->Active() = false;
        bullet->Stop();
    }

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
        // bullets.push_back(new Bullet1(circle->Pos(), 10));
        // bullets[bullets.size() - 1]->SetStat(angle, 20); // 직선 그리기에 쓴 각도 그대로 주기
        // bullets[bullets.size() - 1]->Go();

        for (Bullet1* bullet : bullets)
        {
            if (bullet->Active() == false)
            {
                bullet->SetStat(angle, speed); // 각도와 속도 부여
                bullet->Pos() = circle->Pos(); // 위치 조정
                bullet->Go();                  // "가라!"
                bullet->Active() = true;       // 활성화 (시작)
                break; // 한 총알만 활성화하고, 다른 총알은 (반복문 중에) 더 만들지 않기
            }
        }
    }

    if (KEY_DOWN(VK_RBUTTON))
    {
        rects.push_back(new SpawnObject());
        rects[rects.size() - 1]->Spawn();
    }

    // 지금은 여기서 스테이터스를 설정해주지만,
    // 만약 처음부터 클래스 내에 스테이터스가 있었더라면
    // 그 때는 총알을 그냥 "쏘기만"해도(스폰만 호출해도) 바로 움직일 것!!!

    // 충돌이 났을 경우 상정한 반복문 제작
    
    // 각 총알이...
    for (Bullet1* bullet : bullets)
    {
        // * for each문이 시작되기 전에 while처럼 내부에서 사용할 변수를 미리 초기화 가능
        // 여기서는 사각형 벡터의 반복자를 미리 시작 위치로 만들기
        vector<SpawnObject*>::iterator itRect = rects.begin();
        // 각 사각형에....
        for (SpawnObject* rect : rects)
        {
            // 충돌을 일으켰다면
            if (bullet->IsCollision(rect))
            {
                // 뭔가를 수행한다
                // 반사는 어떻게 하지?

                // 1. 어떻게 반사됐는가? ("어디서 반사됐는가?")
                //    → 자리의 문제, 관계의 문제, 상황의 문제
                //    → 이 씬 안에 함수가 있는 편이 좋다

                // 2. 반사해서 어떻게 되는가? → 총알의 문제

                // 위 연산을 수행할 첫 함수를 헤더에서 만들고 호출
                // (1. 수행 후, 2. 까지 함수 내에서 호출)
                ReflectBullet(bullet, rect);

                // 사각형은 지우고 싶다
                rect->Destroy(); // 시각정보 및 활성화 해제
                // 그리고 얘를 벡터와 메모리에서 삭제를 해야 하는데..
                SpawnObject* rectDelete = rect;
                rects.erase(itRect); // 아까 만든 반복자 정보를 이용해 벡타에서 삭제
                delete rectDelete; // 메모리에서 삭제
                break; // 사각형 반복문 전체를 중단 (연산 효율 높이기 겸 반복자 초기화까지)
            }
            // 충돌이 안 일어났다면...
            // 다음 사각형을 검사하기 전에 반복자 정보를 갱신 (다음 사각혀엥 대응하도록)
            itRect++;
        }
    }
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
        if (bullet->Active()) // 활성화일 때만 적용하도록
        {
            bullet->RefreshLocation();
            bullet->Render(hdc);
        }
    }

    if (rects.size() > 0)
    {
        for (SpawnObject* rect : rects)
        {
            rect->Render(hdc);
        }
    }
}
