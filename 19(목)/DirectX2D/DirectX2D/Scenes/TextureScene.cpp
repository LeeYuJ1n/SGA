#include "Framework.h"
#include "TextureScene.h"



// 10-6일의 예습 혹은 복습

// 복습 : 오늘 알아본 전역 코드, 이벤트, 버튼을 활용해서...
//        버튼을 눌렀을 때 호출 가능한 다른 싱글턴 코드 써보기 (오디오, 불릿매니저 등)

// 예습 : 시간상 모두 다루지 못했던 std::function 기능의 좀 더 자세한 사항들
//        -> 클래스의 멤버 함수는 어떻게 사용할 수 있는가?
//        -> 호출 클래스와 작성 클래스가 같다면 (버튼에서 함수를 만들고
//           버튼에서 또 할당한다면) 그래도 오류가 나는가?

// -> 알아봐온 만큼을 카페에 올려주세요! 복습이면 실행 영상을, 예습이면 필기를 올려주세요.



// 10-5일의 복습 혹은 응용 과제 (양자 택일)

// 1. 씬 매니저를 통해서 또 다른 씬 만들어보기
//    로딩이 끝나고 비행기 씬으로 넘어가기 전에, 중간에 화면에 꽉 차는 그림이 나오는 씬을 만들어주세요.
//    일정 시간이 지나고, 본론인 비행기 씬으로 넘어가면 됩니다. 그림 선정은 자유입니다. (건전한 범위 내에서)

// 2. 비행기 씬에서 초기화와 종료 코드 채워넣기 :
//    다시 이 씬을 시작하면 총알이 없고 적들도 다른 곳에서 다시 나타나게




// 10-4일의 실습 겸 과제

// 로딩 씬 만들기 (흉내)

// 화면에 (배경이 있어도 되고 없어도 됩니다) 로딩 막대기가 있습니다.
// 로딩 막대기가 (진행 표시기, 프로그레스 바) 크기가 0에서 시간이 지나면 1까지 커지게 해주세요
// 
// (현재는 크기가 좌우로 커질 겁니다.
// 다만 프레임워크를 좀 더 살펴보시거나, 트랜스폼을 잘 응용했을 경우 막대기를 한쪽으로만 커지게 할 수도 있습니다)

// 로딩에 걸리는 시간은 자유롭게 설정하시면 되는데.... 2초보다는 좀 더 오래 걸리게 해주세요.
// 방향과 상관없이 로딩 막대기 크기가 1에 도달하면 텍스처 씬, 혹은 템퍼러리 씬 (우리가 만든 장면) 중 하나가 나오게 해주세요.

// 이렇게 로딩 씬(흉내) 구현을 해서 카페에 제출해주시기 바랍니다.

// (옵션) 로딩이 끝나면 "아무 키나 눌러주세요" 문구가 텍스처로 같이 뜨고, 그 상태에서 멈추게 해주세요.
// 여기서 아무 키나 (혹은 아무 키가 안 된다면 엔터 혹은 스페이스바 혹은 좌클릭) 눌렀을 때 씬을 넘어가게 해주세요.



// 27일의 실습 겸 과제
// 지금부터 해서, 되면 좋고 안 되면 과제로 해주셔도 됩니다.
// 연휴 동안에 한번 봐보시고 된 만큼 카페에 올려주세요.

// 1. 역행 : 충돌했을 때, 총알이 정반대로 날아가도록 해봅시다. -완료-

// 2. 삼각함수 복습 : WINAPI에서 썼던 각도에 의한 반사를 다시 한 번 써봅시다.
//                   XMConvertToDegrees : 다이렉트x 제공 함수, 매개변수로 호도를 넣으면 각도가 나옵니다.
//                   XMConvertToRadians : 위와 마찬가지, 매개변수로 각도를 넣으면 호도가 나옵니다.
//                   위 두 함수를 활용하면 직접 원주율 계산을 하지 않아도 각도와 호도 계산을 할 수 있습니다.

// -> 다음에 해봅시다.

// 3. 총알의 경우 짧은 시간에 너무 많은 같은 함수가 호출되면 활성화가 꺼지게 -각자 해보기-
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

    delete tmpButton;
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

    tmpButton->Update();
}

void TextureScene::Render()
{
    plane->Render();
    //enemy->Render();
    EnemyManager::Get()->Render();
    BulletManager::Get()->Render();

    for (Bullet* bulletS : sceneBullets)
        bulletS->Render();

    tmpButton->Render();
}

//다이렉트x에서 렌더의 절차를 쪼개어서 한 함수의 부담을 줄이는 방편
//이 함수에서 연산되는 함수들은 "화면에 보일 정보가 보인 다음" 덤으로 연산할 것들의 집합
void TextureScene::PostRender()
{
    //예 : 트랜스폼 정보 출력
    plane->RenderUI();
    //enemy->RenderUI();

}

void TextureScene::Init()
{
    // 이 장면이 초기화가 된다면, 어떻게 되어야 할까?

    tmpButton = new Button(L"Textures/Shooting/triEnemy.png");
    tmpButton->Pos() = { CENTER_X / 2, CENTER_Y };
}

void TextureScene::Quit()
{
    // 이 장면이 끝난다면, 어떤 코드를 수행하고 끝나야 할까?


}