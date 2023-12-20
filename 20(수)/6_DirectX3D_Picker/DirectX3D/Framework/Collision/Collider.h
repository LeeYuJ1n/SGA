#pragma once
#include "Objects/Basic/GameObject.h" //충돌체 헤더를 먼저 읽었을 경우 게임오브젝트 내용을 참조하기 위함 (상호 참조의 경우)

// 2D(모니터)-3D(실제 앱 속 행렬공간) 사이의 입출력 관계를 연산하기 위한 "광선"
struct Ray
{
    // 광선에 들어가야 하는 것
    // 1. 이 광선은 어디서부터 왔는가?
    // 2. 이 광선은 어디로 가는가?

    Vector3 pos;
    Vector3 dir;

    Ray() {}
    Ray(Vector3 pos, Vector3 dir) : pos(pos), dir(dir)
    {
        //this->pos = pos;
        //this->dir = dir;
    }
};

// 광선이 존재한다면, 해당 광선이 물체에 부딪친 정보도 있을 것이다
// 해당 정보를 표시하기 위한 별도 구조체

struct Contact //접점
{
    string tag; //접점의 이름
    //↑ 충돌 판정을 비롯한 레이캐스팅 결과 반환이 일어났을 때, 해당 경우가 필요한 상황인지 알려면
    // 1. 충돌에 개입한 물건의 이름, 2. 광선의 현재 정보가 사용된다
    // 그런데 1, 2만으로 충분하지 않은 경우 (물건에 이름이 없고, 광선의 정보 대상이 물체 간 상호작용일 때)
    // 보험의 역할을 하기 위해 태그 변수가 꼭 필요하다

    // 접점의 세부 항목 : 어디에 부딪쳤는가(충돌점),
    // 여기 부딪치기까지 광선이 얼마나 왔는가(거리)

    Vector3 hit;
    float distance; // 거리는 "그냥 숫자"라서 그냥 숫자(=스칼라)로 표기
};

// 광선과 접점을 활용하는 단순한 형태의 충돌체 클래스 만들기
// + 인터페이스로 만들어서 호환성 높이기

//class Collider : public Transform // 2D에서의 방식, 기본형에서 속성을 이어받는 트리 구조
class Collider : public GameObject  // 기본형(트랜스폼과 기본 게임 개체)이 있고, 거기에 새로운 속성을 부여하는 컴포넌트 구조
{
protected: //상속받은 실제 충돌체와 공유 가능하도록
    
    enum class Type
    {
        //RECT, CIRCLE // 직사각형, 원 : 2D의 명칭
        //CUBE, SPHERE // <- "원시 형태"(프리미티브 모델)의 3D 명칭
        BOX, SPHERE, // 흔히 쓰이는 3D 충돌체의 명칭들
    };

    const float PUSH_SPEED = 500.0f;

public:
    Collider();
    ~Collider();

    void Render(); //렌더

    bool IsCollision(Collider* collider); //충돌 판별

    // 타입별 충돌 세부 판별 각각 만들기 (인터페이스)
    // 
    // 광선과 충돌체 (기본 충돌 관계 : 점 충돌이나 선 충돌과 같다)
    virtual bool IsRayCollision(IN Ray ray, OUT Contact* contact = nullptr) = 0;
    // 매개변수에 쓰인 IN과 OUT : 실제 코드는 아니고, 그냥 나중에 봤을 때 각 매개변수의 역할을 잘 기억하기 위한 메모
    // IN Ray ray : 함수에 광선 정보"를" 쓰겠다 // OUT Contact* contact : 이 함수의 결과는 별도의 반환형은 없지만 이 구조체는 담겠다

    virtual bool IsSphereCollision(class SphereCollider* collider) = 0;
    virtual bool IsBoxCollision(class BoxCollider* collider) = 0;

    // 렌더시에 충돌체 보이기 어떻게 설정할 것인가

    void SetColor(Float4 color) { material->GetData().diffuse = color; } // 색깔 지정
    void SetColor(float r, float g, float b)
    {
        material->GetData().diffuse = { r, g, b, 1 };
    }

    //렌더 토글
    void RenderOnOff() { isRender = !isRender; } // A = !A : bool 변수 참과 거짓 뒤집기
    static void RenderOnOffAll() { allRender = !allRender; } // 정적(전역)함수화 - 모든 렌더를 일괄통제 (상위옵션)
    void RenderLineToggle() { isRenderAsLine = !isRenderAsLine; }

protected:

    virtual void MakeMesh() = 0; // 트랜스폼의 메시 만들기 : 이번에는 충돌체가 직접

    Type type; //충돌체 실제 유형

    Mesh<Vertex>* mesh; // 정점으로 만든 모양 틀

    bool isRender; // 렌더 여부 (트랜스폼을 안 받는 대신 직접 만들기) : 렌더를 안 해도 충돌은 해야 할 수 있어서
    static bool allRender;

    bool isRenderAsLine = true;
};

