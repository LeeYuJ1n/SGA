#pragma once

class EventMap_1 : public Scene
{
public:
	EventMap_1();
	~EventMap_1();

	void Update() override;
	void Render(HDC hdc) override;

	// HDC
	HDC memDC;
	HDC stretchDC;

	HBITMAP EventMap1; // �ǹ� �ٴ�

	// HBITMAP �� �÷��̾� ĳ����
	HBITMAP character1;       // �÷��̾� ���ĵ� ���
	HBITMAP character1WALK;   // �÷��̾� �ȱ� ���
	HBITMAP character1ATK;    // �÷��̾� ���� ���
	HBITMAP character1DEAD;   // �÷��̾� �״� ���

	POINT characterPosition;
	Rect* characterArea;
	Rect* EventMap1Area;

	int actCode; // 0 : �� �ֱ�, 1 : �ȱ�
	int actIndex1;
	int actIndex1Walk;
	int actIndex1Run;
	int actIndex1Atk;

	bool isReversIndex1;
	bool isReversIndex1Walk;
	bool isReversIndex1Run;

	bool isLeft = false; // ������ ���� �ִ°�? (true : ������ ���� �� / false : �������� ���� ��) 
	bool isAtk = false;  // ���� ���ΰ�? (true : ���� �� / false : ������ �� �ϴ� ��)

	int lastIndex1 = 4;
	int lastIndex1Walk = 5;
	int lastIndex1Run = 5;
	int lastIndex1Atk1 = 4;

	float animationSpeed;
	float walkSpeed = 10.0f;

	float currentTimeElapsed; // ���� ��� �ð�
	float interval;           // �ð� ����

	float moveSpeed = 10.0f;

	// ���� ����
	Rect* platform;
	bool Collision = false;

	// �浹�� ������ �˱� ���� ������ �Լ�
	int directionForm_Code; // �� �� �浹 ������ �ڵ�ȭ�ؼ� ������, ��Ȯ�ϰ� ���� ����

	enum COL_DIRECTION // �� ���� ���� �ǹ̸� �������� �Ἥ ���߿� �˾ƺ��� ���� ���� ��
	{
		NONE,     // defualt
		LEFT,     // ����
		RIGHT,    // ������
		ABOVE,    // ��
		BENEATH   // �Ʒ�
	};

	// ���� �ִ� �������� �Ἥ �浹 ������ �� �� �ִ� ������ ������
	// �̵��� �浹 ���°� ������ ����, ���� ������ ������ �Ѵ�
	COL_DIRECTION GetCollisionDirection(Rect* rect_one, Rect* rect_two)
	{
		float _left = rect_one->Left() > rect_two->Left() ? rect_one->Left() : rect_two->Left();
		float _right = rect_one->Right() < rect_two->Right() ? rect_one->Right() : rect_two->Right();
		float _top = rect_one->Top() > rect_two->Top() ? rect_one->Top() : rect_two->Top();
		float _bottom = rect_one->Bottom() < rect_two->Bottom() ? rect_one->Bottom() : rect_two->Bottom();

		// �� ������ ����, �� �簢���� ��ġ�� ���� �� �ִ��� ���� ���� = �������� ���� �� �ִ�

		// �׸��� �������� ����� �Ǻ��ؼ�

		bool collideHorizontal;

		if (_right - _left > _top - _bottom) // ���� (����) �簢���� ���ΰ� ���κ��� ũ��
		{
			collideHorizontal = false; // �������� �浹�ߴ� (�� �Ʒ� ��ġ = �׷��� �������� �����ϴ�)
		}
		else collideHorizontal = true; // ���� �浹 (���� ������ ��ġ)

		if (collideHorizontal) // ���� �浹�̴�
		{
			// ���� ���� ���г��� ���ؼ� �� ���ʿ� �ִ� ���� ����
			if (rect_one->Left() > rect_two->Left())
			{
				return LEFT; // rect_one�� rect_two�� �����̴�
			}
			else
			{
				return RIGHT;
			}
		}
		else
		{
			if (rect_one->Bottom() < rect_two->Bottom())
			{
				if (_bottom - _top > 10) return NONE; // �浹 ���� ũ�Ⱑ Ŀ�� ���� ũ��

				return ABOVE; // ��
			}
			else
			{
				return BENEATH; // �Ʒ�
			}
		}
	}

	// �� ����� �ޱ� ���� ���� �߰� (�ɼ�)
	COL_DIRECTION singleDir; // �� ���� ĳ���Ͱ�, �ϳ��� ���ǿ� ���� ������ ���Ⱚ// BLENDFUNCTION : �׸� ����(Ư�� ���� ��)�� ���� ������ ����ü
};

