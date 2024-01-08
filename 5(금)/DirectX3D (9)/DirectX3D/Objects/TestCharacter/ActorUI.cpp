#include "Framework.h"

ActorUI::ActorUI()
{
    //쿼드 3종
    crosshair = new Quad(L"Textures/UI/cursor.png");
    crosshair->Pos() = { CENTER_X, CENTER_Y, 0 };
    crosshair->UpdateWorld();

    quickSlot = new Quad(L"Textures/UI/QuickSlot.png");
    quickSlot->SetTag("QuickSlot"); // 트랜스폼의 이름을 정하기
    quickSlot->Load();              // 2D 때 맵레벨 등을 불러올 때처럼, 바이너리 리더 클래스를 사용하여,
                                    // 위치, 회전, 크기 정보를 정해진 파일에서 읽어들인다
    quickSlot->UpdateWorld();       // 업데이트

    iconFrame = new Quad(L"Textures/UI/IconFrame.png"); // 아이콘의 "프레임" = 그림을 불러올 때 자리가 되어주거나
                                                        // 인벤토리 관련 조작이라면 "커서"의 역할을 하거나
                                                        // -> 다른 그림과 같이 쓰이거나, 조작을 받기 위한 리소스라서
                                                        // 생성 시점에서는 위치를 생각할 필요는 없다
    //iconFrame->Scale() = { 0.7f, 0.7f, 0.7f }; // 직접 크기 지정
    iconFrame->Scale() *= 0.7f;                  // 상대 크기 지정 (처음 크기에서 70%)
    iconFrame->SetActive(false);                 // 생성 시점에서는 쓸 필요가 없으니까 (다른 그림과 같이 쓰거나, 조작 받는 커서로 쓰거나)

    // 블록의 아이콘도 같이 만들기
    // (게임에 아이템이 나온다면 아이템의 아이콘도 이런 식으로)

    for (int i = 0; i < 5; ++i) // 반복횟수 5 = 블록의 종류
    {
        wstring file = L"Textures/Block/BlockIcon" + to_wstring(i) + L".png"; // 블록 아이콘의 원본 파일을 스트링으로 만들기
        Quad* blockIcon = new Quad(file);
        blockIcon->Scale() *= 0.1f; // 원래 크기에서 10%
        blockIcon->SetParent(quickSlot); // 인벤토리 퀵바를 부모 트랜스폼으로
        blockIcon->SetTag("Icon " + to_string(i));

        blockIcons.push_back(blockIcon); // 만든 블록 아이콘 넣기

        //blockIcon->SetActive(false); // 시작시 아이콘 표기 안 함
    }
}

ActorUI::~ActorUI()
{
    delete crosshair;
    delete quickSlot;
    delete iconFrame;

    for (Quad* blockIcon : blockIcons)
        delete blockIcon;
}

void ActorUI::Update()
{
    if (KEY_DOWN('1')) // 1을 누르면
    {
        if (iconData[0].second > 0) // 블록의 데이터가 값이 있다면
            selectIconIndex = 0; // 해당 블록 선택하기
    }

    if (KEY_DOWN('2'))
    {
        if (iconData[1].second > 0)
            selectIconIndex = 1;
    }

    if (KEY_DOWN('3'))
    {
        if (iconData[2].second > 0)
            selectIconIndex = 2;
    }

    if (KEY_DOWN('4'))
    {
        if (iconData[3].second > 0)
            selectIconIndex = 3;
    }

    if (KEY_DOWN('5'))
    {
        if (iconData[4].second > 0)
            selectIconIndex = 4;
    }
}

void ActorUI::Render()
{
    // 생성시 업데이트월드 했음 -> 나중에 필요하면 렌더 추가하기
}

void ActorUI::PostRender()
{
    // * 뎁스 버퍼에 의한 우선순위 적용됨
    //   이미지가 같은 곳에 그려졌을 때도 해당 이미지가 행렬공간을 계속 점유하지 안혹
    //   코드상 먼저 그려진 쪽이 "밑에" 그 위에 다시 뒤에 그려지는 쪽이 덧그려지면서
    //   여러 이미지가 같은 곳에 존재할 수 있게 된다

    // * 이 뎁스라는 개념은 엔진에서도 적용된다 (2D 이미지끼리 겹쳤을 때 어떤 그림이 위로 가는가?)

    // UI로서 쿼드 출력 (UI버퍼 사용)

    crosshair->Render(); // 렌더를 여기서 호출
    // quickSlot->Render(); // 퀵바도 렌더 호출

    for (int i = 0; i < 5; ++i)
    {
        Vector3 pos;
        pos.x = -80 + (20 * i);

        if (iconData[i].second) //현재 반복문에서 보고 있는 아이콘의 데이터...에 해당하는 진짜 블록 데이터를 봤을 때
        {
            Quad* icon = blockIcons[iconData[i].first]; // 대응하는 아이콘 찾기
            icon->Pos() = pos; // 이 아이콘 위치는 위에 정한 대로
            icon->UpdateWorld(); // 업데이트를 여기서 수행 (아이콘끼리 위치가 바뀌거나 표시 여부가 바뀌는 경우 대비)
            icon->Render(); // 그리고 렌더 (* 뎁스에 의해 퀵슬롯 위에 그려질 수 있게 됨)

            string str = to_string(iconData[i].second); // 블록의 데이터를 문자열로

            Vector3 tmp = icon->GlobalPos();

            Font::Get()->RenderText(str, {tmp.x, tmp.y}); // 위에서 받은 아이콘의 위치에, 블록의 데이터를 문자로 표시

            if (i == selectIconIndex) // 반복문이 선택 중인 아이콘의 데이터를 보고 있다면 (="이 블록 선택 중")
            {
                // 그림이 강조되든, 커서가 나오든, 해당 "자리"를 표시하기 위한....
                // 프레임 쿼드를 출력할 차례

                iconFrame->SetActive(true); // 활성화
                iconFrame->Pos() = icon->GlobalPos(); // 위치 = 선택한 아이콘의 위치
                iconFrame->UpdateWorld(); //업데이트
                iconFrame->Render(); //렌더
            }
            else
            {
                iconFrame->SetActive(false); // 비활성화
            }
        }
    }
}

void ActorUI::GUIRender()
{
    // 아이콘의 프레임 위치 나타내기
    iconFrame->RenderUI();
}

void ActorUI::Pick()
{
    //블록 고르기

    Cube* block = BlockManager::Get()->GetCollisionBlock(); // 광선에 의해 충돌된 = 선택된 블록

    if (block == nullptr) return; // 골라진 게 없으면 그냥 종료

    //있으면 이제부터 진행

    // 텍스처 파일 이름 받아오기
    wstring file = block->GetMaterial()->GetDiffuseMap()->GetFile();

    int tmp = file.find_last_of('.'); // 기준 문자에서 잘린 나머지 데이터의 마지막 순번을 가져오기
    file = file.substr(tmp - 1, 1);   // 위에서 도출한 데이터를 기점으로 해서 한 글자 = 파일의 숫자
    int index = stoi(file);

    if (inventory[index].size() == 0) // 인벤토리의 블록 종류 개수가 0이라면 = 인벤토리에 블록이 없었으면
    {
        for (int i = 0; i < 5; ++i)
        {
            if (iconData[i].second == 0) // 블록 개수도 없었으면
            {
                //처음으로 넣기
                iconData[i].first = index; //새 블록을 아이콘에 배정
                iconData[i].second++; // 개수 +1
                break; //반복종료
            }
        }
    }
    else // 인벤토리에 내용물이 있는 상황이면
    {
        //반복문 돌려서 일치하는 블록에 +1
        for (auto& data : iconData)
            // auto : 맥락에 따라 코드에서 지정된 자료형을 자동으로 감지해주는 명령
            //        정확한 자료형을 선호하는 C++ 특성성 남발하면 문제가 많고...
            //        지금처럼 자료형이 너무 길 때 (맵, 페어 등을 썼을 때, 클래스 관계가 복잡할 때)
            //        한정적으로 쓰면 사람은 편하다
        {
            if (data.second.first == index) // 블록의 종류가 맞으면
            {
                data.second.second++; // 블록의 개수 + 1
                break;
            }
        }
    }

    // 여기까지 오면서 맵에 블록의 보유 정보 (어떤 종류를 몇 개 가졌다)를 기입했다
    // 그러므로 실제 대상 = 포인터로 받은 block도 인벤토리에 넣자

    inventory[index].push_back(block);

    // 이걸로 정보 기입 완료(맵) + 실체도 벡터에 저장 완료(벡터)
    // -> 픽업 종료

}

void ActorUI::Build()
{
    //내가 가진 아이템(블록)에서 꺼내어 외부에 짓기
    if (selectIconIndex < 0) return; // <- 초기화 상태의 "없음"(=-1)에서 입력을 안 했다 = 고른 블록이 없었다

    //고른 블록이 있으면 일단 하나 검출 (선택한 유형의 블록의 벡터의 가장 마지막 개체)
    Cube* block = inventory[iconData[selectIconIndex].first].back();

    if (BlockManager::Get()->BuildBlock(block))
        // 블록 매니저를 호출해서, "이 블록을 써서 짓기"를 했는데 결과가 true = 수행이 됐다면
        // -> 애초에 블록이 없었거나, 호출을 했지만 광선이 기존 블록과 충돌을 안 해 접점이 없었으면 false
    {
        // 벡터에서 블록 빼기 (블록을 썼으므로 인벤토리에서 지울 타이밍)
        inventory[iconData[selectIconIndex].first].pop_back();

        iconData[selectIconIndex].second--; // 블록 개수에서 -1

        if (iconData[selectIconIndex].second == 0) // 블록 개수가 0에 다다르면
        {
            selectIconIndex = -1; // 선택 취소하기
        }
    }
}