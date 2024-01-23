#include "Framework.h"
#include "MatchingScene.h"


// 23일 과제 : 택1

// 복습/초심으로 돌아가기

// 빙고, 혹은 시프트 숫자 문자 !@#$%^&* 들을 이용한 사천성 중 하나를 C++로 작성해보기
// (이중배열, 좌표 등의 개념을 다시 되살리는 것이 목적)

// 예습 / 도전

// 오늘 미완성된 이 씬을 여러분의 방식으로 끝까지 만들어봅시다.
// (단, 내일 완성할 것이기 때문에 백업 필수)


MatchingScene::MatchingScene()
{
    //카드 텍스처를 읽은 다음
    LoadTextures();
    //카드를 생성하고 (벡터로)
    CreateCards();
    //순서를 뒤섞기
    ShuffleCard();

    // 카드 선택(void*) 함수를 실제로 만들어진 카드들에 배정
    Observer::Get()->AddParamEvent
    ("SelectCard", bind(&MatchingScene::SelectCard, this, placeholders::_1));

    // 더 필요한 게 있으면 와서 작성...
}

MatchingScene::~MatchingScene()
{
    for (Card* card : cards)
        delete card;
}

void MatchingScene::Update()
{
    
    //전체 카드 업데이트
    for (Card* card : cards)
        card->Update();
}

void MatchingScene::Render()
{


    for (Card* card : cards)
        card->Render();
}

void MatchingScene::CreateCards()
{
    // 전체 개수 (기본 생성량에 페어 수를 곱하기)
    UINT totalCardNum = baseAmount * PAIR;

    //가능한 인수 목록 제작
    vector<UINT> factors; // 인수 벡터
    for (UINT i = 1; i <= totalCardNum; ++i)
    {
        if (totalCardNum % (i) == 0)
            factors.push_back(i); //가능한 인수 목록에 i를 추가
    }

    //인수 목록의 크기 절반 잘라서 하나 더 받기 (인수의 A, B와 B, A는 같은 쌍이니까)
    UINT halfFactors = factors.size() / 2;

    //가능한 인수 목록의 전체 크기가 홀수면 딱 중간에 해당하는 인수를 쓰고,
    //짝수면 가장 중간에 가까운 벡터상 위치에 해당하는 인수를 써서,
    //이번 게임에 쓸 가로와 세로를 구하기
    if (factors.size() % 2 == 0)
    {
        width = factors[halfFactors];
        height = factors[halfFactors - 1]; //위에서 쓴 인수의 딱 앞자리로
        
        // 예 : 1 2 3 4 5 6 7 8 9 0 이라는 목록이 있으면 이 중에서
        //      1 2 3 4 [5 6] 7 8 9 0 <- 5와 6 사용
    }
    else //홀수면
    {
        width = factors[halfFactors];
        height = factors[halfFactors];

        // 예 : 1 2 3 4 5 6 7 8 9 라는 목록이 있으면 이 중에서
        //      1 2 3 4 [5] 6 7 8 9 <- 5를 사용
    }
    // 배치를 했을 때, 최대한 정사각형에 가까운 직사각형을 만들고자 하는 것이 목적
    // 위 조건문을 다른 곳에도 활용 가능

    // 크기 정하기와 텍스처 (첫 번째) 넣기까지 한 방에
    Vector2 size = Texture::Add(cardTextures[0])->GetSize() * cardScale;

    //전체 행렬의 크기
    Vector2 totalHalfSize = size * Vector2(width, height) * 0.5f;
    //행렬의 시작점
    Vector2 boardOffset = Vector2(CENTER_X, CENTER_Y) - totalHalfSize + size * 0.5f;
    // 카드 1~반개 정도 공백

    //배치

    cardBoard.resize(height); //행 = y축 만큼 리사이즈
    for (vector<Card*>& vec : cardBoard)
        vec.resize(width);

    for (UINT y = 0; y < height; ++y) //y : j 대신 쓴 것
    {
        for (UINT x = 0; x < width; ++x) //x : i 대신
        {
            Vector2 pos = boardOffset + Vector2(x, y) * size;

            UINT index = (y * width + x) / PAIR; //1부터 60까지 숫자를 배정한 후 페어 수만큼 나누기
            Card* card = new Card(cardTextures[index]); //인덱스에 해당하는 파일 이름으로 텍스처 및 카드 생성
            // -> 한 묶음당 페어 수만큼의 카드가 존재할 것

            //만들어진 카드 조정
            card->Pos() = pos;
            card->Scale() = card->Scale() * cardScale; //헤더에서 정한 크기 비율만큼 조정
            card->SetCoord(x, y); //카드가 현재 가진 좌표를 x, y로 부여

            cards.push_back(card); //만들어진 전체 카드 벡터에 추가
            cardBoard[y][x] = card; // 초기화된 카드 보드의 해당 좌표에도 이 카드를 할당
        }
    }
}

void MatchingScene::LoadTextures()
{
    // 텍스처 파일을 여러 개를 미리 읽은 다음에 각 카드를 위해 준비하는 단계

    // *윈도우의 제공 함수 두 가지 사용 (필요하면 검색; "이런 게 있구나" 이해)

    WIN32_FIND_DATA findData; // 하드에서 데이터 찾기
    HANDLE handle = FindFirstFile(L"Textures/Cards/*.png", &findData);

    // WIN32_FIND_DATA : 하드(혹은 디스크)에 있는 파일의 정보를 모아 보존하는 구조체
    // HANDLE = 정체는 void*, 다만 이런 형태로 쓰면 윈도우의 탐색기 기능 등을 수행해서
    //          해당 결과를 받아서 2차 연산으로 전달시킬 수가 있다 (그래서 "핸들")
    //          * 핸들, 핸들러 : 요구받은 조건이 발생할 경우(이벤트, 직접 수행) 조건 결과를 다음 함수에 전달하는 역할 (관리자)

    bool continued = true; // 데이터가 남은 게 있는지 체크
    wstring filename; //들어온 파일 이름

    while (continued) //데이터가 남은 부분이 있는 동안 계속 = 검색된 파일이 있으면
    {
        filename = L"Textures/Cards/"; // 경로 지정 후
        filename += findData.cFileName; //찾아낸 파일 이름을 합친다

        cardTextures.push_back(filename); // 파일 전체 경로명을 벡터에 넣기

        continued = FindNextFile(handle, &findData);
        //findData에 다음 파일 이름이 있는지 handle로 검출
        // 있으면 true 없으면 false
    }

    // 여기까지 오면 : 폴더 안의 모든 파일 이름을 검색해서 벡터에 넣었다
}

void MatchingScene::ShuffleCard()
{

}

void MatchingScene::SwapCard(int card1, int card2)
{

}

bool MatchingScene::IsSameCard()
{
    return false; // 임시
}

bool MatchingScene::IsOnSameLine(POINT coord1, POINT corrd2)
{
    return false; // 임시
}

bool MatchingScene::IsOnSameLineIncludeSelf(POINT coord1, POINT coord2)
{
    return false; // 임시
}

bool MatchingScene::IsUTurn(POINT coord1, POINT corrd2)
{
    return false; // 임시
}

void MatchingScene::CheckMatchCard()
{

}

void MatchingScene::DeleteMatchCard()
{

}

void MatchingScene::SelectCard(void* card)
{

}

MatchingScene::EmptyDir MatchingScene::GetEmptyDir(POINT coord)
{
    EmptyDir tmp; //임시
    return tmp; // 임시
}