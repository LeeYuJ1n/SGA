#pragma once

class Stage1;
class Stage2;
class Hidden1;

class FIrstDHouse
{
public:
	FIrstDHouse();
	~FIrstDHouse();

	void Update();
	void Render();

private:
	Quad* background;   // ��׶��� �̹���
	Button* esterEgg_Btn; // ��ȭ�� ���� �̽��Ϳ��� ��ư
	Button* start_Btn;    // ���� ������ ���� ��ư
	// Button* option_Btn;   // ���� �ɼ� ��ư
	Stage1* stage1;
	Stage2* stage2;
	Hidden1* hidden1;
};

