#pragma once

class ShaderScene : public Scene
{
public:
	ShaderScene();
	~ShaderScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void Init() override;
	virtual void Quit() override;

private:
	// �� �׸��� ���� �ε� �����ϴ� ��

	// ���� �׸� (��� ���)
	Quad* quad;

	// ���ͷ� �׸��� ���� ��� �ش� �ؽ�ó�� �ʿ�
	Texture* secondMap; // �� ��° ����

	// ȭ�� ������ �ְ�ޱ� ���� ���۵��� �ʿ��ϴ�
	// -> �׷��� ���� ������� ��ü�� ��, ���� ���� ���ڰ� �ַ� ���̰�
	//    + �ڷ� ���뵵 �ʿ信 ���� �ٲ� �� �ִ�
	//    -> �ڷ����� ������ ������, ���� �������� �ǹ̴� ��쿡 ���� �޶��� ���� �ִ�
	//    -> �׳� �ڷ����� ������ ���۰� �ִٸ� �̷� ��쿡�� �� ȣ���� ������ �� �ִ� (�ǹ̵� ��Ȯ)
	
	// ConstBuffer* firstValueBuffer;
	// ConstBuffer* secondValueBuffer; // �ڷ����� �� ������ ���� (���뼺 ������ ����, ����, ���� ����)

	IntValueBuffer* intValueBuffer;     // ������ �޴� ����
	FloatValueBuffer* floatValueBuffer; // �Ҽ��� �޴� ����
};

