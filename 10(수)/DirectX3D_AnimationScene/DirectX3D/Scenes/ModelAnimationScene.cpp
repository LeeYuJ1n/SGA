#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
    modelAnimator = new ModelAnimator("Human");
    modelAnimator->ReadClip("Idle", 1);
    modelAnimator->ReadClip("Run", 1);
    modelAnimator->ReadClip("Jump", 1);

    //modelAnimator = new ModelAnimator("Fox");
    //modelAnimator->ReadClip("Fox_Run");

    //modelAnimator = new ModelAnimator("Robot");
    //modelAnimator->ReadClip("Run");
    //modelAnimator->ReadClip("Walk");
    //modelAnimator->ReadClip("Dying");
    //modelAnimator->ReadClip("StandUp");
    //modelAnimator->ReadClip("Hit");
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
