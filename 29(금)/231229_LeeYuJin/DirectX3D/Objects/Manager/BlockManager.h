#pragma once

class BlockManager : public Singleton<BlockManager>
{
    // 블록 매니저 (큐브를 원형으로 하는 "블록" 관리자)

private:
    friend class Singleton;

public:
    BlockManager() = default;
    ~BlockManager();

    void Update();
    void Render();

    // 블록(들) 생성하기
    void CreateBlock(UINT width, UINT height);

    // 블록을 쌓아서 짓기 (결과 확인까지 하기 위해 boolean)
    bool BuildBlock(Cube* block);

    // 밀기
    void Push(Collider* collider);

    // 충돌 체크 (및 그 결과로 나온 대상)
    Cube* GetCollisionBlock();

    // 블록의 높이 재기
    float GetHeight(Vector3& pos);

private:
    list<Cube*> blocks; // <-삽입 삭제 결과 중간이 비어도 구조가 유지되도록 하기 위해서
};

