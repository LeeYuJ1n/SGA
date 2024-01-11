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
    projection = Environment::Get()->GetProjection();
    Frustum();

    if (target)
        FollowMode();
    else
        FreeMode();

    SetView();
}

void Camera::GUIRender()
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

            ImGui::Checkbox("LookAtTargetX", &isLookAtTargetX);
            ImGui::Checkbox("LookAtTargetY", &isLookAtTargetY);
            
            ImGui::InputText("File", file, 128);

            if(ImGui::Button("Save"))
                TargetOptionSave(file);
            ImGui::SameLine();
            if (ImGui::Button("Load"))
                TargetOptionLoad(file);

            ImGui::TreePop();
        }

        Transform::GUIRender();

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

void Camera::LookAtTarget()
{    
    rotMatrix = XMMatrixRotationY(target->Rot().y + rotY);

    Vector3 forward = XMVector3TransformNormal(Vector3::Forward(), rotMatrix);

    Pos() = target->GlobalPos() + forward * -distance;
    Pos().y += height;    

    Vector3 offset = XMVector3TransformCoord(focusOffset, rotMatrix);
    Vector3 targetPos = target->GlobalPos() + offset;

    Vector3 dir = (targetPos - Pos()).GetNormalized();
    forward = Vector3(dir.x, 0.0f, dir.z).GetNormalized();

    Rot().x = acos(Dot(forward, dir));
    Rot().y = atan2(dir.x, dir.z);
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
    destRot = Lerp(destRot, target->Rot().y, rotDamping * DELTA);    
    rotMatrix = XMMatrixRotationY(destRot + rotY);

    Vector3 forward = XMVector3TransformNormal(Vector3::Forward(), rotMatrix);

    destPos = target->GlobalPos() + forward * -distance;
    destPos.y += height;

    Pos() = Lerp(Pos(), destPos, moveDamping * DELTA);    

    Vector3 offset = XMVector3TransformCoord(focusOffset, rotMatrix);
    Vector3 targetPos = target->GlobalPos() + offset;

    Vector3 dir = (targetPos - Pos()).GetNormalized();
    forward = Vector3(dir.x, 0.0f, dir.z).GetNormalized();

    if (isLookAtTargetX)
    {
        Rot().x = acos(Dot(forward, dir));        
    }    
    if (isLookAtTargetY)
    {
        Rot().y = atan2(dir.x, dir.z);
    }
}

void Camera::Frustum()
{
    Float4x4 VP; // ����Ʈ �ӽ� ����
    XMStoreFloat4x4(&VP, view * projection); // ����Ʈ�� ����� ����
                                             // ��� ���� ��� : ����Ʈ ���(2���� ���� 3����) x ��������(���� 3����)
                                             //                  �� ������ ���ذ� �߿�!(����� ���� � �����ε� �� �� �����ϱ�)
                                             // -> ��İ� ��� (4x4 ��� x 4x4 ��� = 4x4 ���)
                                             //    ��� ����� ������, ���� ����� �޶�����
                                             //     -> ������ ����Ʈ ����� �������� ����� ������ �޾� ��â�ϰ� �ȴ�
                                             //     -> �� ����� �ٷ� ����ü

    // ���� ���ο� ����Ʈ (3���� ���, ��ʱ� ����, ���� ���� �ڷ� ������ ��â�ϴ� ���ο� ���)
    // ...�� �������, �� ����� ������ �մ� �� 6���� �ٽ� ����
    //Left
    // x�� ����, z�� �հ� ��
    // * ����� ���� ���ظ� ã�Ƽ� �����ϸ� �ȴ�
    a = VP._14 + VP._11; // �� �� �� ��
    b = VP._24 + VP._21; // �� �� �� ��
    c = VP._34 + VP._31; // �� �� �� ��
    d = VP._44 + VP._41; // �� �� �� ��
    planes[0] = XMVectorSet(a, b, c, d); // DX ���� �Լ��� ���� ���� ���� (2���� ���)
                                         // ��İ��� �ƴ϶� ���� ����� "��"�� ���ϴ� �� �����̶� DX �Լ��� ����

    //Right
    // x�� ����, z�� �հ� ��
    a = VP._14 - VP._11; // �� �� �� ��
    b = VP._24 - VP._21; // �� �� �� ��
    c = VP._34 - VP._31; // �� �� �� ��
    d = VP._44 - VP._41; // �� �� �� ��
    planes[1] = XMVectorSet(a, b, c, d);

    //Bottom
    // x�� �Ʒ�, z�� �հ� ��
    // * �� �İ� ���� ���Ұ� ���� ���δ� : ���� ���õ� ���Ҵ� ������ ��� ���ؿ� ���� ���
    // -> �������� ����? ����� (�츮�� ������ �𸥴�)
    // -> �ϱ�? ���� �� ���̵��� ���輺�� �� ũ�� (�ܿ�� �͵� ���絥 Ʋ���� �� ����)
    // -> Matrix, Elements, 4x4 ���� Ű����� ���� ���� ������ ã���� ���� ������ ��)
    // -> ã�Ƴ� ���ڸ� ���� ���� 4������ ã�Ƽ� ���� �����ϴ� ���� �����ڿ��Դ� �� �߿��ϴ�
    a = VP._14 + VP._12; // �� �� �� ��
    b = VP._24 + VP._22; // �� �� �� ��
    c = VP._34 + VP._32; // �� �� �� ��
    d = VP._44 + VP._42; // �� �� �� ��
    planes[2] = XMVectorSet(a, b, c, d);

    //Top
    // x�� ��, z�� �հ� ��
    a = VP._14 - VP._12; // �� �� �� ��
    b = VP._24 - VP._22; // �� �� �� ��
    c = VP._34 - VP._32; // �� �� �� ��
    d = VP._44 - VP._42; // �� �� �� ��
    planes[3] = XMVectorSet(a, b, c, d);

    //Near
    // ������ �ִ� �� �̶�� ���� ���۸�
    // "���� ����" Ȥ�� "ī�޶��� ��ġ"
    a = VP._14 + VP._13; // �� �� �� ��
    b = VP._24 + VP._23; // �� �� �� ��
    c = VP._34 + VP._33; // �� �� �� ��
    d = VP._44 + VP._43; // �� �� �� ��
    planes[4] = XMVectorSet(a, b, c, d);

    //Far
    // �ϴ� ��ġ�� �� ���� �ִ� �� �� �� ����� �����
    // -> ���⿡�� � �Ÿ��� �ְ� �Ǹ�? -> �װ� �� ����ü�� �Ѱ�(����)
    // * �� �� �� �� ������ ������ ��������ϱ�
    a = VP._14 - VP._13; // �� �� �� ��
    b = VP._24 - VP._23; // �� �� �� ��
    c = VP._34 - VP._33; // �� �� �� ��
    d = VP._44 - VP._43; // �� �� �� ��
    planes[5] = XMVectorSet(a, b, c, d);

    // �� ����ȭ
    // ���� ũ�⸦ ���� ũ��� �ٽ� ����
    // -> Far ���� ũ��(�� �Ÿ�)�� ���� ����
    // -> Far�� �� Ŀ���⸦ �ٶ�� �߰��� �� Far�� �Ÿ��� �÷��ְų�, ���� �ٸ��� �����ؾ� �Ѵ�

    FOR(6)
        planes[i] = XMPlaneNormalize(planes[i]);

    // ������� ����, ī�޶�� ���� ������ ���� �ȴ�

    // 1. ���� ������ ���� ����ü (�Լ� ������ ������ ����)
    // 2. �ش� ����ü�� ���� 6������ �����ϴ� ������ ��� 6�� (��� �����)
    //    ���⼭ ���� planes[0]���� [5]������ �ٸ� ������ ȣ���ϰų�, �Լ��� ���ؼ�
    //    ����ü �浹�� Ȱ���� �� �ִ�
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
    writer->Bool(isLookAtTargetX);
    writer->Bool(isLookAtTargetY);

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
    isLookAtTargetX = reader->Bool();
    isLookAtTargetY = reader->Bool();

    delete reader;
}

bool Camera::ContainPoint(Vector3 point)
{
    // ����ü �浹 �Ǻ� �Լ�

    // ����ü �ȿ� ��ġ�� �ִ��� �Ǻ��� �ϸ� �Ǳ� ������ ȣ���� ��� �ϵ� �������

    // ���� ������ ����
    // 1. Scene       : ����ü �ȿ� Scene ��ü�� ������ ����, �ƴϸ� ���� ����
    // 2. GameManager : ����ü �ȿ� ������ ��� ��ü�� ������ ����, �ƴϸ� ����
    // 3. Environment : �� ���� ...���� ����
    // 4. ��ü ��ü    : �����ΰ� ����ü �ȿ� ���� ��, ���� ��

    // -> �ٸ� ����ȭ��, ���߻��� ���Ǹ� ���ؼ� �Ϲ������� 1 ~ 2 ������ ��ġ�� ����ü ���� ȣ���� �Ѵ�
    //    ���� 4, �׸��� ���� ���� 3 (���� �ش����� ����ü ��� ����)

    // �ݺ��� ������
    FOR(6)
    {
        // ���� ����� ������ ��ġ(�Ű������� ����) ������ ���踦 �������� ���
        // -> ������ ���ϸ�, �鿡�� ������ ��ġ�� ������ �����ٰ� �����ϰ�
        //    �ش� ������ ���ͷ� �����ϴ� ��
        // -> �� ������ ���ϸ� "���� ���� ��ó�� �������� ��, ��ġ�� �� ���� �ִ°�?
        Vector3 dot = XMPlaneDotCoord(planes[i], point); // DX ���� �Լ� (�̰� DX �� �Լ��� ���� ���ϴ�)

        // ���ظ鿡 ���� ������ ������ �������? -> ���� ���̶�� ���� ��, ��ġ�� ���Ͽ� �ִ�
        // = ����� ���� �ȿ� ����
        if (dot.x < 0.0f)
            return false;
    }

    // ������� ���� ����ü�� ���� ���� 6���� �� �ȿ� ������ ��ġ�� ���� �ִ�
    return true;
}
