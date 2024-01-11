#include "Framework.h"

ModelAnimatorInstancing::ModelAnimatorInstancing(string name)
    : ModelAnimator(name)
{
    SetShader(L"Model/ModelAnimationInstancing.hlsl");

    // 인스턴스 할당 + 업데이트, 렌더에서 자기 자신 대신 인스턴스의 데이터를 연산 수행
    // 요점 : 모델의 정점 정보, 뼈대 정보 등 공유 가능한 것들을 최대한 텍스처처럼 한 리소스에서 뽑아 처리하자
    instanceBuffer = new VertexBuffer(instanceDatas, sizeof(InstanceData), MAX_INSTANCE);
    frameInstancingBuffer = new FrameInstancingBuffer();
}

ModelAnimatorInstancing::~ModelAnimatorInstancing()
{
    delete instanceBuffer;
    delete frameInstancingBuffer;

    for (Transform* transform : transforms)
        delete transform;
}

void ModelAnimatorInstancing::Update()
{
    UpdateTransforms();
}

void ModelAnimatorInstancing::Render()
{
    if (texture == nullptr)
        CreateTexture();

    instanceBuffer->Set(1); // 인스턴스 주기
    frameInstancingBuffer->SetVS(4);
    DC->VSSetShaderResources(0, 1, &srv);

    for (ModelMesh* mesh : meshes)
        mesh->RenderInstanced(drawCount);
}

void ModelAnimatorInstancing::GUIRender()
{
    ImGui::Text("DrawCount : %d", drawCount);

    for (Transform* transform : transforms)
        transform->GUIRender();
}

Transform* ModelAnimatorInstancing::Add()
{
    Transform* transform = new Transform();
    transform->SetTag(name + "_" + to_string(transforms.size()));
    transforms.push_back(transform);

    return transform;
}

void ModelAnimatorInstancing::PlayClip(UINT instanceID, int clip, float scale, float takeTime)
{
    frameInstancingBuffer->Get().motions[instanceID].next.clip = clip;
    frameInstancingBuffer->Get().motions[instanceID].next.scale = scale;
    frameInstancingBuffer->Get().motions[instanceID].takeTime = takeTime;
    frameInstancingBuffer->Get().motions[instanceID].runningTime = 0.0f;
}

void ModelAnimatorInstancing::UpdateFrame(UINT instanceID, Motion& motion)
{
    {
        ModelClip* clip = clips[motion.cur.clip];

        motion.runningTime += motion.cur.scale * DELTA;
        motion.cur.time += clip->tickPerSecond * motion.cur.scale * DELTA;

        if (motion.cur.time >= 1.0f)
        {
            motion.cur.curFrame = (motion.cur.curFrame + 1) % (clip->frameCount - 1);
            motion.cur.time -= 1.0f;
        }
    }

    {
        if (motion.next.clip < 0) return;

        ModelClip* clip = clips[motion.next.clip];

        motion.tweenTime += DELTA / motion.takeTime;

        if (motion.tweenTime >= 1.0f)
        {
            motion.cur = motion.next;
            motion.tweenTime = 0.0f;

            motion.next.clip = -1;
            motion.next.curFrame = 0;
            motion.next.time = 0.0f;
            return;
        }

        motion.next.time += clip->tickPerSecond * motion.next.scale * DELTA;

        if (motion.next.time >= 1.0f)
        {
            motion.next.curFrame = (motion.next.curFrame + 1) % (clip->frameCount - 1);
            motion.next.time -= 1.0f;
        }
    }
}

void ModelAnimatorInstancing::UpdateTransforms()
{
    drawCount = 0;

    FOR(transforms.size())
    {
        if (transforms[i]->Active())
        {
            // 애니메이션의 인스턴싱 중에 만들어진 객체가 절두체 안에 있으면 렌더 (프레임 업데이트)
            // 없으면 아무것도 하지 않음 -> 렌더 꺼짐

            // 간단히 말하면 "지금 내 눈에 보이면 그리고 안 보일 거면 그리지도 말아라"

            if (!CAM->ContainPoint(transforms[i]->GlobalPos())) continue;
            
            // 위 코드를 사용함으로써 모니터에 출력되는 물체의 렌더 연산 (정점 연산, 렌더를 위한 버퍼 준비)을
            // 낭비하지 않을 수 있다

            // 인스턴싱의 존재 의의와 비슷 : 렌더(최종 출력)까지 줄이진 못하지만, 적어도 렌더가 필요없는 상황에서
            //                             렌더에 낭비될 컴퓨터 연산을 줄여주는 것은 가능

            // 이것이 프러스텀(절두체) 컬링 = frustum culling

            // frustum culling(절두체 컬링) : 눈에 보이는 것만 렌더링
            // Back-face culling : 눈에 보이더라도 보이는 면만 렌더링하며, 눈에 보이지 않는 면은 렌더링을 하지 않는다
            // Occlusion Culling : 다른 오브젝트에 가려(오클루전된) 카메라에 보이지 않는 오브젝트의 렌더링을 비활성화하는 기능

            UpdateFrame(i, frameInstancingBuffer->Get().motions[i]);
            transforms[i]->UpdateWorld();
            instanceDatas[drawCount].world = XMMatrixTranspose(transforms[i]->GetWorld());
            instanceDatas[drawCount].index = i;
            drawCount++;
        }
    }

    instanceBuffer->Update(instanceDatas, drawCount);
}
