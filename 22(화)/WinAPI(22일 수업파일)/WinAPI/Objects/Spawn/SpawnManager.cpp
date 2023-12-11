#include "Framework.h"

SpawnManager::SpawnManager()
{
    spawnObjects.resize(POOL_SIZE);
    for (SpawnObject*& spawnObject : spawnObjects)
        // 위 반복문은 for와 같은 구문을 공유하지만 작용은 다른 반복문
    {
        spawnObject = new SpawnObject();
    }

    // → for each : for (A : B)라고 하면 "B에 존재하는 A마다"라는 뜻
    //   → 반복문이 배열 같은 자료구조를 정확히 대상으로 하고 
    //     또한 자료구조 안에도 모든 요소들이(원소가) 똑같은 속성을 똑같이 가지고 있을 때
    //     그럴 때 써볼 수 있는 문법

    // → 쓰는 사람은 알음알음 쓰는데, 정확히 공유의 대상으로 다뤄지지 않는 문법
    //   → 이 반복문은 쓰려면 정확히 대상이 지정이 되어야 하고
    //     안에 있는 원소도 구성이 정확해야 하고
    //     결정적으로 느리다

    // → 그런데도 불구하고 왜 쓰느냐? 왜 존재하느냐?
    //   → 조건이 맞으면 코드가 간단해지니까
    //   → 조건이 정말 맞는 상황에서는 웬만해서는 오류가 안 나니까
}

SpawnManager::~SpawnManager()
{
    for (SpawnObject* spawnObject : spawnObjects)
        delete spawnObject;
}

// 스폰 매니저가 하는 일
// 1. 모든 스폰 사각형을 여기서도 관리를 해줬다
// 2. 그런데 방식이 직접관리 방식이 아니군?
//    → "할당 후 방식"(control after allocation)을 사용

// 할당 후 관리 방식 : 만들어져야 할 양을 미리부터 정해놓는다
//                  : 그리고 그 안에서만 관리를 실행한다

// 이 방식은 한 번 배열이 만들어지면 그냥 그걸로 끝(사실상 고정배열)
// 새로 만들어지지도 않고, 없어지지도 않는다

void SpawnManager::Update()
{
    // 제공 함수가 있었다 : 좌클릭 시 일어날 일
    if(KEY_DOWN(VK_LBUTTON))
    {
        // 벡터 내 모든 사각형에게 
        for (SpawnObject* spawnObjecct : spawnObjects)
        {
            // 활성화가 아니었다면
            if (!spawnObjecct->Active())
            {
                // 스폰하라(+활성화하라?)
                spawnObjecct->Spawn();
                playTime = 0.0f;
                break;

                // 위 코드는 엄밀히 말하면 사각형 "생성"이 아닙니다
                // 이미 만들어진 사각형이 눈에 보이게 해주는 것 뿐
            }
        }
    }
    
    // 모든 오브젝트가 업데이트하라
    for (SpawnObject* spawnObjecct : spawnObjects)
    {
        // 자기 관리는 자기가 알아서 하라
        spawnObjecct->Update();
    }
}

void SpawnManager::Render(HDC hdc)
{
    for (SpawnObject* spawnObjecct : spawnObjects)
    {
        spawnObjecct->Render(hdc);
    }

    wstring scoreText = L"Score : " + to_wstring(score);
    TextOut(hdc, (int)CENTER_X, 0, scoreText.c_str(),
        (int)scoreText.size());
}

void SpawnManager::DestoryObject(Vector2 point)
{
    for (SpawnObject* spawnObject : spawnObjects)
    {
        if (spawnObject->IsCollision(point))
        {
            spawnObject->Destroy();
            score++;
            return;
        }
    }
}

void SpawnManager::DestoryObject(Rect* rect)
{
    for (SpawnObject* spawnObject : spawnObjects)
    {
        if (spawnObject->IsCollision(rect))
        {
            spawnObject->Destroy();
            score++;
            return;
        }
    }
}
