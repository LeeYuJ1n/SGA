#include "Framework.h"

SphereCollider::SphereCollider(float radius, UINT stackCount, UINT sliceCount)
    : radius(radius), stackCount(stackCount), sliceCount(sliceCount)
{
    type = Collider::Type::SPHERE;

    MakeMesh();
    mesh->CreateMesh();
}

bool SphereCollider::IsRayCollision(IN Ray ray, OUT Contact* contact)
{
    UpdateWorld();

    Vector3 P = ray.pos;
    Vector3 D = ray.dir.GetNormalized();

    Vector3 C = GlobalPos();
    Vector3 A = P - C;

    float b = Dot(D, A);
    float c = Dot(A, A) - pow(Radius(), 2);

    // 광원과의 관계가 위치관계의 역보다 크다
    // 위치관계가 광원과의 관계를 압도했다
    // = 광원과 구체가 만나는 지점이 있다

    if (pow(b, 2) >= c)
    {
        // 만나는 지점이 있으면 정보를 기록

        if (contact != nullptr)
        {
            float t = -b - sqrt(pow(b, 2) - c);

            contact->tag = tag;
            contact->distance = t;
            contact->hit = P + D * t;
        }

        // 함수는 true 반환

        return true;
    }

    // 여기까지 오면 광선이 진행을 하지만 구와는 만나지 못할 것
    // = 그러므로 거짓

    return false;
}

// 여기서
// 광선과 각 물체 : 체크
// 각 물체와, 자기와 같은 다른 물체끼리 충돌 : 체크
// ( 박스 VS 박스, 구체 VS 구체)

// 그러면 구체와 박스는? (2D 식이면 원과 박스)
// 기본은 같다 (WinAPI, DX2D와 같다)

// 1. 구체와 중심이 큐브 입장에서 면 안에 들어오면
// 2. 그렇지 못하면
// 3. 각각 박스의 크기, 혹은 정점과 구체로부터의 거리를 비교
// -> 차이가 있다면 이 계산들을 벡터로 하는 것뿐

bool SphereCollider::IsBoxCollision(BoxCollider* collider)
{
    // 그리고 우리가 기억하는 0번째
    // : 박스와 구체가 충돌하면 해당 
    return collider->IsSphereCollision(this);
}

bool SphereCollider::IsSphereCollision(SphereCollider* collider)
{
    float distance = Distance(GlobalPos(), collider->GlobalPos());

    return distance <= (Radius() + collider->Radius());
}

void SphereCollider::MakeMesh()
{
    // 구체 콜라이더 정점 찍기 (구체 물체와 방식은 같은데 텍스처가 필요 없다)

    float thetaStep = XM_2PI / sliceCount;
    float phiStep = XM_PI / stackCount;

    vector<Vertex>& vertices = mesh->GetVertices();
    vertices.reserve((sliceCount + 1) * (stackCount + 1));

    for (UINT i = 0; i <= stackCount; i++)
    {
        float phi = i * phiStep;

        for (UINT j = 0; j <= sliceCount; j++)
        {
            float theta = j * thetaStep;

            Vertex vertex;
            vertex.pos.x = sin(phi) * cos(theta) * radius;
            vertex.pos.y = cos(phi) * radius;
            vertex.pos.z = sin(phi) * sin(theta) * radius;

            vertices.push_back(vertex);
        }
    }

    //Indices
    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve(sliceCount * stackCount * 6);

    for (UINT i = 0; i < stackCount; i++)
    {
        for (UINT j = 0; j < sliceCount; j++)
        {
            indices.push_back((sliceCount + 1) * i + j);//0
            indices.push_back((sliceCount + 1) * (i + 1) + j);//1

            indices.push_back((sliceCount + 1) * i + j);//0            
            indices.push_back((sliceCount + 1) * i + j + 1);//2            
        }
    }
}
