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
    // ī�޶� ���� ��� �Լ� (3���� ��������)

    // 2���� ī�޶� ������ 3���� ������ ���� ū ����
    // : �¿� ������ ������ �� ȸ���� �ϴ��� �̵��� �ϴ��� (����� �� ���� ������ �������� �и�)

    // -> �� �߿��� �� �Լ��� ȸ���� �����ؼ� ���� (ī�޶��� ��ġ�� Ʈ�������� ��ġ�� ���ӵǵ���)
    // -> �� ����� �ٸ� ���ӿ����� ���� ���������� ��ȣ�Ǵ� ���

    //�׷��� ó�� �ٷ� ���� = ��ǥ�� �ϴ� ȸ������
    destRot = Lerp(destRot, target->Rot().y, rotDamping * DELTA);

    // ȸ�� ������ ���ȭ
    rotMatrix = XMMatrixRotationY(rotY + destRot);

    // Y�� ȸ�� ������ ��� = �¿� ȸ�� ������ ���Դ�

    // �� ���¿��� ���� ��� �������� ���

    Vector3 forward = XMVector3TransformNormal(Vector3::Forward(), rotMatrix);

    // ��ġ ���
    destPos = target->GlobalPos() + (forward * -distance);
    // Ÿ���� ������ġ�� ��������, �Ÿ� �����ŭ �ڷ� ���� ī�޶� ��ġ�ϰ�
    // -> distance�� ���� ī�޶�� ĳ������ ������ �޶��� �� ����

    destPos.y += height; // ���� �����ŭ ��ġ�� �� �ø��� (height ���� ���� ����)

    // ��ǥ ��ġ�� ���߾ ī�޶��� ���� ��ġ�� �ٽ� ����
    Pos() = Lerp(Pos(), destPos, moveDamping * DELTA);

    // ������� ���� Ÿ���� ������ ���� ī�޶��� ��ġ�� ȸ�� ������ ��� �ȴ�

    if (isLookAtTarget) // ī�޶� Ÿ���� ���� + Ÿ���� �������� ��� �ִٸ�
    {
        //����ġ(������)���� �����
        Vector3 offset = XMVector3TransformCoord(focusOffset, rotMatrix);
        // �Ű����� focusOffset : ��Ŀ���� ���� �� (�Ͽ� ��ġ)
        //         rotMatrix : ��� ������ ȸ�� ����

        // ��ǥ�� ��ġ�� ã�Ƴ��� (�ٷ� ���� ���� ������ ���)
        Vector3 targetPos = target->GlobalPos() + offset;

        // ī�޶��� ���� ����
        Vector3 dir = (targetPos - Pos()).GetNormalized();
        forward = Vector3(dir.x, 0, dir.z).GetNormalized(); // "��"�� ������� �ٽ� ���

        Rot().x = acos(Dot(forward, dir));
        Rot().y = atan2(dir.x, dir.z);

        // �̸� ���� Ÿ��"��" ������ ��ġ, ������ ������
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
