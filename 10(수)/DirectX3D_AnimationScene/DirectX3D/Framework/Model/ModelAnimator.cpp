#include "Framework.h"
#include "ModelAnimator.h"

ModelAnimator::ModelAnimator(string name)
    : Model(name) // 이름을 받아서 모델을 불러오고 생성
{

    SetShader(L"Model/ModelAnimation.hlsl");
    frameBuffer = new FrameBuffer();

}

ModelAnimator::~ModelAnimator()
{
    for (ModelClip* clip : clips)
    {
        delete clip;
    }

    delete frameBuffer;

    //배열처럼 쓸 수 있는 집합성 변수들
    delete[] clipTransforms; // 배열처럼 쓰였다면 배열처럼 일괄삭제될 수 있게
    delete[] nodeTransforms;

    texture->Release(); // 자료가 있으면 있는 대로 지우고, 없어도 내버려 두고 (윈도우 기본 제공)
    srv->Release();

}

void ModelAnimator::Update()
{
    UpdateFrame(); //프레임을 업데이트하고
    UpdateWorld(); //업데이트된 정보에 따라 트랜스폼 업데이트 (정점, 화소 등이 갱신)
    // 그렇게 움직임을 "움직이는 것처럼" 보이게
}

void ModelAnimator::Render()
{
    if (texture == nullptr) CreateTexture(); // 직접 텍스처 만들기

    frameBuffer->SetVS(3); // 움직임의 정점 셰이더를 설정
    DC->VSSetShaderResources(0, 1, &srv); // GPU에 의한 셰이더 연산 후 출력

    Model::Render(); //부모의 렌더 함수 실행
}

void ModelAnimator::GUIRender()
{
    int clip = frameBuffer->Get().cur.clip;
    ImGui::SliderInt("Clip", &frameBuffer->Get().cur.clip, 0, clips.size() - 1);
    ImGui::SliderInt("Frame", (int*)&frameBuffer->Get().cur.curFrame,
        0, clips[clip]->frameCount - 1);
    ImGui::SliderFloat("Scale", &frameBuffer->Get().cur.scale, 0, 10.0f);

    Model::GUIRender();
}

// 움직임 불러오기
void ModelAnimator::ReadClip(string clipName, UINT clipNum)
{
    //지정된 모델의, 매개변수로 받은 움직임을, 매개변수로 받은 곳부터 쓰인 만큼
    string path = "Models/Clips/" + name + "/" + clipName + to_string(clipNum) + ".clip";

    BinaryReader* reader = new BinaryReader(path);

    ModelClip* clip = new ModelClip();
    clip->name = reader->String(); //움직임의 이름은 리더에 있었던 대로
    clip->frameCount = reader->UInt(); //프레임 개수도 파일에 있던 대로
    clip->tickPerSecond = reader->Float();
    UINT boneCount = reader->UInt(); //뼈대 개수도 읽어오기

    FOR(boneCount) //뼈 개수 동안
    {
        KeyFrame* keyFrame = new KeyFrame();
        keyFrame->boneName = reader->String();

        UINT size = reader->UInt();
        if (size > 0) // 크기가 있다면 = 프레임이 있다면
        {
            keyFrame->transforms.resize(size);

            void* ptr = (void*)keyFrame->transforms.data();
            reader->Byte(&ptr, sizeof(KeyTransform) * size); //안에 있는 트랜스폼 정보만큼 읽기
        }
        //프레임이 없었으면
        clip->keyFrames[keyFrame->boneName] = keyFrame; //뼈대 이름에 따라 새로 넣어주기
    }

    //만들어진 프레임의 집합을 (= 움직임을) 벡터에 최종 추가

    clips.push_back(clip);

    delete reader;
}

void ModelAnimator::PlayClip(int clip, float scale, float takeTime)
{
    // 위에서 준비된 움직임을 재생
    isPlay = true; // "재생 중"

    frameBuffer->Get().next.clip = clip;
    frameBuffer->Get().next.scale = scale;
    frameBuffer->Get().takeTime = takeTime;
}

Matrix ModelAnimator::GetTransformByNode(int nodeIndex)
{
    // 노드에서 트랜스폼 (크기, 회전, 움직임 등 정보) 얻기

    // 여기까지 와서도 텍스처가 없다 = 만들어진 움직임, 노드 정보가 없다
    if (texture == nullptr) return XMMatrixIdentity();

    //그렇지 않다면....
    Matrix curAnim;

    // 아무 조건 없는 중괄호 {} : 내부에서 만든 임시 공간 안에서 코딩을 진행한다는 뜻
    // 이 중괄호가 끝날 때마다 임시로 만들었던 변수들은 도로 사라진다 (지역변수, 전역변수...)
    {
        //현재 움직임 연산
        Frame& curFrame = frameBuffer->Get().cur;

        //노드 트랜스폼의 구조체 내 정보를 쫓아가서 행렬 추출
        Matrix cur = nodeTransforms[curFrame.clip].transform[curFrame.curFrame][nodeIndex];
        //다음 움직임도 미리 준비
        Matrix next = nodeTransforms[curFrame.clip].transform[curFrame.curFrame + 1][nodeIndex];

        //현재 계산 결과를 밖에서 만든 curAnim에 적용
        curAnim = Lerp(cur, next, curFrame.time);
        // Lerp = Line Interpolation, 선형 보간
        // 보간 : 사이를 채워넣기, 트랜스폼 등이 현재 위치가 있고 목적지가 있을 때,
        //        목적지까지 가야 할 시간과 현재의 경과 시간을 계산해서 해당 비율에 따라 위치를 재조정하는 방식
        //        (예) 이동을 10초 뒤에 100미터를 가야 하므로 1초 뒤에는 10미터, 3초 뒤에 30미터 가기 등으로 계산
    }
    // 여기까지 오면 curAnim 준비끝, 위쪽 {} 안에 있던 curFrame, cur, next 지워짐
    {
        //다음 움직임 연산
        Frame& nextFrame = frameBuffer->Get().cur;

        //다음 움직임으로 지정된 동작이 없으면 그냥 종료
        if (nextFrame.clip == -1) return curAnim; //위에서 만든 curAnim만 반환

        Matrix cur = nodeTransforms[nextFrame.clip].transform[nextFrame.curFrame][nodeIndex];
        Matrix next = nodeTransforms[nextFrame.clip].transform[nextFrame.curFrame + 1][nodeIndex];

        //다음 애니메이션 즉석에서 만들기
        Matrix nextAnim = Lerp(cur, next, nextFrame.time);

        //두 애니메이션 (curAnim와 nextAnim) 다시 보간해서 최종 반환
        return Lerp(curAnim, nextAnim, frameBuffer->Get().tweenTime);
        //마지막 매개변수 : 동작 전환에 걸려야 할 전환시간
    }

    return Matrix();
}

void ModelAnimator::CreateTexture()
{
    UINT clipCount = clips.size();

    clipTransforms = new ClipTransform[clipCount];
    nodeTransforms = new ClipTransform[clipCount];

    FOR(clipCount)
        CreateClipTransform(i);

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = MAX_BONE * 4;
    desc.Height = MAX_FRAME;
    desc.MipLevels = 1;
    desc.ArraySize = clipCount;
    desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_IMMUTABLE;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    UINT pitchSize = MAX_BONE * sizeof(Matrix);
    UINT pageSize = pitchSize * MAX_FRAME;

    void* p = VirtualAlloc(nullptr, pageSize * clipCount,
        MEM_RESERVE, PAGE_READWRITE);

    FOR(clipCount)
    {
        UINT start = i * pageSize;

        for (UINT y = 0; y < MAX_FRAME; y++)
        {
            void* temp = (BYTE*)p + pitchSize * y + start;

            VirtualAlloc(temp, pitchSize, MEM_COMMIT, PAGE_READWRITE);
            memcpy(temp, clipTransforms[i].transform[y], pitchSize);
        }
    }

    D3D11_SUBRESOURCE_DATA* subResource = new D3D11_SUBRESOURCE_DATA[clipCount];

    FOR(clipCount)
    {
        void* temp = (BYTE*)p + i * pageSize;

        subResource[i].pSysMem = temp;
        subResource[i].SysMemPitch = pitchSize;
        subResource[i].SysMemSlicePitch = pageSize;
    }

    DEVICE->CreateTexture2D(&desc, subResource, &texture);

    delete[] subResource;
    VirtualFree(p, 0, MEM_RELEASE);

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
    srvDesc.Texture2DArray.MipLevels = 1;
    srvDesc.Texture2DArray.ArraySize = clipCount;

    DEVICE->CreateShaderResourceView(texture, &srvDesc, &srv);
}

void ModelAnimator::CreateClipTransform(UINT index)
{
    ModelClip* clip = clips[index];

    FOR(clip->frameCount)
    {
        UINT nodeIndex = 0;

        for (NodeData node : nodes)
        {
            Matrix animation;
            KeyFrame* frame = clip->GetKeyFrame(node.name);
            if (frame != nullptr) //프레임이 있다면
            {
                KeyTransform& transform = frame->transforms[i];

                // 애니메이션을 DX 식으로 "생성"해서 배치
                animation = XMMatrixTransformation(
                    XMVectorZero(),                  //처음 만들어지는 곳 : 원점
                    XMQuaternionIdentity(),          //처음 주는 회전 값 : 기본
                    Vector3(transform.scale),        // 크기 값 : 트랜스폼대로
                    XMVectorZero(),                  // 추가 보정 : 없음
                    XMLoadFloat4(&transform.rot),    // 보정 회전 값 : 트랜스폼대로 (벡터를 사원수로)
                    Vector3(transform.pos)           // 추가 이동 : 트랜스폼이 원래 가야 할 위치로
                );
            }
            else
            {
                animation = XMMatrixIdentity(); //기본 행렬 = 그냥 없음
            }

            Matrix parent;
            int parentIndex = node.parent;

            if (parentIndex < 0) // 부모가 없는 상황
                parent = XMMatrixIdentity();
            else
                parent = nodeTransforms[index].transform[i][parentIndex];

            /// 두 행렬을 곱해서 자식이 있어야 할 공간정보 수정
            nodeTransforms[index].transform[i][nodeIndex] = animation * parent;

            int boneIndex = -1;
            if (boneMap.count(node.name)) // 노드 이름으로 저장된 뼈대가 있다면
                boneIndex = boneMap[node.name];     //추가 0109

            if (boneIndex >= 0)                     //추가 0109
            {
                //수정용 행렬 추가 (= 뼈대의 행렬 추가)

                Matrix offset = bones[boneIndex].offset; // 미리 지정된 보정치
                offset = offset * nodeTransforms[index].transform[i][nodeIndex]; // 위에서 만든 행렬 또 적용

                clipTransforms[index].transform[i][boneIndex] = offset;
                // -> 뼈대에 의한 정보(가중치, 기준, 회전기준 등) 다시 적용된 데이터
            }

            nodeIndex++; //반복문 수행을 계속 진행
        }
    }

    //여기까지 오면서 노드들의 행렬을 모아서 하나의 움직임 구성
}

void ModelAnimator::UpdateFrame()
{
    if (!isPlay) return; // 플레이 중이 아니면 수행할 필요 없음

    FrameBuffer::Data& frameData = frameBuffer->Get(); // 임시로 frameData로 버퍼 지칭

    //중괄호 안에서 계산 수행
    {
        ModelClip* clip = clips[frameData.cur.clip]; //지금 수행할 움직임

        // 얼마나 수행되어야 하는가(규모)를 진행 시간에 누적합산
        clip->playTime += frameData.cur.scale * DELTA;

        //애니메이션 자체의 분량이 얼마나 진행되어야 하는가를...(위와 같음)
        frameData.cur.time += clip->tickPerSecond * frameData.cur.scale * DELTA;

        if (frameData.cur.time >= 1.0f) // 시간이 소요되면
        {
            // 초가 지나면 프레임 체크
            frameData.cur.curFrame = (frameData.cur.curFrame + 1) % (clip->frameCount - 1);
            frameData.cur.time -= 1.0f; // 시간 재설정
        }
    }

    {
        if (frameData.next.clip < 0) return; //다음 프레임이 더 남지 않으면 종료

        //다음 프레임을 계산
        ModelClip* clip = clips[frameData.next.clip];

        frameData.tweenTime += DELTA / frameData.takeTime; // 걸려야 되는 시간을 전환시간에 누적

        if (frameData.tweenTime >= 1.0f) // 전환시간이 소요되면
        {
            frameData.cur = frameData.next; //프레임을 교체
            frameData.tweenTime = 0; // 전환시간 리셋

            frameData.next.clip = -1; //전환이 끝났으니 추가 지정이 없으면 다음 클립은 없음
            frameData.next.curFrame = 0; // 나머지 데이터도 리셋
            frameData.next.time = 0;
            return; //전환종료
        }

        //여기까지 왔다면 다음 프레임/클립을 재생해야 할 텐데, 아직 전환이 다 되지 않은 것

        //다음 동작을 계산할 차례

        frameData.next.time += clip->tickPerSecond * frameData.next.scale * DELTA;

        if (frameData.next.time >= 1.0f)
        {
            frameData.next.curFrame = (frameData.next.curFrame + 1) % (clip->frameCount - 1);
            frameData.next.time -= 1.0f;
        }
    }
}
