#include "Framework.h"

// ī�޶� ���� : ������ ������ ���� Ʈ�������� ����, �� ��ġ�� ����Ʈ�� ����� �ǵ���
// �⺻�� winAPI ���� ��� : ���̴� ī�޶�(ī�޶� ����) ����ϴ� ���� �ƴ϶�
//                          ����� �Ȱ��� ����Ʈ�� �ϴ� �ͻ� (���� ���� ��ġ�� �޶�����)

//                         -> ����, ���� ī�޶� �ٷ� �Ŵ����� ����� �ϰų� �ڵ����� ���̴� ���� �ƴ϶�
//                            Environment���� ������ ����� �Ѵ� (�׷��� Environment�� ���� �ڵ����� ���)

Camera::Camera()
{
    //���� ����
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
    // �������� ������ �ȷο�ķ���� ����, �ƴϸ� ����ķ���� ����
    if (target != nullptr) FollowMode();
    else FreeMode();

    //�� ���� (��� �� ���ΰ�?)
    SetView();
}

void Camera::SetView()
{
    UpdateWorld(); // Ʈ���������μ��� ���� ������Ʈ (ī�޶�� ��� ��� �ִ°�)

    view = XMMatrixInverse(nullptr, world);

    viewBuffer->Set(view);
    viewBuffer->SetVS(1); //���� ������� ����� �� ������ ���� ����
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

