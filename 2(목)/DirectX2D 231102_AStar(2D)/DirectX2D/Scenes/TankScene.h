#pragma once

class TankScene : public Scene
{
    //�� Ŭ���� �ʼ� 4��

public:
    TankScene();
    ~TankScene();

    virtual void Update() override;
    virtual void Render() override;

    // + �ʿ��ϸ� �ɼ� (����Ʈ����, ��������, �̴Ͻÿ��̼�, ţ)
    virtual void Init() override; //���۰� ���ᰡ �ʿ��ϴٸ�
    virtual void Quit() override;

    virtual void PreRender() override; // ����Ʈ ���� ���� �߰� ����� �ʿ��ϴٸ�
    virtual void PostRender() override; //����� UI ǥ�� ���� �߰� �ȳ��� �ʿ��ϴٸ�

private:

    GameTileMap* gameTileMap; // Ÿ�� ������ ���� Ÿ�� ��ġ�� ���� ���� Ŭ����
    
    AStar* aStar; // �� ã�� �˰��� (�ٽ�)

    Tank* tank; //��ũ (�÷��̾�)
};

