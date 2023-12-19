#pragma once
class DijkstraScene : public Scene
{
public:
    //�ʼ�4��
    DijkstraScene();
    ~DijkstraScene();

    virtual void Update() override;
    virtual void Render() override;

    //�ɼ� �� �ʱ�ȭ�� ����Ʈ����
    virtual void Init() override;
    virtual void PostRender() override;

private:

    Dijkstra* dijkstra;
    Tank* tank;

};

