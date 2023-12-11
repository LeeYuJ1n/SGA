#pragma once
class Bullet1 : public Circle
{
public:
	Bullet1();
	Bullet1(Vector2 pos, float radius) : Circle (pos, radius)
	{
		
	}
	void SetStat(float _angle, float _speed)
	{
		angle = _angle;
		speed = _speed;
	}
	void RefreshLocation()
	{
		// refresh : update�� ���� �� ,������ "���� ��ħ"

		if (isMove == false) return ; // �������� ���� �Ÿ� �۵����� ����

		pos.x = pos.x + cos(angle) * speed;
		pos.y = pos.y + -sin(angle) * speed;
	}

	void Go() { isMove = true; }
	void Stop() { isMove = false; }
	float Angle() { return angle; }
	float Speed() { return speed; }

protected:
	bool isMove;

	float angle;
	float speed;
};

