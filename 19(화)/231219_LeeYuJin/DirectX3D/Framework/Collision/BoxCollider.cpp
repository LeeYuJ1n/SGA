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
// * 12.19 : VS 주석 예외처리 문제로 인해 아래 함수에서 작성했던
//           주석을 모두 정리합니다 (15일 강의자료)

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

        if (NearlyEqual(f, 0.0f))
        {
            if (min[i] > e || max[i] < e) return false;
            // "e"라는 숫자가 음수가 되면 안 된다
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

    // 충돌 지점의 정보를 만들고 초기화 (자기는 box1, 부딪친 쪽도 box2)
    ObbDesc box1, box2;
    GetObb(box1);
    collider->GetObb(box2);

    // 빅 D 계산 : 여기서는 두 큐브 충돌체 사이의 공간관계에서 곧바로 계산
    Vector3 D = box2.pos - box1.pos;

    for (UINT i = 0; i < 3; i++)
    {
        // 축끼리 분석상 어긋남(세퍼레이션)이 있는가? 를 계산하고,
        // * ( 해당 함수의 경우 ) 더불어서 두 큐브 사이에 거리도 지나치게 떨어져 있는가도 계산
        // 해당 계산을 x, y, z 순으로 번갈아서 한다 ( Vector3에 [] 연산자 적용 )
        // * 호출해서 벡터를 사용했을 경우 ( DX, UE, Unity ) -> 그냥 접근연산자나 멤버 연산자를 써도 무방
        // -> 조건문이 참이라면, 축도 떨어져 있거나 거리가 멀다 ( 혹은 둘 다다 )
        if (IsSeperateAxis(D, box1.axis[i], box1, box2)) return false;
        if (IsSeperateAxis(D, box2.axis[i], box1, box2)) return false;
    }
    // 위 계산이 두 큐브에서 회전 정도가 극심하지 않았다는 가정 하에
    // X축끼리, Y축 끼리, Z축끼리 비교하는 것
    
    // 하지만 큐브는 광원과 다르게 축의 양이 ( 선이나 면보다는 ) 많다 ( = 3개다 )

    // 그러므로 밑에 3x3개의 축을 모두 다시 비교 진행
    // -> 그러나 x, y, z끼리 비교하면 결과가 확실한 경우도 많아 위에 간편 조건문으로 진행
    // 나머지를 반복문으로 수행

    // 축의 정보 = 위치, 각도 등이 어느 축이든 다른 큐브와 완전히 같은 것이 있다
    //          = 해당 기하학 정보가 겹친다 = 같은 위치 ( 혹은 쵯한 겹치는 것이 가능한 주변 )
    for (UINT i = 0; i < 3; i++)
    {
        for (UINT j = 0; j < 3; j++)
        {
            if (box1.axis[i] == box2.axis[j]) return true;
        }
    }

    // 여기로 오게 되면 일단 서로 축 정보 = 위치, 각도가 다르다는 뜻
    // 그러므로 이제 모든 축을 모든 축과 다시 어긋나는지 ( 그리고 거리도 먼지 ) 모두 계산
    for (UINT i = 0; i < 3; i++)
    {
        for (UINT j = 0; j < 3; j++)
        {
            // 두 축의 정보를 크로스곱 ( 법선내기, 면적과 벡터간 관계 찾기 ) 
            Vector3 cross = Cross(box1.axis[i], box2.axis[j]);

            // 법선과 빅D ( 위치관계 ) 끼리 다시 어긋나 있는지 또 계산
            // 혹은 "빅D가 벡터간에 만들어진 면적을 뚫을 수 있는가?"
            // 계산 결과가 참 = 이 둘은 어긋난 것 = 만날 수 없다 = 충돌 아님
            if (IsSeperateAxis(D, cross, box1, box2)) return false;
        }
    }

    // 여기까지 오면 알 수 있는 사실
    // 두 큐브는 x, y, z끼리 정보가 완전히 같지는 않지만,
    // 축 정보가 적당히 어긋난 적이 없다 
    // = 약간 삐뚜름한 것 같아도, 정점끼리는 ( 벡터의 정보끼리는 ) 침범을 한다
    // = 충돌 났다
    return true;
}

bool BoxCollider::IsSeperateAxis(Vector3 D, Vector3 axis, BoxCollider::ObbDesc box1, BoxCollider::ObbDesc box2)
{
    //축이 박스끼리 다른 상태인가?

    // 두 큐브의 위치관계와 축의 정보를 받아서 점곱 후, 절대값 내기

    float distance = abs(Dot(D, axis));

    // 함수에 사용할 a, b라는 소수를 초기화

    float a = 0.0f;
    float b = 0.0f;

    for (UINT i = 0; i < 3; i++)
    {
        // a는 축과 각 충돌된 정보 중, 박스1에 저장된 지점을 축정보에 점곱
        // b는 축과 각 충돌된 정보 중, 박스2에 저장된 지점을 축정보에 점곱

        // 그렇게 해서, 박스1과 2의 ( 아직 불명의 ) 충돌면과 
        // 매개변수로 받은 축정보 (두 박스의 축끼리 법선을 낸 것)
        // 차례로 얻게 된다

        Vector3 temp = box1.axis[i] * box1.halfSize[i];
        a += abs(Dot(temp, axis));
        temp = box2.axis[i] * box2.halfSize[i];
        b += abs(Dot(temp, axis));
    }

    // 현재 충돌이 일어난 지점과 각 상자로부터의 축점 ( 원점 = 보통은 객체의 위치 ) 사이의
    // 각도 및 거리를 모두 합한 결과가 일반 숫자 ( 스칼라 ) 로 나올 것

    // 해당 결과보다 상자끼리의 거리가 더 더 멀다면
    // 축도 축이지만 해당 축으로부터 도출 가능한 가장 "가까운" 점끼리도 이들은 서로 만나지 못한다
    // = 충돌 안 났다는 뜻 ( 함수는 True, 왜냐면 "떨어져 있음"을 보기 위함 )

    return distance > a + b;

    // * 사족이지만, 그래서 벡터가 충돌 계산에 쓰이기 시작하면
    //   결국 모든 계산은 기본적으로 거리와 각도의 문제로 바뀝니다
    //   미묘하게 원끼리 계산하는 것과 닮기 시작합니다
    //   그래서 어쩌면 원리가 더 쉬울 수도 있다
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

        // int a = 10; // 인덱스 검사시 중단점 활성화를 위해서 만든 거짓코드
    }
}