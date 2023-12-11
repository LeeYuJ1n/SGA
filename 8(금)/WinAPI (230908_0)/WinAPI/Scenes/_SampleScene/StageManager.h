#pragma once

class StageManager : public PoolingManager, public Singleton<StageManager>
{
private:

    // ���� Ÿ�Ϸ� ������� ������ ������ ����� Ŭ����
    // Ǯ�� �Ŵ����� �Ӽ��� ��� : ���� ���� ������Ʈ�� �� ���� ���� �����ϴ� �Ŵ��� (���� �Ŵ��� ���� ��)

    //�������� �ʴ� ������ �����ϴ� ���
    enum TileType
    {
        //������ Ÿ�Ͽ� �׼�ó�� �ڵ带 �־ ����
        //0 : ���� (�̵� ����)
        //1 : ���� (���� �� ����)
        //2 : ������ ������
        //3 : ��ֹ� (����� �� ���ų�, �ε�ġ�� ����)
        NONE, GROUND, PICKUP, OBSTACLE
    };

    friend class Singleton;

    StageManager() = default;
    ~StageManager() = default;

public:
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    //���� �Ǻ� �� ���� �Լ�
    float GetGroundHeight(Vector2 pos);

    //�浹 �Ǻ� �Լ�
    void CollisionPickup(GameObject* object);
    bool CollisionObstacle(GameObject* object);

    //Ÿ�� ������ ����
    void LoadTileData(string file);

    //(��ũ���� �� ��) �ӵ�
    float GetSpeed() { return speed; }
    void SetSpeed(float value) { speed = value; }

    //�� ���������� (������) ���� ���ΰ�?
    bool IsPlay() { return isPlay; }

    //����
    void Play() { isPlay = true; }
    void Stop() { isPlay = false; }

    void SetAuto(bool value) { isAutoScroll = value; }

    float GetProcess() { return stageProceeded; }

private:
    void Move();
    void CreateTile();

private:
    UINT width, height;
    Vector2 tileSize;

    vector<vector<TileType>> tileData;

    UINT score = 0;

    bool isPlay = true;

    bool isAutoScroll = false;
    float speed = 0;

    float stageProceeded = 0;
};
