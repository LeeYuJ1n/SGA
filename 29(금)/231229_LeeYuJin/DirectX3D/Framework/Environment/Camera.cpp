#include "Framework.h"

Camera::Camera()
{
    tag = "Camera";

    viewBuffer = new ViewBuffer();
    viewBuffer->SetVS(1);

    Load();

    prevMousePos = mousePos;
}

Camera::~Camera()
{
    delete viewBuffer;

    Save();
}

void Camera::Update()
{
    if (target)
        FollowMode();
    else
        FreeMode();

    SetView();
}

void Camera::RenderUI()
{
    if (ImGui::TreeNode("CameraOption"))
    {
        ImGui::DragFloat("MoveSpeed", &moveSpeed);
        ImGui::DragFloat("RotSpeed", &rotSpeed);

        if (target && ImGui::TreeNode("TargetOption"))
        {
            ImGui::DragFloat("Distance", &distance, 0.1f);
            ImGui::DragFloat("Height", &height, 0.1f);
            ImGui::DragFloat3("FocusOffset", (float*)&focusOffset, 0.1f);

            float degree = XMConvertToDegrees(rotY);
            ImGui::DragFloat("RotY", &degree, 0.1f);
            rotY = XMConvertToRadians(degree);

            ImGui::DragFloat("MoveDamping", &moveDamping, 0.1f);
            ImGui::DragFloat("RotDamping", &rotDamping, 0.1f);

            ImGui::Checkbox("LookAtTarget", &isLookAtTarget);

            ImGui::InputText("File", file, 128);

            if (ImGui::Button("Save"))
                TargetOptionSave(file);
            ImGui::SameLine();
            if (ImGui::Button("Load"))
                TargetOptionLoad(file);

            ImGui::TreePop();
        }

        Transform::RenderUI();

        ImGui::TreePop();
    }
}

void Camera::SetView()
{
    UpdateWorld();

    view = XMMatrixInverse(nullptr, world);

    viewBuffer->Set(view, world);
    viewBuffer->SetVS(1);
}

Vector3 Camera::ScreenToWorld(Vector3 pos)
{
    return XMVector3TransformCoord(pos, world);
}

Vector3 Camera::WorldToScreen(Vector3 pos)
{
    return XMVector3TransformCoord(pos, view);
}

Ray Camera::ScreenPointToRay(Vector3 screenPoint)
{
    Vector3 screenSize(WIN_WIDTH, WIN_HEIGHT, 1.0f);

    Vector2 point;
    point.x = (screenPoint.x / screenSize.x) * 2.0f - 1.0f;
    point.y = (screenPoint.y / screenSize.y) * 2.0f - 1.0f;

    Matrix projection = Environment::Get()->GetProjection();

    Float4x4 temp;
    XMStoreFloat4x4(&temp, projection);
    
    screenPoint.x = point.x / temp._11;
    screenPoint.y = point.y / temp._22;
    screenPoint.z = 1.0f;

    screenPoint = XMVector3TransformNormal(screenPoint, world);

    Ray ray;
    ray.pos = Pos();
    ray.dir = screenPoint.GetNormalized();

    return ray;
}

void Camera::FreeMode()
{
    Vector3 delta = mousePos - prevMousePos;
    prevMousePos = mousePos;

    if (KEY_PRESS(VK_RBUTTON))
    {
        if (KEY_PRESS('W'))
            Pos() += Forward() * moveSpeed * DELTA;
        if (KEY_PRESS('S'))
            Pos() += Back() * moveSpeed * DELTA;
        if (KEY_PRESS('A'))
            Pos() += Left() * moveSpeed * DELTA;
        if (KEY_PRESS('D'))
            Pos() += Right() * moveSpeed * DELTA;
        if (KEY_PRESS('E'))
            Pos() += Down() * moveSpeed * DELTA;
        if (KEY_PRESS('Q'))
            Pos() += Up() * moveSpeed * DELTA;

        Rot().x -= delta.y * rotSpeed * DELTA;
        Rot().y += delta.x * rotSpeed * DELTA;
    }
}

void Camera::FollowMode()
{
    // 카메라 추적 기능 함수 (3차원 버전으로)

    // 2차원 카메라 추적과 3차원 추적의 가장 큰 차이
    // : 좌우 조작이 들어왔을 때 회전을 하느냐 이동을 하느냐 (현재는 이 둘이 별개의 조작으로 분리)

    // -> 그 중에서 이 함수는 회전을 선택해서 구현 (카메라의 위치는 트랜스폼의 위치에 종속되도록)
    // -> 이 방법이 다른 게임에서도 현재 보편적으로 선호되는 방식

    //그래서 처음 다룰 변수 = 목표로 하는 회전정보
    destRot = Lerp(destRot, target->Rot().y, rotDamping * DELTA);

    // 회전 정보를 행렬화
    rotMatrix = XMMatrixRotationY(rotY + destRot);

    // Y축 회전 정보를 계산 = 좌우 회전 정도가 나왔다

    // 이 상태에서 앞이 어느 방향인지 계산

    Vector3 forward = XMVector3TransformNormal(Vector3::Forward(), rotMatrix);

    // 위치 계산
    destPos = target->GlobalPos() + (forward * -distance);
    // 타겟의 절대위치를 기준으로, 거리 계수만큼 뒤로 빼서 카메라 위치하게
    // -> distance에 따라 카메라와 캐릭터의 간격이 달라질 수 있음

    destPos.y += height; // 높이 계수만큼 위치를 더 올리기 (height 값에 따라 변동)

    // 목표 위치에 맞추어서 카메라의 실제 위치를 다시 보간
    Pos() = Lerp(Pos(), destPos, moveDamping * DELTA);

    // 여기까지 오면 타겟의 정보에 따라 카메라의 위치와 회전 정보를 얻게 된다

    if (isLookAtTarget) // 카메라가 타겟을 추적 + 타겟을 초점으로 삼고 있다면
    {
        //보정치(오프셋)부터 만들기
        Vector3 offset = XMVector3TransformCoord(focusOffset, rotMatrix);
        // 매개변수 focusOffset : 포커스를 맞춘 곳 (록온 위치)
        //         rotMatrix : 행렬 공간의 회전 정보

        // 목표의 위치를 찾아내기 (바로 위에 만든 오프셋 사용)
        Vector3 targetPos = target->GlobalPos() + offset;

        // 카메라의 방향 내기
        Vector3 dir = (targetPos - Pos()).GetNormalized();
        forward = Vector3(dir.x, 0, dir.z).GetNormalized(); // "앞"이 어디인지 다시 계산

        Rot().x = acos(Dot(forward, dir));
        Rot().y = atan2(dir.x, dir.z);

        // 이를 통해 타겟"을" 보도록 위치, 각도를 재조정
    }
}

void Camera::TargetOptionSave(string file)
{
    string path = "TextData/Camera/" + file + ".cam";

    BinaryWriter* writer = new BinaryWriter(path);

    writer->Float(distance);
    writer->Float(height);
    writer->Float(moveDamping);
    writer->Float(rotDamping);
    writer->Float(rotY);
    writer->Vector(focusOffset);
    writer->Bool(isLookAtTarget);

    delete writer;
}

void Camera::TargetOptionLoad(string file)
{
    string path = "TextData/Camera/" + file + ".cam";

    BinaryReader* reader = new BinaryReader(path);

    distance = reader->Float();
    height = reader->Float();
    moveDamping = reader->Float();
    rotDamping = reader->Float();
    rotY = reader->Float();
    focusOffset = reader->Vector();
    isLookAtTarget = reader->Bool();

    delete reader;
}
