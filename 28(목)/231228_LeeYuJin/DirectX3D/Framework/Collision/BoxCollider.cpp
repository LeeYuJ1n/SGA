#include "Framework.h"

BoxCollider::BoxCollider(Vector3 size)
{
    //임시 코드 : 사이즈가 지정이 안 되네요...
    this->size = Vector3(1, 1, 1);


    //유형 이넘 지정
    type = Type::BOX;

    MakeMesh(); // 처음 생성될 때 부정형이었던 메시 모양 잡기
    mesh->CreateMesh(); //메시 모양 따라 생성
}

void BoxCollider::GetObb(ObbDesc& obbDesc)
{
    // 충돌 상황 당시에 집계된 OBB 구조 기록

    obbDesc.pos = GlobalPos(); // (충돌이 일어난 충돌체의) 월드 내 실제 위치를 반영

    obbDesc.axis[0] = Right(); // 기본 축정보 넣기. Right는 좌우 = X
    obbDesc.axis[1] = Up();    // 위아래 = Y
    obbDesc.axis[2] = Forward(); // 앞뒤 = Z

    //계산 편의를 위한 절반 크기 미리 구하기
    obbDesc.halfSize = size * 0.5f * GlobalScale(); // 비율과 원본의 월드 상 크기를 반영

}

//광선과 박스 충돌체가 부딪친 기본 상황
// * 12.15 : 매개변수의 디폴트 값은 정의에서는 작성하지 않습니다!
bool BoxCollider::IsRayCollision(IN Ray ray, OUT Contact* contact)
{

    ObbDesc box;
    GetObb(box);

    Vector3 min = box.halfSize * -1.0f;
    Vector3 max = box.halfSize;

    Vector3 delta = box.pos - ray.pos;

    Vector3 D = ray.dir.GetNormalized();

    float tMin = 0.0f;
    float tMax = FLT_MAX;

    for (int i = 0; i < 3; i++)
    {
        Vector3 axis = box.axis[i];
        float e = Dot(axis, delta);
        float f = Dot(D, axis);

        if (NearlyEqual(f, 0.0f))//레이와 축이 수직인 상황
        {
            if (min[i] > e || max[i] < e) return false;
        }
        else
        {
            float t1 = (e + min[i]) / f;
            float t2 = (e + max[i]) / f;

            if (t1 > t2) swap(t1, t2);

            if (t2 < tMax) tMax = t2;
            if (t1 > tMin) tMin = t1;
            if (tMin > tMax) return false;
        }
    }

    if (contact != nullptr)
    {
        contact->tag = tag;
        contact->distance = tMin;
        contact->hit = ray.pos + ray.dir * tMin;
    }

    return true;
    
}

bool BoxCollider::IsSphereCollision(class SphereCollider* collider)
{
    // 구체와 박스의 충돌

    ObbDesc box;
    GetObb(box);

    Vector3 closestPointToSphere = box.pos;

    for (UINT i = 0; i < 3; i++)
    {
        Vector3 direction = collider->GlobalPos() - box.pos;

        float length = Dot(box.axis[i], direction);

        float mult = (length < 0.0f) ? -1.0f : 1.0f;

        length = min(abs(length), box.halfSize[i]);

        closestPointToSphere += box.axis[i] * length * mult;
    }

    float distance = Distance(collider->GlobalPos(), closestPointToSphere);

    return distance <= collider->Radius();
}

bool BoxCollider::IsBoxCollision(class BoxCollider* collider)
{
    // 박스끼리의 충돌

    ObbDesc box1, box2;
    GetObb(box1);
    collider->GetObb(box2);

    Vector3 D = box2.pos - box1.pos;

    for (UINT i = 0; i < 3; i++)
    {
        if (IsSeperateAxis(D, box1.axis[i], box1, box2)) return false;
        if (IsSeperateAxis(D, box2.axis[i], box1, box2)) return false;
    }

    for (UINT i = 0; i < 3; i++)
    {
        for (UINT j = 0; j < 3; j++)
        {
            if (box1.axis[i] == box2.axis[j]) return true;
        }
    }

    for (UINT i = 0; i < 3; i++)
    {
        for (UINT j = 0; j < 3; j++)
        {
            Vector3 cross = Cross(box1.axis[i], box2.axis[j]);
            if (IsSeperateAxis(D, cross, box1, box2)) return false;
        }
    }

    return true;
}

bool BoxCollider::IsSeperateAxis(Vector3 D, Vector3 axis, BoxCollider::ObbDesc box1, BoxCollider::ObbDesc box2)
{
    //축이 박스끼리 다른 상태인가?

    float distance = abs(Dot(D, axis));

    float a = 0.0f;
    float b = 0.0f;

    for (UINT i = 0; i < 3; i++)
    {
        Vector3 temp = box1.axis[i] * box1.halfSize[i];
        a += abs(Dot(temp, axis));
        temp = box2.axis[i] * box2.halfSize[i];
        b += abs(Dot(temp, axis));
    }

    return distance > a + b;
}

void BoxCollider::MakeMesh()
{
    //Draw 매개변수 지정에 따라 메시 모양이 다르다

    if (!isRenderAsLine) // 기본 형태 (텍스처 있는 큐브와 동일) : 선 기반 형태는 아래쪽에
    {
        // * 원래는 정점이 8개만 있어도 되지만, UV 큐브를 기준으로 만드느라 중복 좌표 있음

        Vector3 half = size * 0.5f;

        //기본(매개변수 없음, 디폴트) 기준 메시 생성
        vector<Vertex>& vertices = mesh->GetVertices();

        //Front
        vertices.emplace_back(-half.x, -half.y, -half.z);
        vertices.emplace_back(-half.x, +half.y, -half.z);
        vertices.emplace_back(+half.x, -half.y, -half.z);
        vertices.emplace_back(+half.x, +half.y, -half.z);
        //Up                   
        vertices.emplace_back(-half.x, +half.y, -half.z);
        vertices.emplace_back(-half.x, +half.y, +half.z);
        vertices.emplace_back(+half.x, +half.y, -half.z);
        vertices.emplace_back(+half.x, +half.y, +half.z);
        //Left               
        vertices.emplace_back(+half.x, +half.y, -half.z);
        vertices.emplace_back(+half.x, +half.y, +half.z);
        vertices.emplace_back(+half.x, -half.y, -half.z);
        vertices.emplace_back(+half.x, -half.y, +half.z);
        //Right              
        vertices.emplace_back(-half.x, +half.y, -half.z);
        vertices.emplace_back(-half.x, -half.y, -half.z);
        vertices.emplace_back(-half.x, +half.y, +half.z);
        vertices.emplace_back(-half.x, -half.y, +half.z);
        //Back               
        vertices.emplace_back(-half.x, +half.y, +half.z);
        vertices.emplace_back(-half.x, -half.y, +half.z);
        vertices.emplace_back(+half.x, +half.y, +half.z);
        vertices.emplace_back(+half.x, -half.y, +half.z);
        //Down
        vertices.emplace_back(-half.x, -half.y, -half.z);
        vertices.emplace_back(+half.x, -half.y, -half.z);
        vertices.emplace_back(-half.x, -half.y, +half.z);
        vertices.emplace_back(+half.x, -half.y, +half.z);

        vector<UINT>& indices = mesh->GetIndices();

        indices = {
            //Front
            0, 1, 2, 2, 1, 3,
            //Up
            4, 5, 6, 6, 5, 7,
            //Right
            8, 9, 10, 10, 9, 11,
            //Left
            12, 13, 14, 14, 13, 15,
            //Back
            16, 17, 18, 18, 17, 19,
            //Down
            20, 21, 22, 22, 21, 23
        };
    }
    else
    {
        Vector3 half = size * 0.5f;

        //기본(매개변수 없음, 디폴트) 기준 메시 생성
        vector<Vertex>& vertices = mesh->GetVertices();

        // D3D11_PRIMITIVE_TOPOLOGY_LINELIST 기준일 경우

        // 1. 정점을 간단하게 8개만 찍은 다음
        // 2. 해당 8개의 좌표를 각각.....

        vertices.emplace_back(-half.x, +half.y, -half.z);
        vertices.emplace_back(+half.x, +half.y, -half.z);
        vertices.emplace_back(-half.x, -half.y, -half.z);
        vertices.emplace_back(+half.x, -half.y, -half.z);

        vertices.emplace_back(-half.x, +half.y, +half.z);
        vertices.emplace_back(+half.x, +half.y, +half.z);
        vertices.emplace_back(-half.x, -half.y, +half.z);
        vertices.emplace_back(+half.x, -half.y, +half.z);

        vector<UINT>& indices = mesh->GetIndices();

        // 3. "선의 시작" -> "선의 끝" 순서로 벡터에 추가해 가면서 인덱스 벡터를 채운다
        //    (A 모서리 시작 -> A 모서리 끝 -> (A 모서리 끝과 좌표가 같은) B 모서리 시작 -> B 모서리 끝....)
        //    (순번을 예시로 들면, 0 -> 1 -> 1 -> 3 -> 3 -> 2 -> 2 -> 0 -> 0이나 4....)

        indices = {
            0, 1, 1, 3, 3, 2, 2, 0,
            4, 5, 5, 7, 7, 6, 6, 4,
            0, 4, 1, 5, 2, 6, 3, 7
        };

        int a = 10;
    }
}