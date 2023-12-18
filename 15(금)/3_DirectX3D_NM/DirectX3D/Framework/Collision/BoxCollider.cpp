#include "Framework.h"

BoxCollider::BoxCollider(Vector3 size)
{
	// 유형 타입 지정
	type = Type::BOX;

	MakeMesh();         // 처음 생성될 때 부정형이었던 메시 모양 잡기
	mesh->CreateMesh(); // 메시 모양 따라 생성
}

void BoxCollider::GetObb(ObbDesc& obbDesc)
{
    // 충돌 상황 당시에 집계된 OBB 구조 기록
    obbDesc.pos      = GlobalPos(); // (충돌이 일어난 충돌체의) 월드 내 실제 위치를 반영
    obbDesc.axis[0]  = Right();     // 기본 축 정보 넣기. Right : 좌우  = X
    obbDesc.axis[1]  = Up();        // 위아래  = Y
    obbDesc.axis[2]  = Forward();   // 앞뒤    = Z

    // 계산 편의를 위한 절반 크기 미리 구하기 (half = 절반)
    obbDesc.halfSize = size * 0.5f * GlobalScale(); // 비율과 원본의 월드 상 크기를 반영
}

// 광선과 박스 충돌체가 부딪친 기본 상황
bool BoxCollider::IsRayCollision(IN Ray ray, OUT Contact* contact)
{
	// 충돌체의 현재 상황을 업데이트
    UpdateWorld();

    // 기록용 구조체
    ObbDesc box;
    GetObb(box); // 초기화 기록하기

    // 기록용 구조체에서 취급할 충돌 범위 최소 최대 구하기
    // 기록 박스에 최소 최대 규격을 구해놓고 해당 규격보다 충돌 당시 상황이 벗어나 있으면 그냥 충돌 안 된 걸로 친다
    Vector3 min   = box.halfSize * -1.0f;  // 최소 규격 구하기
    Vector3 max   = box.halfSize * 1.0f;   // 최대 규격 구하기

    Vector3 delta = box.pos = ray.pos;       // 충돌체와 광선 발원지의 벡터상 (공간)관계
    Vector3 D     = ray.dir.GetNormalized(); // 광선 방향을 정규화한 것 : 조사방향
                                             // dir : 방향
                                             // GetNormalized() : 정규화

    // 계산할 구치의 최대 최소 구하기
    float tMin = 0.0f;
    float tMax = FLT_MAX; // 이것보다 큰 숫자는 무시한다
                          // -> unsigned 같은 별도의 자료형을 쓰지 않고도 음수는 빼겠다

    // 여기까지 오면 계산 범위와 기본 벡터 관계 설정 끝
    // 이제부터 광선과 박스의 상황을 대조

    // 3번 돌리는 반복문 : Obb 기록체 축 숫자에 따라 
    // 해당 기록체의 축 기준으로 광선이 어떻게 지나가고 있는가를 보기 위함
    for (int i = 0; i < 3; ++i)
    {
        // OBB에서 축 따오기
        Vector3 axis = box.axis[i]; // 다른 설정이 없다면 x -> y -> z 축 순서로 위치관계 판별
        
        // 축과 방향을 각각 점곱
        float e = Dot(axis, delta); // 기록체 축과 박스-광선 공간관계 점곱
        float f = Dot(D, axis);     // 광선 자체의 (박스와는 무관환) 자체 방향을 기록체의 축과 내적
        // 방향(D)에서부터 나오는 숫자들이기 때문에 지칭할 때 e, f로 지칭
        // -> 두 벡터의 사이에서 나온 cos = 각도와 비율를 짐작할 수 있는 숫자가 나온다

        // 그래서 두 각도를 비교했을 때 
        // 1. 수직이다 = 광선이 물체와 만나지 못 한다

        // if (f == 0)            // <- 칼계산 가능. 실수와 배정밀도 계산이 자주 일어나는 DirectX 특성상 오류 가능성
        // if (f <= FLT_EPSILON)  // <- 컴퓨터가 음수로 넘어가지 않고 인지 가능한 가장 작은 소수 (입실론 오차)
                                  // FLT_EPSILON : 컴퓨터가 인지 가능한 가장 작은 소수
        if (NearlyEqual(f, 0.0f)) // <- 이 프레임워크에서, 해당 숫자가 기준 숫자에서 얼마 만큼의 입실론 오차가 일어나는지 (혹은 안 일어나는지) 판별 가능
        {
            // 광원이 Obb 아넹 있었느냐 아니냐를 판별
            // 아예 광서닝 처음부터 충돌체 안에서 나온 거라면 당연히 충돌 가능성 있음(이라기보다, 높음)
            // 반대로 광선이 아예 밖이고, 축끼리 비교한 거리 관계와도 또 수직이면 -> 지나쳐 간다

            // 기록체의 x, y, z 축에 다시 검사
            switch (i)
            {
            case 0:
                if (min.x > e || max.x < e) return false;
                break;

            case 1:
                if (min.y > e || max.y < e) return false;
                break;

            case 2:
                if (min.z > e || max.z < e) return false;
                break;
            }

            // 여기까지 오면, 일단 가능성은 둘
            // 1. 각도가 수직이 아니다 (위 if에서 거짓)
            // 2. 각도는 수직인데, 위치가 겹쳤을 수 있다 (switch) 안에서 is 조건문 거짓)
            //    -> 검사는 계속 한다
        }
        else
        {
            float raw1;
            float raw2;

            // x, y, z에 따라 공간 관계에 따른 축 정보 조정
            switch (i)
            {
            case 0:
                raw1 = min.x;
                raw2 = max.x;
                break;

            case 1:
                raw1 = min.y;
                raw2 = max.y;
                break;

            case 2:
                raw1 = min.z;
                raw2 = max.z;
                break;
            }

            // raw를 이용해서 비교용 소수 t를 구한다 (벡터 공식을 적용)

            float t1 = (e + raw1) / f; // 공간 관계(거리)에 현 벡터의 최소값을 적용하고 방향관계를 계산한다
            float t2 = (e + raw2) / f;

            // t1과 t2의 관계 다시 구하기 (광원과 기록체의 거리관계, 광원가 기록체의 크기관계)

            // if (t1 > t2) swap(t1, t2); // 더 큰 쪽이 t2가 되도록 서로 데이터 바꾸기

            // 더 큰 수가 현재 어느 정도인가?
            if (t2 < tMax) tMax = t2; // 최대를 tMax에 재할당
            if (t1 > tMin) tMin = t1; // 최소도 재할당

            // 더 큰 쪽이 뒤로 갔어야 하는데 
            if (tMin > tMax)  // 계산의 최소값이 최대값을 오히려 넘어간 상황 = 거리 혹은 방향이 어긋났음
                return false;
        }

        // 여기까지 오면 
        // 1. 광선과 충돌체의 축들 사이에 수직이 없음 (방향 면에서 만날 가능성 있음)
        // 2. 광선과 충돌체 사이에, 거리 - 방향 관계에서 어긋남이 없음 (광선이 쭉 따라가면 반드시 부딪침)

        // 접점 정보 기록하기
        if (contact != nullptr)
        {
            contact->tag      = tag;                        // 충돌체의 이름을 태그에 기록 (무엇에 부딪쳤는가)
            contact->distance = tMin;                       // 기록된 가장 작은 거리 = 충돌이 시작된 지점
            contact->hit      = ray.pos + (ray.dir * tMin); // 광선 기준으로 본 충돌 시작점(의 벡터)
        }

        return true; // 만났으므로 true
    }
}

bool BoxCollider::InSphereCollision(SphereCollider* collider)
{
	
}

bool BoxCollider::IsBoxCollision(BoxCollider* collider)
{
	
}

bool BoxCollider::IsSeperateAxis(Vector3 D, Vector3 axis, BoxCollider::ObbDesc box1, BoxCollider::ObbDesc box2)
{
	
}

void BoxCollider::MakeMesh()
{
	// Draw 매개변수 지정에 따라 매시 모양이 다르다

	// 기본(매개변수 없음, 디폴트) 기준 메시 생성

    vector<Vertex>& vertices = mesh->GetVertices();

    Vector3 half = size * 0.5f;

    // * 원래는 정점이 8개만 있어도 되지만, UV 큐브를 기준으로 만드느라 중복 좌표 있음

    //Front
    vertices.emplace_back(-half.x, -half.y, -half.z, 0, 1);
    vertices.emplace_back(-half.x, +half.y, -half.z, 0, 0);
    vertices.emplace_back(+half.x, -half.y, -half.z, 1, 1);
    vertices.emplace_back(+half.x, +half.y, -half.z, 1, 0);
    //Up
    vertices.emplace_back(-half.x, +half.y, -half.z, 0, 1);
    vertices.emplace_back(-half.x, +half.y, +half.z, 0, 0);
    vertices.emplace_back(+half.x, +half.y, -half.z, 1, 1);
    vertices.emplace_back(+half.x, +half.y, +half.z, 1, 0);
    //Left
    vertices.emplace_back(+half.x, +half.y, -half.z, 0, 1);
    vertices.emplace_back(+half.x, +half.y, +half.z, 0, 0);
    vertices.emplace_back(+half.x, -half.y, -half.z, 1, 1);
    vertices.emplace_back(+half.x, -half.y, +half.z, 1, 0);

    //Right
    vertices.emplace_back(-half.x, +half.y, -half.z, 0, 1);
    vertices.emplace_back(-half.x, -half.y, -half.z, 0, 0);
    vertices.emplace_back(-half.x, +half.y, +half.z, 1, 1);
    vertices.emplace_back(-half.x, -half.y, +half.z, 1, 0);

    //Back
    vertices.emplace_back(-half.x, +half.y, +half.z, 0, 1);
    vertices.emplace_back(-half.x, -half.y, +half.z, 0, 0);
    vertices.emplace_back(+half.x, +half.y, +half.z, 1, 1);
    vertices.emplace_back(+half.x, -half.y, +half.z, 1, 0);

    //Down
    vertices.emplace_back(-half.x, -half.y, -half.z, 0, 1);
    vertices.emplace_back(+half.x, -half.y, -half.z, 0, 0);
    vertices.emplace_back(-half.x, -half.y, +half.z, 1, 1);
    vertices.emplace_back(+half.x, -half.y, +half.z, 1, 0);

    vector<UINT>& indices = mesh->GetIndices();
    indices = 
    {
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

    // D3D11_PRIMITIVE_TOPOLOGY_LINELIST 기준일 경우
    // 1. 정점을 간단하게 8개만 찍은 다음
    // 2. 해당 8개의 좌표를 각각
    // 3. "선의 시작" -> "선의 끝" 순서로 벡터에 추가해 가면서 인덱스 벡터를 채운다
    //    (A 모서리 시작 -> A 모서리 끝 -> (A 모서리 끝과 좌표가 같은) B 모서리 시작 -> B 모서리 끝)
    //    (순번을 예시로 들면, 0 -> 1 -> 1 -> 3 -> 3 -> 2 -> 2 -> 0 -> 0이나 4)
}
