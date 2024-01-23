#include "Framework.h"

Transform::Transform()
{
    world = XMMatrixIdentity(); // 단위행렬 만들기
}

void Transform::UpdateWorld() // 여기서의 월드 = 자기 월드 = 자기의 존재
{
    // 크기, 회전, 위치 정보 행렬로 계산
    S = XMMatrixScaling(localScale.x, localScale.y, 1.0f);
    //z축만이 아닌 3축회전 (피치, 요우, 롤링) 대응 함수를 호출
    // 피치 = x 회전, 앞뒤 위아래로 까딱까딱
    // 요우 = y 회전, 좌우로 빙글빙글
    // 롤링 = z 회전, 텀블링하듯이 휘청휘청
    R = XMMatrixRotationRollPitchYaw(localRotation.x,
        localRotation.y, localRotation.z);
    T = XMMatrixTranslation(localPosition.x, localPosition.y, 0.0f);

    // 월드 내에서 축위치를 재연산 (필요하면 축의 위치도 앞으로 바꿀 수 있다)
    P = XMMatrixTranslation(pivot.x, pivot.y, 0.0f);
    IP = XMMatrixInverse(nullptr, P);

    //위에서 계산한 행렬을 모두 연산해서 월드에 적용
    world = IP * S * R * T * P;

    // 여기서부터 나오는 계산은, 만들어진 행렬 정보를 밖에서 이용하거나 볼 수 있도록 한 것

    // "이 트랜스폼이 다른 트랜스폼에 붙어있을 경우, 그 트랜스폼에도 월드 정보를 공유한다"
    if (parent)
        world *= parent->world;

    // 벡터 계산을 통해서 (Store : 가게, 혹은 "확보")
    XMStoreFloat4x4(&matWorld, world);
    right = Vector2(matWorld._11, matWorld._12); //현재 기준의 "오른쪽" (이 기준들이 벡터 계산 등에 쓰인다)
    up = Vector2(matWorld._21, matWorld._22);    //현재 기준의 "위쪽"

    //외부로 보이기 위한 정보도 재추출
    XMVECTOR outS, outR, outT;
    XMMatrixDecompose(&outS, &outR, &outT, world);

    Float2 tempPos, tempScale;
    XMStoreFloat2(&tempPos, outT);
    XMStoreFloat2(&tempScale, outT);

    //글로벌 월드에 추출된 정보를 이용해서 "전체 화면 내의 위치"를 정한다
    globalPosition = tempPos;
    globalScale = tempScale;
}

void Transform::RenderUI()
{
    // ImGUI를 사용해서 트랜스폼의 정보 출력 (씬을 돌릴 때, 기회가 있으면 살펴보기)

    ImGui::Text(tag.c_str());

    string temp = tag + "_Pos";
    ImGui::DragFloat2(temp.c_str(), (float*)&localPosition, 1.0f);

    temp = tag + "_Rot";
    Float3 rot;
    rot.x = XMConvertToDegrees(localRotation.x);
    rot.y = XMConvertToDegrees(localRotation.y);
    rot.z = XMConvertToDegrees(localRotation.z);

    ImGui::DragFloat3(temp.c_str(), (float*)&rot, 1.0f, -180, 180);

    localRotation.x = XMConvertToRadians(rot.x);
    localRotation.y = XMConvertToRadians(rot.y);
    localRotation.z = XMConvertToRadians(rot.z);

    temp = tag + "_Scale";
    ImGui::DragFloat2(temp.c_str(), (float*)&localScale, 0.1f);
}
