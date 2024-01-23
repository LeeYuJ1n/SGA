#include "Framework.h"
#include "MatchingScene.h"


// 24�� ���� : ��1

// ���� 1����

// -> ī�带 Ŭ���ϸ� �� ���콺 Ŀ���� ī�� ����� �����Ǿ ����ٴϰ� ���ּ���.
//    Ŭ���� ���� �̺�Ʈ, ���콺 ��ġ �ޱ� ���� ������ ���մϴ�.

// -> Ÿ�� ��ġ�� ���� ���� �ʵ� ���信 ���ؼ� �˻��ؼ� �ʱ��ϰ� �÷��ּ���.

// ���� ���� (���� ������ �ƴ����� �߰��� �ð� ���� �ѹ� �����غ��ô�)

// -> �ؽ�ó �ڸ��� + Ÿ���� ��Ģ�� ��ġ + Ŭ���� ��ȣ�ۿ� ���� �̿��ؼ�...
//    �����̵� ������ �ѹ� �����غ��ô� (DX �������)


//-----------------------------------------------

// 25�� ���� : ���̳ʸ� ������ ������ Ŭ���� ����

// ���̳ʸ� ����, ������ : ���̳ʸ� �˰����� ���� �� �ϳ�, ��ǻ�� ������ ���� ������� �д� ��

// �������� ���� ������̶� ���� ������ ������, ���ҿ� ���̸� ����� ���� ȿ���� ���⵵ �Ѵ�

// (* ����, �������� ��� �츮�� �˰��� �� ��ü�� ���� ���� �ƴϴ� : DX,Windows�� ����� �Ἥ
//    ���� ������ ������ �а� ���ڴٴ� ��)



MatchingScene::MatchingScene()
{
    //ī�� �ؽ�ó�� ���� ����
    LoadTextures();
    //ī�带 �����ϰ� (���ͷ�)
    CreateCards();
    //������ �ڼ���
    ShuffleCard();

    // ī�� ����(void*) �Լ��� ������ ������� ī��鿡 ����
    Observer::Get()->AddParamEvent
    ("SelectCard", bind(&MatchingScene::SelectCard, this, placeholders::_1));

    // �� �ʿ��� �� ������ �ͼ� �ۼ�...
}

MatchingScene::~MatchingScene()
{
    for (Card* card : cards)
        delete card;
}

void MatchingScene::Update()
{
    if (firstSelectedCard != nullptr)
    {
        //���õ� ī�尡 ������ ���� ���� ��� ����

        deleteTime += DELTA;

        if (deleteTime > timeToResetCard)
        {
            //isDeleteDelay = true;
            DeleteMatchCard();
        }
    }

    //��ü ī�� ������Ʈ
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
    // ��ü ���� (�⺻ �������� ��� ���� ���ϱ�)
    UINT totalCardNum = baseAmount * PAIR;

    //������ �μ� ��� ����
    vector<UINT> factors; // �μ� ����
    for (UINT i = 1; i <= totalCardNum; ++i)
    {
        if (totalCardNum % (i) == 0)
            factors.push_back(i); //������ �μ� ��Ͽ� i�� �߰�
    }

    //�μ� ����� ũ�� ���� �߶� �ϳ� �� �ޱ� (�μ��� A, B�� B, A�� ���� ���̴ϱ�)
    UINT halfFactors = factors.size() / 2;

    //������ �μ� ����� ��ü ũ�Ⱑ Ȧ���� �� �߰��� �ش��ϴ� �μ��� ����,
    //¦���� ���� �߰��� ����� ���ͻ� ��ġ�� �ش��ϴ� �μ��� �Ἥ,
    //�̹� ���ӿ� �� ���ο� ���θ� ���ϱ�
    if (factors.size() % 2 == 0)
    {
        width = factors[halfFactors];
        height = factors[halfFactors - 1]; //������ �� �μ��� �� ���ڸ���
        
        // �� : 1 2 3 4 5 6 7 8 9 0 �̶�� ����� ������ �� �߿���
        //      1 2 3 4 [5 6] 7 8 9 0 <- 5�� 6 ���
    }
    else //Ȧ����
    {
        width = factors[halfFactors];
        height = factors[halfFactors];

        // �� : 1 2 3 4 5 6 7 8 9 ��� ����� ������ �� �߿���
        //      1 2 3 4 [5] 6 7 8 9 <- 5�� ���
    }
    // ��ġ�� ���� ��, �ִ��� ���簢���� ����� ���簢���� ������� �ϴ� ���� ����
    // �� ���ǹ��� �ٸ� ������ Ȱ�� ����

    // ũ�� ���ϱ�� �ؽ�ó (ù ��°) �ֱ���� �� �濡
    Vector2 size = Texture::Add(cardTextures[0])->GetSize() * cardScale;

    //��ü ����� ũ��
    Vector2 totalHalfSize = size * Vector2(width, height) * 0.5f;
    //����� ������
    Vector2 boardOffset = Vector2(CENTER_X, CENTER_Y) - totalHalfSize + size * 0.5f;
    // ī�� 1~�ݰ� ���� ����

    //��ġ

    cardBoard.resize(height); //�� = y�� ��ŭ ��������
    for (vector<Card*>& vec : cardBoard)
        vec.resize(width);

    for (UINT y = 0; y < height; ++y) //y : j ��� �� ��
    {
        for (UINT x = 0; x < width; ++x) //x : i ���
        {
            Vector2 pos = boardOffset + Vector2(x, y) * size;

            UINT index = (y * width + x) / PAIR; //1���� 60���� ���ڸ� ������ �� ��� ����ŭ ������
            Card* card = new Card(cardTextures[index]); //�ε����� �ش��ϴ� ���� �̸����� �ؽ�ó �� ī�� ����
            // -> �� ������ ��� ����ŭ�� ī�尡 ������ ��

            //������� ī�� ����
            card->Pos() = pos;
            card->Scale() = card->Scale() * cardScale; //������� ���� ũ�� ������ŭ ����
            card->SetCoord(x, y); //ī�尡 ���� ���� ��ǥ�� x, y�� �ο�

            cards.push_back(card); //������� ��ü ī�� ���Ϳ� �߰�
            cardBoard[y][x] = card; // �ʱ�ȭ�� ī�� ������ �ش� ��ǥ���� �� ī�带 �Ҵ�
        }
    }
}

void MatchingScene::LoadTextures()
{
    // �ؽ�ó ������ ���� ���� �̸� ���� ������ �� ī�带 ���� �غ��ϴ� �ܰ�

    // *�������� ���� �Լ� �� ���� ��� (�ʿ��ϸ� �˻�; "�̷� �� �ֱ���" ����)

    WIN32_FIND_DATA findData; // �ϵ忡�� ������ ã��
    HANDLE handle = FindFirstFile(L"Textures/Cards/*.png", &findData);

    // WIN32_FIND_DATA : �ϵ�(Ȥ�� ��ũ)�� �ִ� ������ ������ ��� �����ϴ� ����ü
    // HANDLE = ��ü�� void*, �ٸ� �̷� ���·� ���� �������� Ž���� ��� ���� �����ؼ�
    //          �ش� ����� �޾Ƽ� 2�� �������� ���޽�ų ���� �ִ� (�׷��� "�ڵ�")
    //          * �ڵ�, �ڵ鷯 : �䱸���� ������ �߻��� ���(�̺�Ʈ, ���� ����) ���� ����� ���� �Լ��� �����ϴ� ���� (������)

    bool continued = true; // �����Ͱ� ���� �� �ִ��� üũ
    wstring filename; //���� ���� �̸�

    while (continued) //�����Ͱ� ���� �κ��� �ִ� ���� ��� = �˻��� ������ ������
    {
        filename = L"Textures/Cards/"; // ��� ���� ��
        filename += findData.cFileName; //ã�Ƴ� ���� �̸��� ��ģ��

        cardTextures.push_back(filename); // ���� ��ü ��θ��� ���Ϳ� �ֱ�

        continued = FindNextFile(handle, &findData);
        //findData�� ���� ���� �̸��� �ִ��� handle�� ����
        // ������ true ������ false
    }

    // ������� ���� : ���� ���� ��� ���� �̸��� �˻��ؼ� ���Ϳ� �־���
}

void MatchingScene::ShuffleCard()
{
    // �ڼ��� : ���� ���ϰ� ���� ����ϰ�
    // -> ī�尡 ������ �ν��Ͻ��� ���ͼ�, ���� ������ 1�� ���ͷ�, ���� ����� 2�� ���ͷ� ���� ��Ȳ
    // -> � �ǹ̿����� ���� ���⵵ (�ڵ� ���� �Ҿ �� : �׷��� �Լ��� ���� �ѷ� �и�)

    // �и��� �ڼ��� �Լ� : ���� ����� �� �Լ���, ������ ī�带 �ٲٱ� ���� �Ʒ� �Լ�

    for (int i = 0; i < SHUFFLE; ++i)
    {
        int rand1 = Random(0, cards.size()); // ��ü ī�� ���� �߿��� �ƹ� �����̳� �ϳ� ���
        int rand2 = Random(0, cards.size());

        if (rand1 != rand2) SwapCard(rand1, rand2); // ���� ī�� �ٲٱ�� �и��ؼ� �ؿ� �ۼ�
    }
}

void MatchingScene::SwapCard(int card1, int card2)
{
    //��¿� �� ��ġ �ٲٱ�
    Vector2 tempPos = cards[card1]->Pos();
    cards[card1]->Pos() = cards[card2]->Pos();
    cards[card2]->Pos() = tempPos;

    //��ķμ��� ��ġ�� �� ��ǥ�� �ٲٱ�
    POINT tempCoord = cards[card1]->GetCoord();
    cards[card1]->SetCoord(cards[card2]->GetCoord());
    cards[card2]->SetCoord(tempCoord);

    //�ٲ� ��ǥ�� �޾Ƽ� ���忡�� �ݿ��ϱ�
    POINT newCoord1 = cards[card1]->GetCoord();
    POINT newCoord2 = cards[card2]->GetCoord();

    Card* tempCard = cardBoard[newCoord1.y][newCoord1.x]; //���� ��ġ ������ ������ �ν��Ͻ�(��Ī)�� ��ü
    cardBoard[newCoord1.y][newCoord1.x] = cardBoard[newCoord2.y][newCoord2.x];
    cardBoard[newCoord2.y][newCoord2.x] = tempCard;

    // ������� ���� ��ü ī�� (1�� ����) ���� ī�� ������ �ٲ��
    // ������ ��µ� ��ü �ǿ����� �� ī���� ��ġ�� �ٲ��
}

bool MatchingScene::IsSameCard()
{
    // ī�尡 ¦�� �´���, (���Ҿ ���� ���� ī�带 �� ���������� �ʾҴ���)

    // �� ���� ī�带 ������ ���
    if (firstSelectedCard == secondSelectedCard)
    {
        MessageBox(hWnd, L"���� ī�带 �� �� �����߽��ϴ�.", L"Error", MB_OK);
        return false;

        // MassageBox : WinAPI ȯ�濡�� ��� ������ ���� �Լ� �� �ϳ�
        //              �޽����� ���Ե� �˾� â�� ����ִ� ���� ����
        //              WinAPI �� ����� ���� ������ �� ������ �ʴ´�...

        // �Ű����� : hWnd = ���� ������
        //           L"���� ī�带..." = �޽��� �ڽ� ���� ����
        //           L"Error" = �޽��� �ڽ� Ÿ��Ʋ, ���ÿ� ����
        //           MB_OK = �� �޽��� �ڽ����� ��� ��ư, ���� ����.
    }

    // ¦�� �´� ���
    if (firstSelectedCard->GetKey() == secondSelectedCard->GetKey())
        //����� ���� �̸��̰�, ��쿡 ���� Ÿ��ID, ��쿡 ���� �±�.... ���� �����Ͱ� �ְ�����
        // �ƹ�ư ���� �̷� Key-Data�� �����Ѵٸ� �� ���� ���� ������ ���ļ� ������� ��ü��� �Ǵ� ����
        // (�ν��Ͻ��� ���� ���� ���� ���� ����, ���� ���ҽ��� �� ���� ����� Kay-Data�� �ٿ��ָ� ����)
    {
        return true;
    }

    //������� ���� ������ ���� ī��� �ƴѵ�, �׷��ٰ� ¦�� �´� �͵� �ƴ� ���
    MessageBox(hWnd, L"¦�� ���� �ʽ��ϴ�.", L"Error", MB_OK);
    return false;
}

bool MatchingScene::IsOnSameLine(POINT coord1, POINT coord2)
{
    //�׳� ��ǥ�� �ٸ� ���
    if (coord1.x != coord2.x && coord1.y != coord2.y)
    {
        // ��� �޽����� ��� ���� ������, �� ������ Ʋ���� ���� ������ ���� �� �����Ƿ� �޽��� ����
        return false;
    }

    // ���� ���� ��� (���� ������ = ���� x)
    if (coord1.x == coord2.x)
    {
        //���� ���� ã��
        int minY = min(coord1.y, coord2.y);
        int maxY = max(coord1.y, coord2.y);

        for (int y = minY + 1; y < maxY; ++y)
        {
            //�߰��� ��ֹ��� �� ������
            if (cardBoard[y][coord1.x]->Active()) return false; // �޽����� ���������� ����
        }
    }

    // ���� ���� ��� (y)
    if (coord1.y == coord2.y)
    {
        //�� �Ÿ� ���� ã��
        int minX = min(coord1.x, coord2.x);
        int maxX = max(coord1.x, coord2.x);

        for (int x = minX + 1; x < maxX; ++x)
        {
            //�߰��� ��ֹ��� �� ������
            if (cardBoard[coord1.y][x]->Active()) return false;
        }
    }

    // ������� ���� x, y ��ǥ �߿� �ϳ��� ��ġ�ϰ� (�� �� ��ġ�ϸ� ���൵ �� �� �Ű�)
    // ���� ���� ��ġ �߰��� ��ֹ��� ���ٴ� ��
    // =���� �� ��ġ�� �����Ѵٴ� ��

    return true;
}

bool MatchingScene::IsOnSameLineIncludeSelf(POINT coord1, POINT coord2)
{
    /*
    if (coord1.x != coord2.x && coord1.y != coord2.y) return false;

    if (coord1.x == coord2.x)
    {
        int minY = min(coord1.y, coord2.y);
        int maxY = max(coord1.y, coord2.y);

        for (int y = minY + 1; y < maxY; ++y)
        {
            if (cardBoard[y][coord1.x]->Active()) return false;
        }
    }

    if (coord1.y == coord2.y)
    {
        int minX = min(coord1.x, coord2.x);
        int maxX = max(coord1.x, coord2.x);

        for (int x = minX + 1; x < maxX; ++x)
        {
            if (cardBoard[coord1.y][x]->Active()) return false;
        }
    }

    return true;
    */

    return IsOnSameLine(coord1, coord2);
}

bool MatchingScene::IsUTurn(POINT coord1, POINT coord2)
{
    EmptyDir dir1 = GetEmptyDir(coord1);
    EmptyDir dir2 = GetEmptyDir(coord2);

    // ������ "�� �ڸ� ����"���� ���

    // ���� ������ ��� : ù ī�嵵 �ش� ���� �����ڸ�, �� ��° ī�嵵 �����ڸ��� ���
    // = ��ǻ� ���� ���� ������ ��Ȳ�̳� �ٸ����� ���

    if (dir1.right && dir2.right) return true;
    if (dir1.left && dir2.left) return true;
    if (dir1.up && dir2.up) return true;
    if (dir1.down && dir2.down) return true;

    // ������� ���� �� ī�尡 �����ڸ���⿣ ���絥,
    // ���Ҳ����ϰ� �̾��� ���ɼ��� �������� �𸣴� ����

    //������...
    for (int x = coord1.x + 1; x < width; ++x)
    {
        POINT tempCoord1 = { x, coord1.y };

        if (cardBoard[tempCoord1.y][tempCoord1.x]->Active())
            break;

        //�߰��� �� �ڸ��� ���ٰ� ���� ī��� ���� ��ĥ �� (���� ����)
        if (IsOnSameLine(tempCoord1, coord2))
            return true;

        POINT tempCoord2 = { x, coord2.y };

        //�ڱ⸦ �����ؼ��� ���� ���� �ȴٸ�... (���� �����ε� ����� �� �ִٵ簡, �������� 1�̶�簡)
        if (IsOnSameLineIncludeSelf(tempCoord1, tempCoord2))
        {
            //�ٽ� �� �� ����� ī��� ���� ī�尡 ������
            if (IsOnSameLine(coord2, tempCoord2))
                return true;
        }
    }

    for (int x = coord1.x - 1; x >= 0; --x)
    {
        POINT tempCoord1 = { x, coord1.y };

        if (cardBoard[tempCoord1.y][tempCoord1.x]->Active())
            break;

        //�߰��� �� �ڸ��� ���ٰ� ���� ī��� ���� ��ĥ �� (���� ����)
        if (IsOnSameLine(tempCoord1, coord2))
            return true;

        POINT tempCoord2 = { x, coord2.y };

        //�ڱ⸦ �����ؼ��� ���� ���� �ȴٸ�... (���� �����ε� ����� �� �ִٵ簡, �������� 1�̶�簡)
        if (IsOnSameLineIncludeSelf(tempCoord1, tempCoord2))
        {
            //�ٽ� �� �� ����� ī��� ���� ī�尡 ������
            if (IsOnSameLine(coord2, tempCoord2))
                return true;
        }
    }

    for (int y = coord1.y + 1; y < height; ++y)
    {
        POINT tempCoord1 = { coord1.x, y };

        if (cardBoard[tempCoord1.y][tempCoord1.x]->Active())
            break;

        //�߰��� �� �ڸ��� ���ٰ� ���� ī��� ���� ��ĥ �� (���� ����)
        if (IsOnSameLine(tempCoord1, coord2))
            return true;

        POINT tempCoord2 = { coord2.x, y };

        //�ڱ⸦ �����ؼ��� ���� ���� �ȴٸ�... (���� �����ε� ����� �� �ִٵ簡, �������� 1�̶�簡)
        if (IsOnSameLineIncludeSelf(tempCoord1, tempCoord2))
        {
            //�ٽ� �� �� ����� ī��� ���� ī�尡 ������
            if (IsOnSameLine(coord2, tempCoord2))
                return true;
        }
    }

    for (int y = coord1.y - 1; y >= 0; --y)
    {
        POINT tempCoord1 = { coord1.x, y };

        if (cardBoard[tempCoord1.y][tempCoord1.x]->Active())
            break;

        //�߰��� �� �ڸ��� ���ٰ� ���� ī��� ���� ��ĥ �� (���� ����)
        if (IsOnSameLine(tempCoord1, coord2))
            return true;

        POINT tempCoord2 = { coord2.x, y };

        //�ڱ⸦ �����ؼ��� ���� ���� �ȴٸ�... (���� �����ε� ����� �� �ִٵ簡, �������� 1�̶�簡)
        if (IsOnSameLineIncludeSelf(tempCoord1, tempCoord2))
        {
            //�ٽ� �� �� ����� ī��� ���� ī�尡 ������
            if (IsOnSameLine(coord2, tempCoord2))
                return true;
        }
    }

    //������� ���� ����� �� �˻��ߴµ� true�� �� ���� ��Ȳ
    
    return false;
}

void MatchingScene::CheckMatchCard()
{
    // ¦�� ���缭 ����� ã�Ƴ��� (ȣ���)

    // 1. ������ ī�� �� �������� �� �״�� ����
    // 2. ī�尡 ¦�� ������ ���� (ī���� ������ ���ƾ�)

    if (!IsSameCard()) return; // 1, 2�� �� �Լ����� �� ó���ϰ� �Լ� ����� true���� ����ǰ�

    // ������� ������ ¦�� �°�, �� �� ī�带 �ٸ��� �����߰�
    // 3. ���� ���� ��
    if (IsOnSameLine(firstSelectedCard->GetCoord(), secondSelectedCard->GetCoord()))
    {
        //ī�带 �� �����
        firstSelectedCard->SetActive(false);
        secondSelectedCard->SetActive(false);
        return;
    }

    // 4. �� ���̴� �ٸ����� U�� ������� �̾����� �� ������ ��
    if (IsUTurn(firstSelectedCard->GetCoord(), secondSelectedCard->GetCoord()))
    {
        firstSelectedCard->SetActive(false);
        secondSelectedCard->SetActive(false);
        return; // ������ ���� �ʿ�� ���µ� ���߿� �ڿ� �ڵ尡 �� ���� ��츦 ���
    }
}

void MatchingScene::DeleteMatchCard()
{
    //ī�� ������ "���õ�" ���� ����
    firstSelectedCard->Select(false); // �����ߴ� ī���� ���� ����
    if (secondSelectedCard != nullptr) secondSelectedCard->Select(false);

    //�� �ȿ����� ������ ����
    firstSelectedCard = nullptr;
    if (secondSelectedCard != nullptr) secondSelectedCard = nullptr;

    //�� ����� ���� ��, ���� ���� ���� (�׷��� ������ �ٽ� ���� ����)
    deleteTime = 0;
    isDeleteDelay = false;
}

void MatchingScene::SelectCard(void* card)
{
    // ī�带 Ŭ���� ���� �� �Ͼ �ϵ�

    // ������ Ʋ�� �Է��� �߰ų�, �ϳ��� Ŭ���ϰ� �ð��� �ʹ� ���� ����
    // ���õ� ���� ��ҵǵ��� �ϰ� �ʹ� (��õ�� �����̸� ���� �׷��ϱ�)

    if (isDeleteDelay) // �ð��� ���� ������ (Ȥ�� �ٸ� ��쿡�� �� �ɼ��� ������)
    {
        DeleteMatchCard();
    }

    // ����� ���� ������ �� ������ �� ��

    Card* selectedCard = (Card*)card; // �Ű������� ī��� ����ȯ�ؼ� ����
    selectedCard->Select(true); // ���õ� ī���� "���õ�" ������ true

    if (firstSelectedCard == nullptr)
    {
        firstSelectedCard = selectedCard; //ù ��° ī�� ������ �ڸ��� ������ ī�� �Ҵ�
        return; //�� �������� ����
    }
    //else if (secondSelectedCard == nullptr)
    //{
    //    secondSelectedCard = selectedCard;
    //}

    //�� �ڵ� : �� ��° �����Ϳ��� �Ҵ��ϴ� �ڵ����� �Ʒ� ������� ���ؼ� �� ������ �մϴ�
    // 1. �� �ڵ带 ���� Ŭ���� �߸��ؼ� �� ���� �� ��, �� �� ī�带 �Ĵٴ� Ŭ������ �� ������ �� �մϴ�
    // 2. ....������ ¦ �������� ��� �񱳸� �ؾ� �Ǵµ� �� �Ϸ� ���� "�� ī��� �� ��° ĭ���� ���� ����" �������?
    // �׷���...

    secondSelectedCard = selectedCard; // ù ��° �����Ͱ� �Ҵ��� ������, �� ��°�� ���� �ʿ� ���� ������ ���� �ֱٿ� �� ī�带 �Ҵ�

    // �׸��� �� ��ٸ� �ʿ� ���� ��� ¦ ���߱�
    CheckMatchCard();

    //������� ���� ¦ ���߱⸦ �� ������ ���� ���� �����鵵 ����
    deleteTime = 0;
    //isDeleteDelay = true; //�̰� true�� ����, ī�� ¦�� �����, �ش� �Լ����� �� ���� false��
    DeleteMatchCard(); // Ȥ�� �׳� ���� ���� �Լ��� ȣ���ص� ������ �̴ϴ�. (���� ȣ���̳�, ȣ��� ��Ȳ�� ������� ����)
}

MatchingScene::EmptyDir MatchingScene::GetEmptyDir(POINT coord)
{
    EmptyDir result;

    //�� ������ Ʈ�� �ִ°��� �Ǻ�

    //������
    for (int x = coord.x + 1; x < width; ++x)
    {
        if (cardBoard[coord.y][x]->Active())
            result.right = false;
    }

    //����
    for (int x = coord.x - 1; x >= 0; --x)
    {
        if (cardBoard[coord.y][x]->Active())
            result.left = false;
    }

    //����
    for (int y = coord.y + 1; y < height; ++y)
    {
        if (cardBoard[y][coord.x]->Active())
            result.up = false;
    }

    //�Ʒ���
    for (int y = coord.y - 1; y >= 0; --y)
    {
        if (cardBoard[y][coord.x]->Active())
            result.down = false;
    }

    // ������� ���� true�� false�� �� ��ǥ �ֺ��� ��Ȳ�� ���´�
    // �ش� �������� ����ü�� �״�� ��ȯ

    return result;
}