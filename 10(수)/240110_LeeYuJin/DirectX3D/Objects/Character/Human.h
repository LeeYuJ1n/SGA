#pragma once

class Human : public ModelAnimator
{
public:
	Human();
	~Human();

	void Update();
	void Render();
	void GUIRender();

private:
	// TODO :
	// ���߿� �ڽ� ��ü�� �ٰų� ���� ���� ����� ����� �ڵ� �߰�
	// �ڽ� ��ü : ����, �賶, ��ź ����, �տ� �� ���� ��
	// ���� ���� ��� : �߼Ҹ� üũ�� ���� "�� ��" Ȥ�� ���⸦ ��� ���� "�� ��"

	// �� : �������븦 ����� �����, �տ� ���
	Crowbar* crowbar;    // �������� (����)
	Transform* mainHand; // �ַ� ���� �� (������ ��������)

private:
	void Control();
	void Jump(); // ������ ��ǥ����(���� 0)�� ��ġ ���� �� ó�� ���� OK
	             // Ȥ�� �����ϴ� �ͷ��� ������ Ȥ�� ��� �Ŵ����� �����ϰų�

	// �����ӿ� ������ 

	// �ϴ��� ���� (�ᵵ ����, �����ص� ����)
	float moveSpeed;
	float jumpVelocity;
	float jumpForce;
	float gravityMult;

	bool isJump;

};

