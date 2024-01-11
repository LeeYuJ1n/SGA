#include "Framework.h"

Camera::Camera()
{
    tag = "Camera";

    viewBuffer = new ViewBuffer();
    viewBuffer->SetVS(1);

    Load();

    prevMousePos = mousePos;
}

Camera::~Camera()
{
    delete viewBuffer;

    Save();
}

void Camera::Update()
{
    projection = Environment::Get()->GetProjection();
    Frustum();

    if (target)
        FollowMode();
    else
        FreeMode();

    SetView();
}

void Camera::GUIRender()
{
    if (ImGui::TreeNode("CameraOption"))
    {
        ImGui::DragFloat("MoveSpeed", &moveSpeed);
        ImGui::DragFloat("RotSpeed", &rotSpeed);

        if (target && ImGui::TreeNode("TargetOption"))
        {
            ImGui::DragFloat("Distance", &distance, 0.1f);
            ImGui::DragFloat("Height", &height, 0.1f);
            ImGui::DragFloat3("FocusOffset", (float*)&focusOffset, 0.1f);

            float degree = XMConvertToDegrees(rotY);
            ImGui::DragFloat("RotY", &degree, 0.1f);
            rotY = XMConvertToRadians(degree);

            ImGui::DragFloat("MoveDamping", &moveDamping, 0.1f);
            ImGui::DragFloat("RotDamping", &rotDamping, 0.1f);

            ImGui::Checkbox("LookAtTargetX", &isLookAtTargetX);
            ImGui::Checkbox("LookAtTargetY", &isLookAtTargetY);
            
            ImGui::InputText("File", file, 128);

            if(ImGui::Button("Save"))
                TargetOptionSave(file);
            ImGui::SameLine();
            if (ImGui::Button("Load"))
                TargetOptionLoad(file);

            ImGui::TreePop();
        }

        Transform::GUIRender();

        ImGui::TreePop();
    }
}

void Camera::SetView()
{
    UpdateWorld();

    view = XMMatrixInverse(nullptr, world);

    viewBuffer->Set(view, world);
    viewBuffer->SetVS(1);
}

Vector3 Camera::ScreenToWorld(Vector3 pos)
{
    return XMVector3TransformCoord(pos, world);
}

Vector3 Camera::WorldToScreen(Vector3 pos)
{
    return XMVector3TransformCoord(pos, view);
}

Ray Camera::ScreenPointToRay(Vector3 screenPoint)
{
    Vector3 screenSize(WIN_WIDTH, WIN_HEIGHT, 1.0f);

    Vector2 point;
    point.x = (screenPoint.x / screenSize.x) * 2.0f - 1.0f;
    point.y = (screenPoint.y / screenSize.y) * 2.0f - 1.0f;    

    Float4x4 temp;
    XMStoreFloat4x4(&temp, projection);

    screenPoint.x = point.x / temp._11;
    screenPoint.y = point.y / temp._22;
    screenPoint.z = 1.0f;

    screenPoint = XMVector3TransformNormal(screenPoint, world);

    Ray ray;
    ray.pos = Pos();
    ray.dir = screenPoint.GetNormalized();

    return ray;
}

void Camera::LookAtTarget()
{    
    rotMatrix = XMMatrixRotationY(target->Rot().y + rotY);

    Vector3 forward = XMVector3TransformNormal(Vector3::Forward(), rotMatrix);

    Pos() = target->GlobalPos() + forward * -distance;
    Pos().y += height;    

    Vector3 offset = XMVector3TransformCoord(focusOffset, rotMatrix);
    Vector3 targetPos = target->GlobalPos() + offset;

    Vector3 dir = (targetPos - Pos()).GetNormalized();
    forward = Vector3(dir.x, 0.0f, dir.z).GetNormalized();

    Rot().x = acos(Dot(forward, dir));
    Rot().y = atan2(dir.x, dir.z);
}

void Camera::FreeMode()
{
    Vector3 delta = mousePos - prevMousePos;
    prevMousePos = mousePos;

    if (KEY_PRESS(VK_RBUTTON))
    {
        if (KEY_PRESS('W'))
            Pos() += Forward() * moveSpeed * DELTA;
        if (KEY_PRESS('S'))
            Pos() += Back() * moveSpeed * DELTA;
        if (KEY_PRESS('A'))
            Pos() += Left() * moveSpeed * DELTA;
        if (KEY_PRESS('D'))
            Pos() += Right() * moveSpeed * DELTA;
        if (KEY_PRESS('E'))
            Pos() += Down() * moveSpeed * DELTA;
        if (KEY_PRESS('Q'))
            Pos() += Up() * moveSpeed * DELTA;

        Rot().x -= delta.y * rotSpeed * DELTA;
        Rot().y += delta.x * rotSpeed * DELTA;
    }
}

void Camera::FollowMode()
{   
    destRot = Lerp(destRot, target->Rot().y, rotDamping * DELTA);    
    rotMatrix = XMMatrixRotationY(destRot + rotY);

    Vector3 forward = XMVector3TransformNormal(Vector3::Forward(), rotMatrix);

    destPos = target->GlobalPos() + forward * -distance;
    destPos.y += height;

    Pos() = Lerp(Pos(), destPos, moveDamping * DELTA);    

    Vector3 offset = XMVector3TransformCoord(focusOffset, rotMatrix);
    Vector3 targetPos = target->GlobalPos() + offset;

    Vector3 dir = (targetPos - Pos()).GetNormalized();
    forward = Vector3(dir.x, 0.0f, dir.z).GetNormalized();

    if (isLookAtTargetX)
    {
        Rot().x = acos(Dot(forward, dir));        
    }    
    if (isLookAtTargetY)
    {
        Rot().y = atan2(dir.x, dir.z);
    }
}

void Camera::Frustum()
{
    Float4x4 VP; // 뷰포트 임시 변수
    XMStoreFloat4x4(&VP, view * projection); // 뷰포트의 모양을 낸다
                                             // 모양 내는 방법 : 뷰포트 행렬(2차원 같은 3차원) x 프로젝션(실제 3차원)
                                             //                  이 관계의 이해가 중요!(행렬의 곱은 어떤 식으로든 할 수 있으니까)
                                             // -> 행렬곱 결과 (4x4 행렬 x 4x4 행렬 = 4x4 행렬)
                                             //    행렬 모양은 같은데, 면의 모양이 달라진다
                                             //     -> 원래의 뷰포트 모양이 프로젝션 행렬의 영향을 받아 팽창하게 된다
                                             //     -> 그 결과가 바로 절두체

    // 만든 새로운 뷰포트 (3차원 모양, 우너근 시점, 앞은 졸고 뒤로 갈수록 팽창하는 새로운 모양)
    // ...를 살펴봐서, 각 행렬의 정점을 잇는 면 6개를 다시 도출
    //Left
    // x의 왼쪽, z의 앞과 뒤
    // * 행렬의 원소 분해를 찾아서 적용하면 된다
    a = VP._14 + VP._11; // ● ○ ○ ●
    b = VP._24 + VP._21; // ● ○ ○ ●
    c = VP._34 + VP._31; // ● ○ ○ ●
    d = VP._44 + VP._41; // ● ○ ○ ●
    planes[0] = XMVectorSet(a, b, c, d); // DX 제공 함수로 벡터 공간 세팅 (2차원 평면)
                                         // 행렬곱이 아니라 실제 적용될 "면"을 구하는 게 목적이라 DX 함수가 유리

    //Right
    // x의 왼쪽, z의 앞과 뒤
    a = VP._14 - VP._11; // ● ○ ○ ●
    b = VP._24 - VP._21; // ● ○ ○ ●
    c = VP._34 - VP._31; // ● ○ ○ ●
    d = VP._44 - VP._41; // ● ○ ○ ●
    planes[1] = XMVectorSet(a, b, c, d);

    //Bottom
    // x의 아래, z의 앞과 뒤
    // * 위 식과 같은 원소가 여럿 쓰인다 : 지금 선택된 원소는 수학적 행렬 분해에 의한 결과
    // -> 직관적인 이해? 힘들다 (우리는 수학을 모른다)
    // -> 암기? 했을 때 난이도와 위험성이 더 크다 (외우는 것도 힘든데 틀리면 더 문제)
    // -> Matrix, Elements, 4x4 등의 키워드로 수학 관련 정보를 찾으면 가장 적절할 것)
    // -> 찾아낸 숫자를 통해 정점 4군데를 찾아서 면을 도출하는 것이 개발자에게는 더 중요하다
    a = VP._14 + VP._12; // ○ ● ○ ●
    b = VP._24 + VP._22; // ○ ● ○ ●
    c = VP._34 + VP._32; // ○ ● ○ ●
    d = VP._44 + VP._42; // ○ ● ○ ●
    planes[2] = XMVectorSet(a, b, c, d);

    //Top
    // x의 위, z의 앞과 뒤
    a = VP._14 - VP._12; // ○ ● ○ ●
    b = VP._24 - VP._22; // ○ ● ○ ●
    c = VP._34 - VP._32; // ○ ● ○ ●
    d = VP._44 - VP._42; // ○ ● ○ ●
    planes[3] = XMVectorSet(a, b, c, d);

    //Near
    // 가까이 있는 곳 이라기 보다 시작면
    // "지금 여기" 혹은 "카메라의 위치"
    a = VP._14 + VP._13; // ○ ○ ● ●
    b = VP._24 + VP._23; // ○ ○ ● ●
    c = VP._34 + VP._33; // ○ ○ ● ●
    d = VP._44 + VP._43; // ○ ○ ● ●
    planes[4] = XMVectorSet(a, b, c, d);

    //Far
    // 일단 위치는 안 잡혀 있는 저 먼 곳 어딘가의 평행면
    // -> 여기에서 어떤 거리를 주게 되면? -> 그게 이 절두체의 한계(범위)
    // * 상 하 좌 우 범위는 위에서 만들었으니까
    a = VP._14 - VP._13; // ○ ○ ● ●
    b = VP._24 - VP._23; // ○ ○ ● ●
    c = VP._34 - VP._33; // ○ ○ ● ●
    d = VP._44 - VP._43; // ○ ○ ● ●
    planes[5] = XMVectorSet(a, b, c, d);

    // 면 정규화
    // 면의 크기를 단위 크기로 다시 조정
    // -> Far 쪽의 크기(와 거리)를 조정 가능
    // -> Far가 더 커지기를 바라면 추가로 더 Far의 거리를 늘려주거나, 식을 다르게 적용해야 한다

    FOR(6)
        planes[i] = XMPlaneNormalize(planes[i]);

    // 여기까지 오면, 카메라는 다음 정보를 갖게 된다

    // 1. 지역 변수로 만든 절두체 (함수 끝나면 없어질 거임)
    // 2. 해당 절두체의 경계면 6군데를 정의하는 가상의 평면 6개 (계속 사용함)
    //    여기서 만든 planes[0]부터 [5]까지를 다른 곳에서 호출하거나, 함수를 통해서
    //    절두체 충돌에 활용할 수 있다
}

void Camera::TargetOptionSave(string file)
{
    string path = "TextData/Camera/" + file + ".cam";

    BinaryWriter* writer = new BinaryWriter(path);

    writer->Float(distance);
    writer->Float(height);
    writer->Float(moveDamping);
    writer->Float(rotDamping);
    writer->Float(rotY);
    writer->Vector(focusOffset);
    writer->Bool(isLookAtTargetX);
    writer->Bool(isLookAtTargetY);

    delete writer;
}

void Camera::TargetOptionLoad(string file)
{
    string path = "TextData/Camera/" + file + ".cam";

    BinaryReader* reader = new BinaryReader(path);

    distance = reader->Float();
    height = reader->Float();
    moveDamping = reader->Float();
    rotDamping = reader->Float();
    rotY = reader->Float();
    focusOffset = reader->Vector();
    isLookAtTargetX = reader->Bool();
    isLookAtTargetY = reader->Bool();

    delete reader;
}

bool Camera::ContainPoint(Vector3 point)
{
    // 절두체 충돌 판별 함수

    // 절두체 안에 위치가 있는지 판별만 하면 되기 때문에 호출은 어디서 하든 상관없다

    // 적용 가능한 예시
    // 1. Scene       : 절두체 안에 Scene 개체가 들어오면 렌더, 아니면 렌더 없음
    // 2. GameManager : 절두체 안에 게임의 모든 개체가 들어오면 렌더, 아니면 없음
    // 3. Environment : 앱 안의 ...이하 생략
    // 4. 객체 자체    : 스스로가 절두체 안에 있을 때, 없을 때

    // -> 다만 최적화나, 개발상의 편의를 위해서 일반적으로 1 ~ 2 정도의 위치에 절두체 관련 호출을 한다
    //    가끔 4, 그리고 더욱 가끔 3 (가장 극단적인 절두체 계산 강요)

    // 반복문 돌려서
    FOR(6)
    {
        // 면의 방향과 정해진 위치(매개변수로 받은) 사이의 관계를 수직으로 계산
        // -> 간단히 말하면, 면에서 정해진 위치로 법선을 내었다고 가정하고
        //    해당 법선을 벡터로 도출하는 것
        // -> 더 간단히 말하면 "면이 땅인 것처럼 생각했을 때, 위치는 면 위에 있는가?
        Vector3 dot = XMPlaneDotCoord(planes[i], point); // DX 제공 함수 (이건 DX 이 함수가 제일 편하다)

        // 기준면에 의한 법선의 방향이 음수라면? -> 면이 땅이라고 쳤을 때, 위치는 지하에 있다
        // = 면들의 범위 안에 없다
        if (dot.x < 0.0f)
            return false;
    }

    // 여기까지 오면 절두체를 구성 중인 6개의 면 안에 완전히 위치가 들어와 있다
    return true;
}
