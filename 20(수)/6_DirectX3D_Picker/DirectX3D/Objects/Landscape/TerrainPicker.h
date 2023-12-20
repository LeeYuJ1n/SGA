#pragma once

class TerrainPicker : GameObject
{
    // 클래스 목적 : 마우스로 터레인을 찍으면 터레인의 좌표를 알 수 있도록 하기 위한
    //              클릭 테스트용 지형

private:
    typedef VertexUVNormalTangent VertexType; //이 클래스의 정점 타입은 Z축 계산을 감안한 정점입니다.
    //위 재지정이 왜 굳이 필요한가?
    //나중에 VetrexType이라는 지정 인터페이스를 공유하면서 다른 클래스에서도 비슷한 코딩이 가능해서
    const float MAX_HEIGHT = 20.0f; // 최대 높이 미리 정해놓기 (터레인처럼)

public:
    TerrainPicker();
    ~TerrainPicker();

    void Update();
    void Render();
    void RenderUI();

    Vector3 Pick(); // 찍는 행동

private:
    //기본 메쉬 혹은 높이 맵에서 구체적인 지형 만들기
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();

    //터레인이니까 가로, 세로
    UINT width;
    UINT height;

    //Mesh<VertexUVNormalTangent>* mesh;
    //위 코드 대신, 재지정된 정점 타입을 적용한 간단 선언으로
    Mesh<VertexType>* mesh;

    //터레인이니까 높이맵 미리 선언 (최초 구현 때는 아마 안 쓰겠지만)
    Texture* heightMap;

    Vector3 pickingPos; // 찍고 있는 좌표
};

