#include "Framework.h"

ModelInstancing::ModelInstancing(string name)
    : Model(name)
{
    // 정점 데이터를 따로 하나 만들고, 이름을 인스턴스 버퍼라고 지칭한다
    // -> 업데이트도 자기 안의 트랜스폼x 인스턴스 버퍼를 업데이트
    // -> 렌더도 자기 안의 메쉬를 x 인스턴스 버퍼를 통해 연산된 메쉬를 렌더

    // -> 실제로 나오는 건 여러 물체인데, 정작 컴퓨터가 연산하고 있는 대상은 하나밖에 없다
    //    -> 이런 원리로 컴퓨터가 여러 물체를 부드럽게, 빠르게, 무리하지 않고 렌더 가능

    // 모델뿐 아니라 애니메이터도 인스턴싱이 있다 ( -> 애니메이터 인스턴싱 확인)

    instanceBuffer = new VertexBuffer(instanceDatas, sizeof(InstanceData), MAX_INSTANCE);
    SetShader(L"Model/ModelInstancing.hlsl");
}

ModelInstancing::~ModelInstancing()
{
    delete instanceBuffer;

    for (Transform* transform : transforms)
        delete transform;
}

void ModelInstancing::Update()
{
    drawCount = 0;

    FOR(transforms.size())
    {
        if (transforms[i]->Active())
        {   
            transforms[i]->UpdateWorld();
            instanceDatas[drawCount].world = XMMatrixTranspose(transforms[i]->GetWorld());
            instanceDatas[drawCount].index = i;
            drawCount++;
        }
    }

    instanceBuffer->Update(instanceDatas, drawCount);
}

void ModelInstancing::Render()
{
    instanceBuffer->Set(1);

    for (ModelMesh* mesh : meshes)
        mesh->RenderInstanced(drawCount);
}

void ModelInstancing::GUIRender()
{
    ImGui::Text("DrawCount : %d", drawCount);

    for (Transform* transform : transforms)
        transform->GUIRender();
}

Transform* ModelInstancing::Add()
{
    Transform* transform = new Transform();
    transform->SetTag(name + "_" + to_string(transforms.size()));
    transforms.push_back(transform);

    return transform;
}
