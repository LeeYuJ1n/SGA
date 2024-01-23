#pragma once

// "¦ ���߱� ���"

// 1. ī�带 ��ķ� ��ġ
// 2. ī�带 ¦���� Ŭ���մϴ�. (�ϳ� Ŭ�� �ÿ��� ���ø�, �� Ŭ���ؾ� ���� ����)

// 3. �Ȱ��� ī�尡 ¦�� �Ǹ� �������� �Ϸ��� �մϴ�.
// 4. ��, ¦�� �Ǵ� ī�尡 ����� ���� �ٱ��� �־�� �մϴ�.
// 5. �׸��� ¦�� �Ǵ� ī�尡 ����� ���� "��"�� �����ؾ� �մϴ�.
// 6. �׸��� ¦�� �Ǵ� ī���� ���̿� ��ֹ��� ������ �� �˴ϴ�.

class MatchingScene : public Scene
{
public:
    MatchingScene();
    ~MatchingScene();

    virtual void Update() override;
    virtual void Render() override;

private:

    //ī�� ¦ ���߱��̹Ƿ�, ī����� �ʿ��ϴ�
    vector<Card*> cards;
    vector<wstring> cardTextures; // ī�忡 �� ������ �ؽ�ó
    
    //ī��� ���� ��� (2�� �迭)
    vector<vector<Card*>> cardBoard;

    //�迭�� ���� ����
    UINT width;
    UINT height;

    // ī�带 Ŭ������ �� �����͸� ���� ����
    Card* firstSelectedCard = nullptr;
    Card* secondSelectedCard = nullptr;

    //ī�带 Ŭ���ߴµ� ¦�� Ʋ���� ��쿡 ����� ���� ���İ� ����
    float deleteTime = 0.0f;
    bool isDeleteDelay = false; // �����̰� �ߵ��Ǿ��� (Ȥ�� ������ ��Ģ ������ �� ����...)

    // �� ������ �̿��ؼ� ������ �� �ִ� �Լ���

    //ī�� ���� ����(����)
    void CreateCards();
    void LoadTextures();
    void ShuffleCard(); //�ڼ���
    void SwapCard(int card1, int card2); //��ȣ��ü

    //ī�带 ������ ��... �Ǻ��� �Լ�
    bool IsSameCard(); // ���� ī���ΰ�? = ���� �����ų�, �׳� �� ���� ī�带 �� �� Ŭ���߰ų�
    bool IsOnSameLine(POINT coord1, POINT corrd2); // �� ī���� ��ǥ�� ���� ���ΰ�?
    bool IsOnSameLineIncludeSelf(POINT coord1, POINT coord2); // ���� ���̸鼭 ������ ������ �Ǿ� �ִ°�?
    bool IsUTurn(POINT coord1, POINT corrd2); // U�� ¦ ���߱Ⱑ �Ǵ°� = Ȯ���ϰ� ���� ���� �����ϴ°�?

    // �� �� ��ü�� �ϱ� ���� ȣ��� �Լ�
    void CheckMatchCard();

    // �񱳸� �߰�, ¦�� �¾Ƽ�, ¦�� ����� ���� �Լ�
    void DeleteMatchCard(); // ¦ �����

    //ī�� �����ϱ�
    void SelectCard(void* card);


    //���� ã��
    // -> ī�� �ֺ��� ������ �ִ°�?

    struct EmptyDir
    {
        bool up = true;
        bool down = true;
        bool left = true;
        bool right = true;
    };
    EmptyDir GetEmptyDir(POINT coord); // ȣ��� ������ ��ǥ�� �ֺ� ���ڸ� Ž��

    // QoL ���ǿ� �Լ� (Quality of Life) : �ʿ�� ���µ� ������ ���� ��

    UINT SHUFFLE = 1000;     //�ڼ��� ��
    float cardScale = 0.5f;  //ī�� ũ��
    UINT PAIR = 4;           //����� �� (����� �߸��� ���� ����)

    UINT REAL_PAIR = 2; //<- �̰� 2�� ���ذ��鼭 ���� �¾Ҵ�
    
    UINT baseAmount = 15;    //�⺻ ī�� ������ (����� ������ ���� �޴´�)

    float timeToResetCard = 5.0f;
};

