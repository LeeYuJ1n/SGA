#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
    // modelAnimator = new ModelAnimator("Human"); // 모델명으로 애니메이터 생성
    // modelAnimator->ReadClip("Idle", 1);         // 사전에 설정됐던 클립명으로 동작을 불러오기
    // modelAnimator->ReadClip("Run", 1);          // 동작의 이름은 .fbx에 내장되었던 동작이름(클립명)에서 따온 것
    // modelAnimator->ReadClip("Jump", 1);         // fbx 뷰어 프로그램 등을 사용하면 클립명, 기타 정보 확인 가능
                                                // 전용 뷰어 프로그램이 좋고, 편집 프로그램도 좋습니다 (예 : 3Ds MAX)

    // 가져온 동작에 따라 ReadClip 함수 실행
    // : 동작 구성에 따라 클립의 소분류가 지정된 경우, 호출할 때 클립의 수 (혹은 순번)를 매개변수로 하나 더 주면 된다
    //   -> 위에 있는 호출

    // modelAnimator = new ModelAnimator("Fox");
    // modelAnimator->ReadClip("Fox_Run");

    modelAnimator = new ModelAnimator("Robot");
    modelAnimator->ReadClip("Run");
    modelAnimator->ReadClip("Walk");
    modelAnimator->ReadClip("Dying");
    modelAnimator->ReadClip("StandUp");
    modelAnimator->ReadClip("Hit");
}

ModelAnimationScene::~ModelAnimationScene()
{
    delete modelAnimator;
}

void ModelAnimationScene::Update()
{
    if (KEY_DOWN('1'))
        modelAnimator->PlayClip(0);
    if (KEY_DOWN('2'))
        modelAnimator->PlayClip(1);
    if (KEY_DOWN('3'))
        modelAnimator->PlayClip(2);
    if (KEY_DOWN('4'))
        modelAnimator->PlayClip(3);
    if (KEY_DOWN('4'))
        modelAnimator->PlayClip(4);

    modelAnimator->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
    modelAnimator->Render();
}

void ModelAnimationScene::PostRender()
{
}

void ModelAnimationScene::GUIRender()
{
    modelAnimator->GUIRender();
}

void ModelAnimationScene::SetIdle()
{
    modelAnimator->PlayClip(0, 1.0f, 0.1f);
}
