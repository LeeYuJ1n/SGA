#pragma once

class Transform
{
public:
    Transform();
    ~Transform() = default;

    void UpdateWorld();
    void RenderUI();

    // 트랜스폼의 행렬 정보를 바깥에서 볼 수 있도록 하는 겟터들

    // 만들어진 기준 방향을 정규화해서 반환하는 함수
    // 정규화 : 벡터의 크기 정보를 무효화하는 대신, 방향과 각도 정보를 만든다
    Vector2 Right() { return right.GetNormalized(); }
    Vector2 Up() { return up.GetNormalized(); }

    // 만들어진 전체 세계에서의 위치와 크기 (방향은 위에 기준 방향을 보면 되니까)
    Vector2 GlobalPos() { return globalPosition; }
    Vector2 GlobalScale() { return globalScale; }

    // 트랜스폼의 부모(결속된 상위 트랜스폼 정하기)
    // *하위는 필요없는가? -> 하위는 각 클래스에서 따로 변수 지정하면 되니까...
    void SetParent(Transform* transform) { parent = transform; }
    void SetPivot(Vector2 pivot) { this->pivot = pivot; } //축도 필요하면 정하기

    // 활성화
    bool& Active() { return isActive; }

    // 상대적인 트랜스폼 정보 도출
    // 위에 있는 함수는 절대, 여기서는 상대
    // 이 둘의 차이는 트랜스폼이 다른 트랜스폼의 자식일 때 (다른 쪽이 부모일 때) 발생
    // 예를 들면 탱크의 포탑의 경우, 절대 위치는 탱크의 위치. 하지만 상대 위치는? 탱크 바로 위(=움직이지 않았음)
    Vector2& Pos() { return localPosition; }
    Float3& Rot() { return localRotation; }
    Vector2& Scale() { return localScale; }

protected:
    string tag;

    // 상대 위치, 상대 회전, 상대 크기
    Vector2 localPosition;
    Float3 localRotation = { 0, 0, 0 };
    Vector2 localScale = { 1, 1 };

    bool isActive = true;    

    Matrix world;

    Transform* parent = nullptr; // 트랜스폼에 직접 연결된 다른 트랜스폼이 있을 경우 해당 트랜스폼의 포인터

private:

    Matrix S, R, T;
    Matrix P, IP;
    Vector2 pivot; //축 정보

    Vector2 right, up; //오른쪽, 위 방향을 가리킬 벡터
    Vector2 globalPosition, globalScale; //글로벌 월드 (모든 사물이 모이는 곳) 에서의 위치, 크기 정보

    XMFLOAT4X4 matWorld;
    
};