#include "Framework.h"

BlockManager::~BlockManager()
{
    for (Cube* block : blocks)
        delete block; // 블록 위치 지우기

    blocks.clear(); // 블록 리스트 지우기
}

void BlockManager::Update()
{
    for (Cube* block : blocks)
        block->Update();
}

void BlockManager::Render()
{
    for (Cube* block : blocks)
        block->Render();
}

void BlockManager::CreateBlock(UINT width, UINT height)
{
    vector<wstring> textures; //블록을 구성, 혹은 구분하기 위한 기준(=텍스처)의 벡터
    textures.resize(5); // 텍스처 벡터의 크기 정하기 (숫자는 현재 바라는 블록 종류)

    //만든 벡터에 텍스처 정보를 등록 (텍스처 그 자체는 아님)
    for (int i = 0; i < textures.size(); ++i)
    {
        textures[i] = L"Textures/Block/block" + to_wstring(i) + L".png";
    }

    //만들어진 텍스처 정보(파일 이름)를 이용해서 큐브 만들기
    for (int z = 0; z < height; ++z)
    {
        for (int x = 0; x < width; ++x)
        {
            Vector3 pos = { (float)x, 0, (float)z };
            wstring file = textures[Random(0, textures.size())];

            Cube* block = new Cube(); // 큐브 생성
            block->GetMaterial()->SetDiffuseMap(file); //위에서 찾은 텍스처 파일명 대입
            block->Pos() = pos; // 위에서 만든 위치도 대입
            block->Update(); //업데이트 1회

            blocks.push_back(block); // 블록 리스트에 지금 만든 큐브 추가
        }
    }
}

bool BlockManager::BuildBlock(Cube* block)
{
    // 광선
    Ray ray = CAM->ScreenPointToRay(Vector3(CENTER_X, CENTER_Y));

    // 충돌 정보
    float minDistance = FLT_MAX;
    Contact contact;
    Vector3 hit;

    // 반복자와 충돌대상 초기화
    list<Cube*>::iterator it = blocks.begin();
    Cube* collidBlock = nullptr;

    for (it; it != blocks.end(); ++it)
    {
        if ((*it)->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance)
            {
                minDistance = contact.distance;
                hit = contact.hit;
                collidBlock = *it;
            }
        }
    }

    // 충돌한 블록이 없으면 종료하고 false 반환
    if (collidBlock == nullptr) return false;

    // 여기까지 오면 충돌한 블록이 있었음

    // 해당 결과에 따른 추가 연산 시작

    // 방향도출 (충돌한 블록으로 가는 방향)
    Vector3 dir = hit - collidBlock->GlobalPos();

    int maxIndex = 0;
    float maxValue = 0;

    for (int i = 0; i < 3; ++i)
    {
        //한 축 방향이 다른 축 방향보다 더 크면
        if (abs(dir[i] > maxValue))
        {
            maxIndex = i;
            maxValue = abs(dir[i]); // 해당 값 갱신
        }
    }

    //가장 많이 간 방향을 기준으로 다시 스위치문
    switch (maxIndex)
    {
    case 0:
        dir.x = dir.x > 0 ? 1 : -1;
        dir.y = 0;
        dir.z = 0;
        break;

    case 1:
        dir.x = 0;
        dir.y = dir.y > 0 ? 1 : -1;
        dir.z = 0;
        break;

    case 2:
        dir.x = 0;
        dir.y = 0;
        dir.z = dir.z > 0 ? 1 : -1;
        break;
    }

    // 여기까지 오면 각각 방향에 맞추어서 "상하, 좌우, 전후" 중 하나인 방향이 나온다
    // 그 방향에 추가로 블록을 만들어주거나(빌드) 다른 사물을 붙여주면 된다

    // 현재 : 블록이 비활성화되었다고 치고, 활성화된 후(나타난 후) 리스트에 추가되는 코드를 작성
    // TODO : 상호작용이 다르게 만들어지거나 변경되면 아래에서 수정, 작성
    // 혹은 : 바로 아래 Push를 여기서 쓰는 것도 어쩌면 가능

    block->SetActive(true); // 어딘가에서 비활성화된 블록이 있다고 치고 여기서 "생기게"
    block->Pos() = collidBlock->GlobalPos() + dir; // 내가 상호작용한 "위치" 블록에서 위에서 만든 dir만큼 비껴나간 위치
    block->Update();

    blocks.push_back(block); // "새" 블록 추가

    return true;
}

void BlockManager::Push(Collider* collider)
{
    // 상호작용하면 밀어낸 방향에 가장 가까운 XYZ 기본 방향으로 블록이 움직이게 해보자

    Cube* collidBlock = nullptr;

    for (Cube* block : blocks)
    {
        //두 블록끼리 부딪친다면
        if (block->GetCollider()->IsCollision(collider))
        {
            collidBlock = block;

            Vector3 dir = collider->GlobalPos() - collidBlock->GlobalPos();

            int maxIndex = 0;
            float maxValue = 0;

            for (int i = 0; i < 3; ++i)
            {
                if (abs(dir[i] > maxValue))
                {
                    maxIndex = i;
                    maxValue = abs(dir[i]);
                }
            }

            switch (maxIndex)
            {
            case 0:
                dir.x = dir.x > 0 ? 1 : -1;
                dir.y = 0;
                dir.z = 0;
                break;

            case 1:
                dir.x = 0;
                dir.y = dir.y > 0 ? 1 : -1;
                dir.z = 0;
                break;

            case 2:
                dir.x = 0;
                dir.y = 0;
                dir.z = dir.z > 0 ? 1 : -1;
                break;
            }

            if (NearlyEqual(dir.y, 1)) continue; // 수직 위로는 가지 않게 = 솟아나지는 않게

            collider->GetParent()->Pos() += dir * 50.0f * DELTA; //  부딪친 대상 큐브가 해당 방향으로 밀려나게
        }
    }
}

Cube* BlockManager::GetCollisionBlock()
{
    // 화면 중앙에서 나가는 광선 설정 (즉 1인칭이나 초기 3인칭처럼 플레이어 입장에서 상호작용)
    Ray ray = CAM->ScreenPointToRay(Vector3(CENTER_X, CENTER_Y));
    // 후기 3인칭 게임처럼 정교한 광선이 필요하면 지금 위 광선의 광원과 방향을 조절하면 된다

    float minDistance = FLT_MAX; // 최소거리 초기화
    Contact contact;

    list<Cube*>::iterator it = blocks.begin();        // 돌리면서 검사할 순번
    list<Cube*>::iterator collidBlock = blocks.end(); // 최소거리처럼 기준이자 반복문 한계

    for (/*시작 조건 생략, 위에 만든 반복자 사용*/;
        it != blocks.end();
        ++it)
    {
        if ((*it)->GetCollider()->IsRayCollision(ray, &contact))
        {
            if (contact.distance < minDistance) // 충돌이 일어났는데 최소거리를 갱신한다면
            {
                minDistance = contact.distance; // 갱신 값 반영
                collidBlock = it; // 충돌한 블록을 it에 저장
            }
        }
    }

    if (collidBlock != blocks.end()) // 갱신된 "충돌 블록"이 위에 초기화했던 기준(한계) 안이라면
    {
        //해당 결과를 반영, 출력
        Cube* block = *collidBlock;

        //TODO : 이후 이 블록에 상호작용이 필요하면 여기서 추가 작성

        return block; // 해당 블록을 컴퓨터에게 반환
    }
    else
    {
        //여기까지 왔으면 collidBlock은 계속 리스트의 끝 = 한계 끝 = 충돌한 큐브 없었음
        return nullptr;
    }
}

float BlockManager::GetHeight(Vector3& pos)
{
    // 현재 바닥이 된 블록의 높이

    Ray ray(pos, Vector3::Down());

    Contact contact; // 광선과 물체의 충돌 결과를 저장할 곳

    float maxHeight = 0; // 터레인의 최소높이를 대신할 "바닥" 역할을 위한 초기화

    for (Cube* block : blocks)
    {
        if (block->GetCollider()->IsRayCollision(ray, &contact))
        {
            //이 안으로 들어오면 광선이 바닥에 부딪쳤다 = 광선이 중심이 되는 어떤 것이 바닥의 "위"에 있다

            if (contact.hit.y > maxHeight) // 충돌의 정보 중 높이가 위에 정한 바닥보다 높으면
            {
                maxHeight = contact.hit.y; // 값 갱신
            }
        }
    }

    // 여기까지 오면 바닥 위에 있을 경우 바닥의 높이가
    // 그렇지 않으면 초기화된 높이인 0이 나온다

    //반환
    return maxHeight;
}