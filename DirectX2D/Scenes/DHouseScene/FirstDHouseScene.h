#pragma once

class FirstDHouseScene : public Scene
{
public:
	FirstDHouseScene();
	~FirstDHouseScene();

	virtual void Update() override;
	virtual void Render() override;

private:
	FIrstDHouse* firstdhouse;

	// ��Ƽ��Ʈ�� "ȭ�� ��ü:��� : ���� ����, �� ���� ���� ����� �޾ƾ� �Ѵ�
	// �׷��� ���� �ʰڴٸ� -> �� ��� ������ ������ �ؼ� �����ΰ� -> ó������ ���� �� ���̰�
	// ������ ���� �̺�Ʈ��� ����� ó������ �����ΰ� -> �� �ȿ��� image�� �����ٰ� ����ٰ�
};

