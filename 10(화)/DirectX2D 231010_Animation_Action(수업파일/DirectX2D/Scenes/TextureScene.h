#pragma once

// ���� �� �� : ���� ���� �ݶ��̴��� �̿��ؼ� �浹 ��ȣ�ۿ� ������

// -> �浹�� ����Ű�� ���ؼ��� �ݶ��̴�, �Ѿ�, �׸���... �¾��ִ� �ʵ� �ʿ��ϴ�!

class TextureScene : public Scene
{
public:
    TextureScene();
    ~TextureScene();
        
    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void Init() override;
    virtual void Quit() override;

private:

    Plane* plane;

    //�¾��� ���� ������
    //Enemy* enemy; //���� ���� �ʿ䰡 ���� (�Ŵ��� ���)

    vector<Bullet*> sceneBullets;

    Button* tmpButton;
};