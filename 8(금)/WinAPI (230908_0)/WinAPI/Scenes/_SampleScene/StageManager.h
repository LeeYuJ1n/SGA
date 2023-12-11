#pragma once

class StageManager : public PoolingManager, public Singleton<StageManager>
{
private:

    // 작은 타일로 만들어진 지형의 지도를 만드는 클래스
    // 풀링 매니저의 속성을 상속 : 여러 개의 오브젝트를 한 번에 만들어서 관리하는 매니저 (스폰 매니저 같은 것)

    //움직이지 않는 지형을 지정하는 방법
    enum TileType
    {
        //지형의 타일에 액션처럼 코드를 넣어서 구분
        //0 : 없음 (이동 영역)
        //1 : 지면 (밟을 수 있음)
        //2 : 집어드는 아이템
        //3 : 장애물 (통과할 수 없거나, 부딪치면 피해)
        NONE, GROUND, PICKUP, OBSTACLE
    };

    friend class Singleton;

    StageManager() = default;
    ~StageManager() = default;

public:
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    //높이 판별 및 전달 함수
    float GetGroundHeight(Vector2 pos);

    //충돌 판별 함수
    void CollisionPickup(GameObject* object);
    bool CollisionObstacle(GameObject* object);

    //타일 데이터 얻어내기
    void LoadTileData(string file);

    //(스크롤을 할 때) 속도
    float GetSpeed() { return speed; }
    void SetSpeed(float value) { speed = value; }

    //이 스테이지가 (게임이) 진행 중인가?
    bool IsPlay() { return isPlay; }

    //셋터
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
