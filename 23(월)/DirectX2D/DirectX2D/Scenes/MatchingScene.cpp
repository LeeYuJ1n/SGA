#include "Framework.h"
#include "MatchingScene.h"


// 23�� ���� : ��1

// ����/�ʽ����� ���ư���

// ����, Ȥ�� ����Ʈ ���� ���� !@#$%^&* ���� �̿��� ��õ�� �� �ϳ��� C++�� �ۼ��غ���
// (���߹迭, ��ǥ ���� ������ �ٽ� �ǻ츮�� ���� ����)

// ���� / ����

// ���� �̿ϼ��� �� ���� �������� ������� ������ �����ô�.
// (��, ���� �ϼ��� ���̱� ������ ��� �ʼ�)


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

}

void MatchingScene::SwapCard(int card1, int card2)
{

}

bool MatchingScene::IsSameCard()
{
    return false; // �ӽ�
}

bool MatchingScene::IsOnSameLine(POINT coord1, POINT corrd2)
{
    return false; // �ӽ�
}

bool MatchingScene::IsOnSameLineIncludeSelf(POINT coord1, POINT coord2)
{
    return false; // �ӽ�
}

bool MatchingScene::IsUTurn(POINT coord1, POINT corrd2)
{
    return false; // �ӽ�
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
    EmptyDir tmp; //�ӽ�
    return tmp; // �ӽ�
}