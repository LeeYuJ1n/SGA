#include "Framework.h"

void StageManager::Update()
{
    if (!isPlay) return;

    //update �Լ����� Move�� ���� ȣ���մϴ�.
    //speed�� 0�� �ƴ� ���, �ش� ����ŭ ���������� �̵��մϴ�.

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
    // �� �Լ��� ���� private�Դϴ�. �Ű������� �ʿ�� ���� �ʽ��ϴ�.
    // ��� ������ speed�� �޾Ƽ� �ڱ� ȥ�� �����ϴ� �Լ��� �˴ϴ�.
    // ��ü �������� �þ �ݸ� (ĸ��ȭ ��ȭ, "�̷���") �����̶�� �������� ���� ����, ������ ���� �������̽��� �ƽ��ϴٸ�...
    // ��� �ڵ尡 �������! ��ó�� ���α׷����� �̷п� ����ϰ�, �������� ��� �ڵ尡 ������ �������� ���� ���� �ֽ��ϴ�.

    // �� �Լ��� Update���� ȣ���մϴ�. (Update �Լ� ����)
    // ���� ����, Move �Լ��� ������ ������ �ʰ�, �ڱ� �ȿ��� ó���ϵ��� �ϰڽ��ϴ�.
    // (Landspace.cpp 25��° �ٿ��� ��� ����)

    for (pair<string, Objects> objects : totalObjects)
    {
        for (GameObject* object : objects.second)
        {
            object->Update();

            ImageRect* rect = (ImageRect*)object;

            rect->pos.x -= speed;
            //rect->pos.y += �߰� ��� ���� �ʿ�

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
                //������ �������� ������ ���⿡ �ڵ� �ֱ�
                // 
                // * �������� �Ŵ�¡ ��Ŀ���, �⺻������
                // ������ �������̳� ��ֹ��� "��"��
                // ���� ������� ����� �˴ϴ�.
            }
                break;
            case StageManager::OBSTACLE:
            {
                //��ֹ��� ������ ���⿡ �ڵ� �ֱ�
                // 
                // * �������� �Ŵ�¡ ��Ŀ���, �⺻������
                // ������ �������̳� ��ֹ��� "��"��
                // ���� ������� ����� �˴ϴ�.
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
