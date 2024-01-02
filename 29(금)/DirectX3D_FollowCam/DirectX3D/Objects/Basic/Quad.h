#pragma once

class Quad : public GameObject
{
    // 3D용으로 다시 만들 2D 사각형 (쿼드) 클래스
    // 3D용 쿼드의 주요 차이 : 메시를 따로 만들 것인가 아닌가
    //                        정점의 구성이 어떻게 되는가
    //                        + 텍스처 등의 데이터가 이제 매티리얼=부모로 옮겨감

private:
    //정점의 구성을 재정의
    typedef VertexUV VertexType;

public:
    Quad(Vector2 size);
    Quad(wstring file); //UV 설정 등은 부모에서 진행
    ~Quad();

    void Render();

private:
    void MakeMesh(); // 3D에 맞추어 함수 명칭 변경

protected:
    Vector2 size; // 크기 정보 따로 저장 (부모 세팅이나 자기 크기 변경 필요한 경우 사용)

    Mesh<VertexType>* mesh;
};