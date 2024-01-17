#include "Framework.h"

CapsuleCollider::CapsuleCollider(float radius, float height, UINT stackCount, UINT sliceCount)
    : radius(radius), height(height), stackCount(stackCount), sliceCount(sliceCount)
{
    type = CAPSULE;
    MakeMesh();
    mesh->CreateMesh();
}

bool CapsuleCollider::IsRayCollision(IN Ray ray, OUT Contact* contact)
{
    UpdateWorld();

    Vector3 direction = Up();
    Vector3 pa = GlobalPos() - direction * Height() * 0.5f;
    Vector3 pb = GlobalPos() + direction * Height() * 0.5f;

    float r = Radius();

    Vector3 ro = ray.pos;
    Vector3 rd = ray.dir;

    Vector3 ba = pb - pa;
    Vector3 oa = ro - pa;

    float baba = Dot(ba, ba);
    float bard = Dot(ba, rd);
    float baoa = Dot(ba, oa);
    float rdoa = Dot(rd, oa);
    float oaoa = Dot(oa, oa);

    float a = baba - bard * bard;
    float b = baba * rdoa - baoa * bard;
    float c = baba * oaoa - baoa * baoa - r * r * baba;
    
    float h = b * b - a * c;

    if (h >= 0.0f)
    {
        float t = (-b - sqrt(h)) / a;

        float distance = baoa + t * bard;

        if (distance > 0.0f && distance < baba)
        {
            if (contact)
            {
                contact->distance = distance;
                contact->hitPoint = ray.pos + ray.dir * t;
            }

            return true;
        }

        Vector3 oc = (distance <= 0.0f) ? oa : ro - pb;
        b = Dot(rd, oc);
        c = Dot(oc, oc) - r * r;
        h = b * b - c;

        if (h > 0.0f)
        {
            if (contact)
            {
                contact->distance = distance;
                contact->hitPoint = ray.pos + ray.dir * t;
            }

            return true;
        }
    }   

    return false;
}

bool CapsuleCollider::IsBoxCollision(BoxCollider* collider)
{  
    // 캡슐vs캡슐 계산 + 구체vs박스 계산 반반 섞은 것
    // 박스 입장에서는 마치 구체에 부딪친 것처럼
    // 캡슐 입장에서는 마치 다른 캡슐의 옆면이나 평면 등에 부딪친 것처럼
    // 각각 계산 후, 해당 위치(박스 입장에서의 접점 혹은 접점후보)로 가는 거리의 합과
    // 두 물체의 중심 지점 간 거리의 합을 비교해서 충돌 여부 판단
    // -> 혹은 더 단순히, 박스 입장에서의 접점 혹은 접점 후보를 내어서,
    //    해당 위치가 그 자체로 캡슐의 반지름(=중심들에서 나온 점들의 경계)을 안쪽으로 넘었는지 판단

    BoxCollider::ObbDesc box;
    collider->GetObb(box);

    Vector3 direction = Up();
    Vector3 pa = GlobalPos() - direction * Height() * 0.5f;
    Vector3 pb = GlobalPos() + direction * Height() * 0.5f;

    Vector3 closestPointToSphere = box.pos;
    Vector3 pointOnLine = ClosestPointOnLine(pa, pb, box.pos);

    for (UINT i = 0; i < 3; i++)
    {
        Vector3 direction = pointOnLine - box.pos;
        float length = Dot(box.axis[i], direction);
        float mult = (length < 0.0f) ? -1.0f : 1.0f;
        length = min(abs(length), box.halfSize[i]);
        closestPointToSphere += box.axis[i] * length * mult;
    }

    float distance = Distance(pointOnLine, closestPointToSphere);

    return distance <= Radius();
}

bool CapsuleCollider::IsSphereCollision(SphereCollider* collider)
{
    // 아래 함수와 원리가 기본적으로 같은데,
    // 상대 구체는 모든 점이 원점에서 거리가 같아서 계산은 더 간단해진다
    Vector3 direction = Up();
    Vector3 pa = GlobalPos() - direction * Height() * 0.5f;
    Vector3 pb = GlobalPos() + direction * Height() * 0.5f;

    Vector3 P = collider->GlobalPos();

    Vector3 pointOnLine = ClosestPointOnLine(pa, pb, P);

    float distance = Distance(P, pointOnLine);

    return distance <= (Radius() + collider->Radius());
}

bool CapsuleCollider::IsCapsuleCollision(CapsuleCollider* collider)
{
    //내 캡슐의 세로 방향 구하기
    Vector3 aDirection = Up();
    Vector3 aA = GlobalPos() - aDirection * Height() * 0.5f;
    Vector3 aB = GlobalPos() + aDirection * Height() * 0.5f;

    //상대 캡슐의 세로 방향 구하기
    Vector3 bDirection = collider->Up();
    Vector3 bA = collider->GlobalPos() - bDirection * collider->Height() * 0.5f;
    Vector3 bB = collider->GlobalPos() + bDirection * collider->Height() * 0.5f;

    //방향별 원점(위아래 구체의 중심)끼리의 관계와 거리 구하기
    //관계
    Vector3 v0 = bA - aA;
    Vector3 v1 = bB - aA;
    Vector3 v2 = bA - aB;
    Vector3 v3 = bB - aB;

    //거리
    float d0 = Dot(v0, v0);
    float d1 = Dot(v1, v1);
    float d2 = Dot(v2, v2);
    float d3 = Dot(v3, v3);

    //거리가 더 가까운 두 점 구하기 (위 구체의 원점 vs 아래 구체의 원점 vs 중간 어디쯤)
    Vector3 bestA;
    if (d2 < d0 || d2 < d1 || d3 < d0 || d3 > d1)
        bestA = aB;
    else
        bestA = aA;

    Vector3 bestB = ClosestPointOnLine(bA, bB, bestA);
    bestA = ClosestPointOnLine(aA, aB, bestB);
    bestB = ClosestPointOnLine(bA, bB, bestA);

    //도출된 거리와 두 캡슐의 반지름의 합을 비교해서 충돌 여부 판단
    // -> 캡슐은 구체의 반지름보다 "원점"에서의 거리가 더 가까운 점이 없기 때문
    float distance = Distance(bestA, bestB);

    return distance <= (Radius() + collider->Radius());
}

void CapsuleCollider::MakeMesh()
{
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

            if (vertex.pos.y > 0)
                vertex.pos.y += height * 0.5f;
            else if(vertex.pos.y < 0)
                vertex.pos.y -= height * 0.5f;

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
