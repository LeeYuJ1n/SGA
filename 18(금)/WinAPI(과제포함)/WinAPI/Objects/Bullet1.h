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
		// refresh : update와 같은 뜻 ,보통은 "새로 고침"

		if (isMove == false) return ; // 움직이지 않을 거면 작동하지 않음

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

