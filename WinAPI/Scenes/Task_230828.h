#pragma once
#include "Construction.h"                // ��ü���� ��
#include "Construction_Building.h"       // �ǹ� ��ġ
#include "EventMap_1.h"                  // �ǹ� ���� 1

class Task_230828 : public Scene
{
public:
	Task_230828();     // ������
	~Task_230828();    // �Ҹ���

	Construction* CTR;          // ��ü���� ��
	Construction_Building* CTB; // �ǹ�
	EventMap_1* EMap1;

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	// HBITMAP �� �÷��̾� ĳ����
	HBITMAP character1;       // �÷��̾� ���ĵ� ���
	HBITMAP character1WALK;   // �÷��̾� �ȱ� ���
	HBITMAP character1ATK;    // �÷��̾� ���� ���
	HBITMAP character1DEAD;   // �÷��̾� �״� ���

	// HBITMAP �� ������
	HBITMAP background;      // ���� ���
	HBITMAP Building1;       // �ǹ�1
	HBITMAP BuildingTile;    // �ǹ� �ٴ�
	HBITMAP BuildingWall;    // �ǹ� ��
	HBITMAP Road;            // ��
	HBITMAP Long_Road;       // ���η� �� ��

	HDC memDC;
	HDC stretchDC;

	POINT characterPosition;
	Rect* characterArea;

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

	// ********************************************************************

	// ��ȣ�ۿ��� ���� �簢��
	Rect* platform[6];
	bool Collision = false;

	// �浹�� ������ �˱� ���� ������ �Լ�
	int directionForm_Code; // �� �� �浹 ������ �ڵ�ȭ�ؼ� ������, ��Ȯ�ϰ� ���� ����

	enum COL_DIRECTION // �� ���� ���� �ǹ̸� �������� �Ἥ ���߿� �˾ƺ��� ���� ���� ��
	{
		NONE,
		LEFT,
		RIGHT,
		ABOVE,
		BENEATH
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

		if (_right - _left > _bottom - _top) // ���� (����) �簢���� ���ΰ� ���κ��� ũ��
		{
			collideHorizontal = false; // �������� �浹�ߴ� (�� �Ʒ� ��ġ = �׷��� �������� �����ϴ�)
		}
		else collideHorizontal = true; // ���� �浹 (���� ������ ��ġ)

		if (collideHorizontal) // ���� �浹�̴�
		{
			// ���� ���� ���г��� ���ؼ� �� ���ʿ� �ִ� ���� ����
			if (rect_one->Left() < rect_two->Left())
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
				if (_bottom - _top > 90) return NONE; // �浹 ���� ũ�Ⱑ Ŀ�� ���� ũ��

				return ABOVE; // ��
			}
			else
			{
				return BENEATH; // �Ʒ�
			}
		}
	}

	// �� ����� �ޱ� ���� ���� �߰� (�ɼ�)
	COL_DIRECTION singleDir; // �� ���� ĳ���Ͱ�, �ϳ��� ���ǿ� ���� ������ ���Ⱚ
	BLENDFUNCTION blend;     // ���� ���� ������
	// BLENDFUNCTION : �׸� ����(Ư�� ���� ��)�� ���� ������ ����ü

	// ********************************************************************
};

