#include "Framework.h"

void StageManager::Update()
{
    if (!isPlay) return;

    //update 함수에서 Move를 직접 호출합니다.
    //speed가 0이 아닐 경우, 해당 값만큼 스테이지가 이동합니다.

    if (isAutoScroll)
    {
        if (speed != 200.0f) speed = 200.0f;

        for (pair<string, Objects> objects : totalObjects)
        {
            for (GameObject* object : objects.second)
            {
                object->Update();

                ImageRect* rect = (ImageRect*)object;

                rect->pos.x -= speed * DELTA;

                if (rect->Right() <= 0.0f)
                {
                    rect->isActive = true;
                    rect->pos.x += width * tileSize.x;
                }

                if (rect->Left() >= WIN_WIDTH)
                {
                    rect->isActive = true;
                    rect->pos.x -= width * tileSize.x;
                }
            }
        }
    }
    else Move();
}

void StageManager::Render(HDC hdc)
{
    vector<GameObject*> grounds = totalObjects["Ground"];

    for (GameObject* ground : grounds)
    {
        ImageRect* rect = (ImageRect*)ground;
        rect->Render(hdc);
    }

    vector<GameObject*> pickups = totalObjects["Pickup"];

    for (GameObject* pickup : pickups)
    {
        pickup->Render(hdc);
    }

    vector<GameObject*> obstacles = totalObjects["Obstacle"];

    for (GameObject* obstacle : obstacles)
    {
        ImageRect* rect = (ImageRect*)obstacle;
        rect->Render(hdc);
    }

    SetTextColor(hdc, WHITE);

    wstring str = L"Score : " + to_wstring(score);
    TextOut(hdc, CENTER_X, 10, str.c_str(), str.length());
}

void StageManager::Move()
{
    // 이 함수는 이제 private입니다. 매개변수를 필요로 하지 않습니다.
    // 멤버 변수인 speed를 받아서 자기 혼자 동작하는 함수가 됩니다.
    // 객체 독립성이 늘어난 반면 (캡슐화 강화, "이론적") 게임이라는 목적에는 맞지 않은, 통제력 없는 인터페이스가 됐습니다만...
    // 대신 코드가 깔끔하죠! 이처럼 프로그래밍의 이론에 충실하고, 목적에서 벗어난 코드가 오히려 실전성이 강할 수도 있습니다.

    // 이 함수는 Update에서 호출합니다. (Update 함수 참조)
    // 지형 역시, Move 함수를 별도로 만들지 않고, 자기 안에서 처리하도록 하겠습니다.
    // (Landspace.cpp 25번째 줄에서 계속 참조)

    for (pair<string, Objects> objects : totalObjects)
    {
        for (GameObject* object : objects.second)
        {
            object->Update();

            ImageRect* rect = (ImageRect*)object;

            rect->pos.x -= speed;
            //rect->pos.y += 추가 멤버 변수 필요

            stageProceeded += speed;

            if (rect->Right() <= 0.0f)
            {
                rect->isActive = true;
                rect->pos.x += width * tileSize.x;
            }

            if (rect->Left() >= WIN_WIDTH)
            {
                rect->isActive = true;
                rect->pos.x -= width * tileSize.x;
            }
        }
    }
}

float StageManager::GetGroundHeight(Vector2 pos)
{
    vector<GameObject*> grounds = totalObjects["Ground"];

    float minHeight = WIN_HEIGHT;

    for (GameObject* ground : grounds)
    {
        ImageRect* rect = (ImageRect*)ground;
        
        if (pos.x < rect->Left() || pos.x > rect->Right())
            continue;

        if (pos.y >= rect->Top())
            continue;

        if (rect->Top() < minHeight)
            minHeight = rect->Top();
    }

    return minHeight;
}

void StageManager::CollisionPickup(GameObject* object)
{
    vector<GameObject*> pickups = totalObjects["Pickup"];

    for (GameObject* pickup : pickups)
    {
        if (pickup->IsCollision(object))
        {
            pickup->isActive = false;
            score++;
            return;
        }
    }
}

bool StageManager::CollisionObstacle(GameObject* object)
{
    vector<GameObject*> obstacles = totalObjects["Obstacle"];

    for (GameObject* obstacle : obstacles)
    {
        if (obstacle->IsCollision(object))
        {            
            return true;
        }
    }

    return false;
}

void StageManager::LoadTileData(string file)
{
    ifstream loadFile(file);

    string temp;

    while (true)
    {
        loadFile >> temp;

        vector<string> datas = SplitString(temp, ",");

        width = datas.size();

        vector<TileType> rowDatas;
        rowDatas.reserve(width);

        for (string data : datas)
        {
            rowDatas.push_back((TileType)stoi(data));
        }

        tileData.push_back(rowDatas);
        height++;

        if (loadFile.eof())
            break;
    }

    tileSize = { WIN_WIDTH / (float)width * 2.0f, WIN_HEIGHT / (float)height };

    CreateTile();
}

void StageManager::CreateTile()
{
    vector<GameObject*> grounds;
    vector<GameObject*> pickups;
    vector<GameObject*> obstacles;

    grounds.reserve(width);
    pickups.reserve(width);
    obstacles.reserve(width);

    Vector2 startOffset = tileSize * 0.5f;

    for (UINT y = 0; y < height; y++)
    {
        for (UINT x = 0; x < width; x++)
        {
            TileType type = tileData[y][x];

            switch (type)
            {
            case StageManager::GROUND:
            {
                ImageRect* ground = new ImageRect(L"Textures/_SampleScene/Ground.bmp");
                ground->pos = startOffset + tileSize * Vector2(x, y);
                grounds.push_back(ground);
            }
                break;
            case StageManager::PICKUP:
            {
                //집어드는 아이템이 있으면 여기에 코드 넣기
                // 
                // * 스테이지 매니징 방식에서, 기본적으로
                // 집어드는 아이템이나 장애물은 "땅"과
                // 같은 방식으로 만들면 됩니다.
            }
                break;
            case StageManager::OBSTACLE:
            {
                //장애물이 있으면 여기에 코드 넣기
                // 
                // * 스테이지 매니징 방식에서, 기본적으로
                // 집어드는 아이템이나 장애물은 "땅"과
                // 같은 방식으로 만들면 됩니다.
            }
                break;
            default:
                break;
            }
        }
    }

    totalObjects["Ground"] = grounds;
    totalObjects["Pickup"] = pickups;
    totalObjects["Obstacle"] = obstacles;
}
