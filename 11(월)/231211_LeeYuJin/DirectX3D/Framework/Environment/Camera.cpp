#include "Framework.h"

Camera::Camera()
{
    tag = "Camera";

    viewBuffer = new MatrixBuffer();
    viewBuffer->SetVS(1);

    Load();
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

        Transform::RenderUI();

        ImGui::TreePop();
    }
}

void Camera::SetView()
{
    UpdateWorld();

    view = XMMatrixInverse(nullptr, world);

    viewBuffer->Set(view);
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

void Camera::FreeMode()
{
    if (KEY_PRESS(VK_RBUTTON))
    {
        if (KEY_PRESS('W'))
            Pos().z += moveSpeed * DELTA;
        if (KEY_PRESS('S'))
            Pos().z -= moveSpeed * DELTA;
        if (KEY_PRESS('A'))
            Pos().x -= moveSpeed * DELTA;
        if (KEY_PRESS('D'))
            Pos().x += moveSpeed * DELTA;
        if (KEY_PRESS('E'))
            Pos().y -= moveSpeed * DELTA;
        if (KEY_PRESS('Q'))
            Pos().y += moveSpeed * DELTA;
    
        ImVec2 delta = ImGui::GetIO().MouseDelta;
    
        Rot().x += delta.y * rotSpeed * DELTA;
        Rot().y += delta.x * rotSpeed * DELTA;
    }
}

void Camera::FollowMode()
{    
}