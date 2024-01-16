#pragma once

// 모델 연산에 필요한 각종 데이터 구조체 및 기초 클래스 집합

//전역 정점 : 3D 모델 추출, 구현 등에 사용될 정점 타입
typedef VertexUVNormalTangentBlend ModelVertex;

//전역 구조체 : 3D 모델을 추출한다면 어디서든 여기서부터 호출할 수 있도록
// -> 이렇게 만들었다가 나중에 너무 번잡하면 네임스페이스를 따로 만들면 된다
//    * 네임스페이스 : 명령어 집합을 따로 묶어둔 것 (예 : std, std::cout)

// 형태를 담기 위한 구조체
struct MeshData
{
    string name; //이 형태의 이름
    UINT materialIndex; // 사용된 매티리얼 데이터

    //메시의 진짜 데이터 = 정점을 갖기 위한 벡터들
    vector<ModelVertex> vertices;
    vector<UINT> indices;
};

//노드를 담기 위한 구조체 (노드 : 데이터 단위, 모델에 이 이름이 쓰이면 보통은 관절, 부위 등을 나타낸다)
struct NodeData
{
    int index; //해당 모델 안에서 이 노드는 몇 번째인가? 혹은 어떻게 지칭되는가?
    string name; //노드의 이름
    int parent; //부모 데이터 (부모도 노드일 경우 int로 지칭 가능)
    Matrix transform; //매트릭스 데이터
};

// 뼈대를 담기 위한 구조체 (뼈대 : 3D 모델에서 노드 간의 관계나, 관절의 움직임을 나타내기 위한 기준)
struct BoneData
{
    int index; //뼈대의 지칭
    string name; //뼈대의 이름
    Matrix offset; //뼈대의 보정치
};

// 정점의 가중치를 계산하고 또 저장하기 위한 구조체
struct VertexWeights
{
    UINT indices[4] = {}; //뼈대의 인덱스 예약
    float weights[4] = {}; // 가중치 초기화

    // 가중치 주기
    void Add(UINT& index, float& weight)
    {
        //for (int i = 0; i < 4; ++i)
        FOR(4) //프레임워크 헤더에서 따온 매크로 적용
        {
            if (weights[i] == 0)
            {
                indices[i] = index; //인덱스를 받아서 전달하고
                weights[i] = weight; //가중치를 주고
                return; //끝
            }
        }
    }

    //결과 정규화
    void Normalize()
    {
        float sum = 0;

        FOR(4)
        {
            sum += weights[i]; //가중치 다 더하기
        }

        FOR(4)
        {
            weights[i] /= sum; //총합으로 또 나누기
        }
        // 여기까지 오면 나오는 결과 : 모든 정점이 갖고 있던 "가중치" 균일화
    }
};

// 중심 트랜스폼 = 키 프레임 (동작 내 기준 자세) 구성요소
struct KeyTransform
{
    Float3 scale; //크기 (S)
    Float4 rot; // 회전 (R)
    Float3 pos; // 위치 (T)

    // 모두 곱하면 해당 트랜스폼의 행렬공간 도출
};

// 중심형상, 혹은 "프레임의 키" = 애니메이션이 있는 경우 몇 번째 프레임인가?
//                              혹은, 해당 프레임에서 이 모델은 지금 어떤 모양인가?
struct KeyFrame
{
    string boneName; // 이 프레임을 적용할 뼈대
    vector<KeyTransform> transforms; //프레임이 적용될 트랜스폼들
};

// 클립의 구성요소 : 프레임을 모으거나 나누어서 만들어진 "동작"을 담기 위한 구조체
struct ClipNode
{
    aiString name; // 애셋 임포트 라이브러리에서 사용된 자료형을 적용 (불러올 때 애셋 임포트를 쓸 테니까)
    vector<KeyTransform> transforms; // 트랜스폼
};

// 클립 : 위에서 만든 구조체로 구성된 "동작"
struct Clip
{
    string name; // 동작의 이름, 지칭

    UINT frameCount; // 사용된 프레임
    float tickPerSecond; //프레임 재생 속도 (tick : 프레임의 다른 이름, 동작 재생 중 한 프레임, 혹은 한 순간을 구분해서 지칭하는 용어)

    vector<KeyFrame*> keyFrame; // 인스턴스로 생성된 키 프레임을 모아놓은 벡터

    // 모아놓은 프레임 트랜스폼을 속도에 따라 바꾸어 가며 재생하면 -> 현재 D3D 환경에서의 애니메이션
    //                                                           엔진에서도 구현 방법은 달라도 원리는 대략 비슷
};

// 클립을 수행하는/수행할 트랜스폼
struct ClipTransform
{
    Matrix transform[MAX_FRAME][MAX_BONE];
};

// 여기까지 오면 : 형태를 만들고, 형태의 구조를 만들고, 형상을 모아서 동작까지 만든 것
// -> 이 구조체들을 모델의 자료로 사용하면 된다