#pragma once

class GameScene : public Scene
{
public:
    // �� ������
    GameScene();

    // �� �Ҹ���
    ~GameScene();

    // �� Scene Ŭ���� �⺻ �ɼ� 5����
    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render()  override;
    virtual void PostRender()  override;
    virtual void GUIRender()  override;

private:
    

private:
    // �� Background
    Model* background;

    // �� Character
    Naruto* naruto;
    // + �κ� �Ŵ���, + ���� �Ŵ���

    // �� BlendState
    // ���� ���� ���� : WinAPI�� ����-����-ȥ�� blt�� ������ ����
    //                   ������ ���� �����ְ�, ���İ��� �����ϰ�, �ֺ� �̹����� ȥ�����ش�
    BlendState* blendState[2];
    // BlendState : �̹��� ���� �̹����� ���׸� �� ����� ��� �������� �����ϴ� ��

    // �� SkyBox
    SkyBox* skyBox;
};

