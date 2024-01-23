#include "Framework.h"

// ī�޶� ���� :
// 1. ������ ������ ���� Ʈ�������� ����, �� ��ġ�� ����Ʈ�� ����� �ǵ���
// 2. �⺻�� winAPI ���� ��� : ���̴� ī�޶�(ī�޶� ����) ����ϴ� ���� �ƴ϶�
//                             ����� �Ȱ��� ����Ʈ�� �ϴ� �� �� (���� ���� ��ġ�� �޶�����)

//                             -> ����, ���� ī�޶� �ٷ� �Ŵ����� ����� �ϰų� �ڵ����� ������ ���� �ƴ϶�
//                                Environment���� ������ ����� �Ѵ� (�׷��� Environment�� ���� �ڵ����� ���)

Camera::Camera()
{
    // ���� ����
    viewBuffer = new MatrixBuffer();
    viewBuffer->SetPS(1);
    // 1 : 0 �ƴ�, 2 �ƴ� = "������ ����"���� ���еȴ�
    // ui�ʹ� ���� = VS�� �ٸ� �� �־ (���� ó���� �ٸ� �� �־) ��Ÿ ���̴�, ��� ������ �Ϻ� ������ ����...

    tag = "Camera"; // ���߿� ��ü������ (�����̵� �и���) �ʿ��� ��� �±׷ε� ������ �� �ֵ���
}

Camera::~Camera()
{
    delete viewBuffer;
    // ǥ���� ����� ������, ������ �ٸ� ������ �����ǰ� ��(�ų� ���ӿ��� ���������� �������� ��)�� ��찡 99%
}

void Camera::Update()
{
    // �������� ������ Follow-Cam���� ����, �ƴϸ� Free-Cam���� ����
    if (target != nullptr) FollowMode();
    else FreeMode();

    // �� ���� (��� �� ���ΰ�?)
    SetView();
}

void Camera::SetView()
{
    UpdateWorld(); // Ʈ���������μ��� ���� ������Ʈ (ī�޶�� ��� ��� �ִ°�)

    view = XMMatrixInverse(nullptr, world); // XMMatrixInverse : ��ġ�� ������ ��¤���� ���� ����

    viewBuffer->Set(view);
    viewBuffer->SetVS(1); // ���� ������� ����� �� ������ ���� ����
}

void Camera::FollowMode()
{
    // TODO : �������� �����, �� �������� �ൿ ��Ÿ���� �������� �׶� �ۼ�
}

void Camera::FreeMode()
{
    // ī�޶� ���� �̵�
    if (KEY_PRESS('T')) Pos().y += speed * DELTA;
    if (KEY_PRESS('G')) Pos().y -= speed * DELTA;
    if (KEY_PRESS('F')) Pos().x -= speed * DELTA;
    if (KEY_PRESS('H')) Pos().x += speed * DELTA;
}

