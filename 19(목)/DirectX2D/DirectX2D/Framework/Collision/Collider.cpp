#include "Framework.h"

// 공통 도형 겹침의 경우에 어떻게 대응하려는가를 정하는 클래스

Collider::Collider()
{
    // 겹침 그 자체를 판별하려는 목적보다는 그 판별의 결과를 시각화하기 위해서
    vertexShader = Shader::AddVS(L"VertexPos.hlsl");
    pixelShader = Shader::AddPS(L"PixelPos.hlsl");

    // 판별을 위한 공간정보 받아오기 (크기, 위치, 회전)
    worldBuffer = new MatrixBuffer();

    // 다시 시각화
    colorBuffer = new ColorBuffer();
    colorBuffer->Get() = { 0, 1, 0, 1 };
}

Collider::~Collider()
{
    delete vertexBuffer;

    delete colorBuffer;
    delete worldBuffer;
}

void Collider::Update()
{
    Transform::UpdateWorld();

    // 콜라이더 활성화 관리 방법 2. 부모 트랜스폼의 활성화 정보를 받아서 Update 때 바로 반영
    // -> 규칙화, 덜 귀찮, 편리, 대신 중심코드에 의존해서 잘못 짜면 다 같이 망함
    // 이렇게 부모 트랜스폼의 활성화 정보를 다른 기능에서도 쓸 경우, 아래 코드 중 윗줄을
    // Tranform 클래스 안으로 옮겨주는 것이 더 좋을 수도 있다! (탱크의 포탑)
    if (parent != nullptr) isActive = parent->Active();
    if (!isActive) return;


}

void Collider::Render()
{
    if (!isActive) return;

    // 판별 결과를 시각화하기 위한 렌더 절차들, 버퍼를 모두 출력

    worldBuffer->Set(world);
    worldBuffer->SetVS(0);
    colorBuffer->SetPS(0);

    vertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);

    vertexShader->Set();
    pixelShader->Set();

    DC->Draw(vertices.size(), 0);
}

bool Collider::IsCollision(Collider* collider)
{
    // 겹쳤는가? 를 판별

    if (!Active()) return false;
    if (!collider->Active()) return false;

    // 부딪친 물체의 타입을 판별해서 해당 클래스로 재변환하고 개별 함수를 호출

    switch (collider->type)
    {
    case Collider::Type::RECT:
        return IsRectCollision((RectCollider*)collider);
    case Collider::Type::CIRCLE:
        return IsCircleCollision((CircleCollider*)collider);
    }

    return false;
}
