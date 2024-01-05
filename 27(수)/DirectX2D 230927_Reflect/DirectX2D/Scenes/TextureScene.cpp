#include "Framework.h"
#include "TextureScene.h"

// 27일의 실습 겸 과제
// 지금부터 해서, 되면 좋고 안 되면 과제로 해주셔도 됩니다.
// 연휴 동안에 한번 봐보시고 된 만큼 카페에 올려주세요.

// 1. 역행 : 충돌했을 때, 총알이 정반대로 날아가도록 해봅시다.

// 2. 삼각함수 복습 : WINAPI에서 썼던 각도에 의한 반사를 다시 한 번 써봅시다.
//                   XMConvertToDegrees : 다이렉트x 제공 함수, 매개변수로 호도를 넣으면 각도가 나옵니다.
//                   XMConvertToRadians : 위와 마찬가지, 매개변수로 각도를 넣으면 호도가 나옵니다.
//                   위 두 함수를 활용하면 직접 원주율 계산을 하지 않아도 각도와 호도 계산을 할 수 있습니다.

// 3. 총알의 경우 짧은 시간에 너무 많은 같은 함수가 호출되면 활성화가 꺼지게
//    (Timer와 추가 int변수 등을 활용)

// 27일의 진짜 과제 : 포트폴리오 어떤 게임으로 할지 확정은 아니고 계획만...
//                   ...한 다음, 연휴가 끝나면 발표하기 (그 발표를 준비하기)
//                   모작이면 원작이 어떤 게임인지 소개하고, 자작이면 어떤 식으로 만들지 계획하기


TextureScene::TextureScene()
{
    plane = new Plane();
    plane->Pos() = { CENTER_X,CENTER_Y }; //상대 위치지만, 부모가 없어서 글로벌처럼 사용가능

    //enemy = new Enemy();
    //EnemyManager::Get(); // 적 매니저 호출 (=적 생성)
    EnemyManager::Get()->SetTarget(plane); // 씬에 있는 비행기를 표적으로 설정

    sceneBullets.resize(30);

    for (Bullet*& bulletS : sceneBullets)
        bulletS = new Bullet(L"Textures/Shooting/triEnemy.png");

    BulletManager::Get()->RegisterSceneBullet(&sceneBullets);


    //소리를 등록
    Audio::Get()->Add("BGM", "Sounds/drumloop.wav", true); // 브금으로 북소리를 등록
    Audio::Get()->Add("Bonk", "Sounds/Hit.wav"); //효과음으로 봉크 등록 (순환 없음)

    //브금 바로 출력
    Audio::Get()->Play("BGM", 0.8f); //"BGM"으로 등록했던 북소리가 재생. 두 번째 매개변수는 음량(선택)
}

TextureScene::~TextureScene()
{
    delete plane;
    //delete enemy;
    EnemyManager::Delete();

    for (Bullet* bulletS : sceneBullets)
        delete bulletS;
}

void TextureScene::Update()
{   
    Audio::Get()->Update(); // 소리 업데이트

    plane->Update();
    //enemy->Update();
    EnemyManager::Get()->Update();
    BulletManager::Get()->Update();

    for (Bullet* bulletS : sceneBullets)
        bulletS->Update();
}

void TextureScene::Render()
{
    plane->Render();
    //enemy->Render();
    EnemyManager::Get()->Render();
    BulletManager::Get()->Render();

    for (Bullet* bulletS : sceneBullets)
        bulletS->Render();
}

//다이렉트x에서 렌더의 절차를 쪼개어서 한 함수의 부담을 줄이는 방편
//이 함수에서 연산되는 함수들은 "화면에 보일 정보가 보인 다음" 덤으로 연산할 것들의 집합
void TextureScene::PostRender()
{
    //예 : 트랜스폼 정보 출력
    plane->RenderUI();
    //enemy->RenderUI();

}
