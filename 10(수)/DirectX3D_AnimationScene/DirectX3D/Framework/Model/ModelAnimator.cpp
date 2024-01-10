#include "Framework.h"
#include "ModelAnimator.h"

ModelAnimator::ModelAnimator(string name)
    : Model(name) // �̸��� �޾Ƽ� ���� �ҷ����� ����
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

    //�迭ó�� �� �� �ִ� ���ռ� ������
    delete[] clipTransforms; // �迭ó�� �����ٸ� �迭ó�� �ϰ������� �� �ְ�
    delete[] nodeTransforms;

    texture->Release(); // �ڷᰡ ������ �ִ� ��� �����, ��� ������ �ΰ� (������ �⺻ ����)
    srv->Release();

}

void ModelAnimator::Update()
{
    UpdateFrame(); //�������� ������Ʈ�ϰ�
    UpdateWorld(); //������Ʈ�� ������ ���� Ʈ������ ������Ʈ (����, ȭ�� ���� ����)
    // �׷��� �������� "�����̴� ��ó��" ���̰�
}

void ModelAnimator::Render()
{
    if (texture == nullptr) CreateTexture(); // ���� �ؽ�ó �����

    frameBuffer->SetVS(3); // �������� ���� ���̴��� ����
    DC->VSSetShaderResources(0, 1, &srv); // GPU�� ���� ���̴� ���� �� ���

    Model::Render(); //�θ��� ���� �Լ� ����
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

// ������ �ҷ�����
void ModelAnimator::ReadClip(string clipName, UINT clipNum)
{
    //������ ����, �Ű������� ���� ��������, �Ű������� ���� ������ ���� ��ŭ
    string path = "Models/Clips/" + name + "/" + clipName + to_string(clipNum) + ".clip";

    BinaryReader* reader = new BinaryReader(path);

    ModelClip* clip = new ModelClip();
    clip->name = reader->String(); //�������� �̸��� ������ �־��� ���
    clip->frameCount = reader->UInt(); //������ ������ ���Ͽ� �ִ� ���
    clip->tickPerSecond = reader->Float();
    UINT boneCount = reader->UInt(); //���� ������ �о����

    FOR(boneCount) //�� ���� ����
    {
        KeyFrame* keyFrame = new KeyFrame();
        keyFrame->boneName = reader->String();

        UINT size = reader->UInt();
        if (size > 0) // ũ�Ⱑ �ִٸ� = �������� �ִٸ�
        {
            keyFrame->transforms.resize(size);

            void* ptr = (void*)keyFrame->transforms.data();
            reader->Byte(&ptr, sizeof(KeyTransform) * size); //�ȿ� �ִ� Ʈ������ ������ŭ �б�
        }
        //�������� ��������
        clip->keyFrames[keyFrame->boneName] = keyFrame; //���� �̸��� ���� ���� �־��ֱ�
    }

    //������� �������� ������ (= ��������) ���Ϳ� ���� �߰�

    clips.push_back(clip);

    delete reader;
}

void ModelAnimator::PlayClip(int clip, float scale, float takeTime)
{
    // ������ �غ�� �������� ���
    isPlay = true; // "��� ��"

    frameBuffer->Get().next.clip = clip;
    frameBuffer->Get().next.scale = scale;
    frameBuffer->Get().takeTime = takeTime;
}

Matrix ModelAnimator::GetTransformByNode(int nodeIndex)
{
    // ��忡�� Ʈ������ (ũ��, ȸ��, ������ �� ����) ���

    // ������� �ͼ��� �ؽ�ó�� ���� = ������� ������, ��� ������ ����
    if (texture == nullptr) return XMMatrixIdentity();

    //�׷��� �ʴٸ�....
    Matrix curAnim;

    // �ƹ� ���� ���� �߰�ȣ {} : ���ο��� ���� �ӽ� ���� �ȿ��� �ڵ��� �����Ѵٴ� ��
    // �� �߰�ȣ�� ���� ������ �ӽ÷� ������� �������� ���� ������� (��������, ��������...)
    {
        //���� ������ ����
        Frame& curFrame = frameBuffer->Get().cur;

        //��� Ʈ�������� ����ü �� ������ �Ѿư��� ��� ����
        Matrix cur = nodeTransforms[curFrame.clip].transform[curFrame.curFrame][nodeIndex];
        //���� �����ӵ� �̸� �غ�
        Matrix next = nodeTransforms[curFrame.clip].transform[curFrame.curFrame + 1][nodeIndex];

        //���� ��� ����� �ۿ��� ���� curAnim�� ����
        curAnim = Lerp(cur, next, curFrame.time);
        // Lerp = Line Interpolation, ���� ����
        // ���� : ���̸� ä���ֱ�, Ʈ������ ���� ���� ��ġ�� �ְ� �������� ���� ��,
        //        ���������� ���� �� �ð��� ������ ��� �ð��� ����ؼ� �ش� ������ ���� ��ġ�� �������ϴ� ���
        //        (��) �̵��� 10�� �ڿ� 100���͸� ���� �ϹǷ� 1�� �ڿ��� 10����, 3�� �ڿ� 30���� ���� ������ ���
    }
    // ������� ���� curAnim �غ�, ���� {} �ȿ� �ִ� curFrame, cur, next ������
    {
        //���� ������ ����
        Frame& nextFrame = frameBuffer->Get().cur;

        //���� ���������� ������ ������ ������ �׳� ����
        if (nextFrame.clip == -1) return curAnim; //������ ���� curAnim�� ��ȯ

        Matrix cur = nodeTransforms[nextFrame.clip].transform[nextFrame.curFrame][nodeIndex];
        Matrix next = nodeTransforms[nextFrame.clip].transform[nextFrame.curFrame + 1][nodeIndex];

        //���� �ִϸ��̼� �Ｎ���� �����
        Matrix nextAnim = Lerp(cur, next, nextFrame.time);

        //�� �ִϸ��̼� (curAnim�� nextAnim) �ٽ� �����ؼ� ���� ��ȯ
        return Lerp(curAnim, nextAnim, frameBuffer->Get().tweenTime);
        //������ �Ű����� : ���� ��ȯ�� �ɷ��� �� ��ȯ�ð�
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
            if (frame != nullptr) //�������� �ִٸ�
            {
                KeyTransform& transform = frame->transforms[i];

                // �ִϸ��̼��� DX ������ "����"�ؼ� ��ġ
                animation = XMMatrixTransformation(
                    XMVectorZero(),                  //ó�� ��������� �� : ����
                    XMQuaternionIdentity(),          //ó�� �ִ� ȸ�� �� : �⺻
                    Vector3(transform.scale),        // ũ�� �� : Ʈ���������
                    XMVectorZero(),                  // �߰� ���� : ����
                    XMLoadFloat4(&transform.rot),    // ���� ȸ�� �� : Ʈ��������� (���͸� �������)
                    Vector3(transform.pos)           // �߰� �̵� : Ʈ�������� ���� ���� �� ��ġ��
                );
            }
            else
            {
                animation = XMMatrixIdentity(); //�⺻ ��� = �׳� ����
            }

            Matrix parent;
            int parentIndex = node.parent;

            if (parentIndex < 0) // �θ� ���� ��Ȳ
                parent = XMMatrixIdentity();
            else
                parent = nodeTransforms[index].transform[i][parentIndex];

            /// �� ����� ���ؼ� �ڽ��� �־�� �� �������� ����
            nodeTransforms[index].transform[i][nodeIndex] = animation * parent;

            int boneIndex = -1;
            if (boneMap.count(node.name)) // ��� �̸����� ����� ���밡 �ִٸ�
                boneIndex = boneMap[node.name];     //�߰� 0109

            if (boneIndex >= 0)                     //�߰� 0109
            {
                //������ ��� �߰� (= ������ ��� �߰�)

                Matrix offset = bones[boneIndex].offset; // �̸� ������ ����ġ
                offset = offset * nodeTransforms[index].transform[i][nodeIndex]; // ������ ���� ��� �� ����

                clipTransforms[index].transform[i][boneIndex] = offset;
                // -> ���뿡 ���� ����(����ġ, ����, ȸ������ ��) �ٽ� ����� ������
            }

            nodeIndex++; //�ݺ��� ������ ��� ����
        }
    }

    //������� ���鼭 ������ ����� ��Ƽ� �ϳ��� ������ ����
}

void ModelAnimator::UpdateFrame()
{
    if (!isPlay) return; // �÷��� ���� �ƴϸ� ������ �ʿ� ����

    FrameBuffer::Data& frameData = frameBuffer->Get(); // �ӽ÷� frameData�� ���� ��Ī

    //�߰�ȣ �ȿ��� ��� ����
    {
        ModelClip* clip = clips[frameData.cur.clip]; //���� ������ ������

        // �󸶳� ����Ǿ�� �ϴ°�(�Ը�)�� ���� �ð��� �����ջ�
        clip->playTime += frameData.cur.scale * DELTA;

        //�ִϸ��̼� ��ü�� �з��� �󸶳� ����Ǿ�� �ϴ°���...(���� ����)
        frameData.cur.time += clip->tickPerSecond * frameData.cur.scale * DELTA;

        if (frameData.cur.time >= 1.0f) // �ð��� �ҿ�Ǹ�
        {
            // �ʰ� ������ ������ üũ
            frameData.cur.curFrame = (frameData.cur.curFrame + 1) % (clip->frameCount - 1);
            frameData.cur.time -= 1.0f; // �ð� �缳��
        }
    }

    {
        if (frameData.next.clip < 0) return; //���� �������� �� ���� ������ ����

        //���� �������� ���
        ModelClip* clip = clips[frameData.next.clip];

        frameData.tweenTime += DELTA / frameData.takeTime; // �ɷ��� �Ǵ� �ð��� ��ȯ�ð��� ����

        if (frameData.tweenTime >= 1.0f) // ��ȯ�ð��� �ҿ�Ǹ�
        {
            frameData.cur = frameData.next; //�������� ��ü
            frameData.tweenTime = 0; // ��ȯ�ð� ����

            frameData.next.clip = -1; //��ȯ�� �������� �߰� ������ ������ ���� Ŭ���� ����
            frameData.next.curFrame = 0; // ������ �����͵� ����
            frameData.next.time = 0;
            return; //��ȯ����
        }

        //������� �Դٸ� ���� ������/Ŭ���� ����ؾ� �� �ٵ�, ���� ��ȯ�� �� ���� ���� ��

        //���� ������ ����� ����

        frameData.next.time += clip->tickPerSecond * frameData.next.scale * DELTA;

        if (frameData.next.time >= 1.0f)
        {
            frameData.next.curFrame = (frameData.next.curFrame + 1) % (clip->frameCount - 1);
            frameData.next.time -= 1.0f;
        }
    }
}
