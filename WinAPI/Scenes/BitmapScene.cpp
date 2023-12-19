#include "Framework.h"
#include "BitmapScene.h"

// �ָ��� ���� : �����ߴ� ������� �� ����
// 
// �׸� ���, �̵�, �浹, ���� ��ü, �浹�� ����, ����, ����... �׸��� ��ȣ�浹����
// �����ϸ� ���ĵ�

BitmapScene::BitmapScene()
{
    //memDC���� ���� �Ҵ� (���ο� ���� ����)
    HDC _hdc = GetDC(_hWnd);              //���� ����� ������ �޾ƿͼ�
    memDC = CreateCompatibleDC(_hdc);
    stretchDC = CreateCompatibleDC(_hdc); //��Ʈ��ġ�� ��¼ҵ� �����
    alphaDC = CreateCompatibleDC(_hdc);

    //�ش� ����� ������ ���� ������ ����, ������ ��� ��Ҹ� �����
    ReleaseDC(_hWnd, _hdc); // �� �������� ����� ����(�޸𸮸� ���� �����ϰ�)
    // ������ ����� ������ �޸𸮸� �������� �ʰ�

//��� ��Ҹ� ���� ��, �׸� ������ �ҷ�����

    artist = (HBITMAP)LoadImage(hInst, L"Textures/background.bmp",
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    // (HBITMAP) : ����ȯ, ��Ʈ������ �Ʒ� ����� �ٲٱ�
    // LoadImage : �׸� ������ ��Ʈ �����ͷ� �б�
    // �Ű����� - hInst : �� ��
    //           L"Textures/doggo.bmp" : ������ ��ü ���. �ַ�� ���� ����, ���� ��ȣ�� /
    //           IMAGE_BITMAP : ����� ����
    //           0, 0 : �б⸦ ������ ��ġ (=ó������)
    //           LR_LOADFROMFILE : "���Ϸκ��� ����" ������� �б�

    // �� �Լ���, ��ũ�� �ִ� �׸� �����͸� RAM�� �ø���
    // �� ���õ� �Լ��� ����� ���ؼ� ȿ�������� (Ȥ�� ��ġ�� VRAM ������) �����͸� �ø� ���� ������,
    // �⺻������ �ۿ��� �׸��� �ٷ� ���� ��ü�� �̷� "�޸𸮿� �׸� �ø���" ����� ���ٴ� �� ����
    // ---> �׷��� ���� �׷��� ī���ϼ��� VRAM�� ����, RAM�� �������� ������ �� ���ư���

    human = (HBITMAP)LoadImage(hInst, L"Textures/Idle.bmp",
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    humanRun = (HBITMAP)LoadImage(hInst, L"Textures/Run.bmp",
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    humanATK = (HBITMAP)LoadImage(hInst, L"Textures/Idle_1_Attack.bmp",
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    human2 = (HBITMAP)LoadImage(hInst, L"Textures/Idle_2.bmp",
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    // �׸� ���� �̸��� ���ڰ� �ø� �׸� ���� ���� ���� ��

    //----------------------

    // �׸� ���� �ʱ�ȭ (0����)

    actIndex1 = 0;
    actIndex2 = 0;

    // �߰� �׸� ���� �ʱ�ȭ
    actIndex1Run = 0;
    actIndex1ATK = 0;

    actCode = 0; //�� �ֱ�

    // ���� ���θ� �ʱ�ȭ
    isReverseIndex1 = false;
    isReverseIndex1Run = false;
    isReverseIndex2 = false;

    // �ð��� ���� ������ �ʱ�ȭ
    currentTimeElapsed = 0; //���� ��� �ð� 0
    interval = 1;           //������ 1
    animateSpeed = 10;      //�ӵ��� �� (�ʿ��ϸ� �� ���� ����, ���� ����)

    //ĳ������ ��ġ (�޾Ƽ�) �����ϱ�
    characterPosition = { 0, 0 };
    characterArea = new Rect(Vector2(256, 256), Vector2(512, 512));

    float sizeX = 200;
    float sizeY = 300;
    float posX = 256;             // 256 : ���� �ִ� ĳ���� (�׸�) ������ ��ġ
    float posY = 512 - sizeY / 2; //512 : ĳ���� (�׸�) ������ ũ�⿡�� ĳ���� (�浹) ������ ũ�⸦ �� ��

    characterHit = new Rect(Vector2(posX, posY), Vector2(sizeX, sizeY));

    //���� �����

    platform = new Rect(Vector2(CENTER_X, WIN_HEIGHT - 100), Vector2(300, 300));

    //Ÿ�� fx �����

    fx = new HitFX(Vector2(-1000, -1000), Vector2(300, 600));
    //����� �����
    fx->Active() = false;
}

BitmapScene::~BitmapScene()
{
    // �� ���� ���� ��
    DeleteDC(memDC); // �� ������ ��ü�� �޸𸮿��� ���ֱ�
    DeleteDC(stretchDC);

    // ��Ʈ�ʵ� ���̳� �귯��ó�� ��� ������, ������ �� �� ����� ����
    DeleteObject(artist);
    DeleteObject(human);

    //������ �ν��Ͻ� �����
    delete characterArea;
    delete platform;
    delete fx;
}

void BitmapScene::Update()
{
    // ��� �ð��� ������ ������ŵ�ô�.

    currentTimeElapsed += DELTA * animateSpeed; //����� �ð���ŭ�� ���� (�ӵ� ����)

    // �ٸ� ���� ���� ĳ������ �׸��� �浹 ������ ����ȭ����
    UpdateHitToAreaPos();
    //���� ĳ���Ͱ� ������ Ŭ������ �и��ȴٸ�, �� �Լ��� ĳ���͸� ���� ���� �մϴ�.
    //fx ������Ʈ
    fx->UpdateThis();

    if (currentTimeElapsed >= interval)
        //if (KEY_DOWN(VK_LBUTTON)) //���콺 ��Ŭ��(����)
    {
        //�ð��� ������ �Ѿ����, �Ѿ ��ŭ�� �ٽ� ���ų�, 0���� ����
        currentTimeElapsed -= interval;


        //�ൿ �ڵ忡 ���� �ٸ� �׸� ���� ������
        // ���� : ��������� ���θ� Ȯ���ϰ� �ε����� 1 ���ϰų� 1 ����
        if (actCode == 0 && !isReverseIndex1) actIndex1++;
        else if (actCode == 0 && isReverseIndex1) actIndex1--;
        else if (actCode == 1 && !isReverseIndex1Run) actIndex1Run++;
        else if (actCode == 1 && isReverseIndex1Run) actIndex1Run--;
        else if (actCode == 2 && isATKing) actIndex1ATK++;

        if (!isReverseIndex2)
        {
            actIndex2++;
        }
        else actIndex2--;


        // +1 ���� �ڱ� ���� ������ ǥ�������ν� �ڱ⸦ ǥ���ϴµ�...
        // -> ������ �׸��� �ִ� ������ �Ѿ�� �� �ɰ�!
        //���ʿ� ���ǹ����� �����ϰų�...
        //...Ȥ�� ��� ���Ŀ� ����
        if (actIndex1 > lastIndex1)
        {
            //actIndex1 = actIndex1 - lastIndex1; // ���꺸��
            //actIndex1 = 0; //��������

            //��������� ������ ���
            actIndex1 = lastIndex1; //������ �������� ����
            isReverseIndex1 = true; //����� ����
        }
        if (actIndex2 > lastIndex2)
        {
            //actIndex2 = actIndex2 - lastIndex2; // ���꺸��
            //actIndex1 = 0; //��������

            actIndex2 = lastIndex2;
            isReverseIndex2 = true;
        }
        if (actIndex1Run > lastIndex1Run)
        {
            //actIndex1Run -= lastIndex1Run; //���꺸��

            actIndex1Run = lastIndex1Run;
            isReverseIndex1Run = true;
        }
        if (actIndex1 < 0)
        {
            actIndex1 = 0; //������� ���� ���� ���� (���� ����) ���� ����� ���
            isReverseIndex1 = false;
        }
        if (actIndex1Run < 0)
        {
            actIndex1Run = 0;
            isReverseIndex1Run = false;
        }
        if (actIndex2 < 0)
        {
            actIndex2 = 0;
            isReverseIndex2 = false;
        }

        if (actIndex1ATK > lastIndex1ATK) //�ִϸ��̼� ����Ŭ(����)�� ������ �� ��
        {
            actCode = 0;      //������ �ƴ� �� �ֱ�� �ൿ ��ȭ (=���� ����)
            isATKing = false; //���� �� ������ ��������
            actIndex1ATK = 0; //�ε����� ����
        }
    }

    // ��Ŭ���� �ϸ� �׸��� �ٸ� �ɷ� �ٲ� ����??
    if (KEY_DOWN(VK_RBUTTON))
    {
        // ���� �ڵ� : �ൿ �ڵ� �ٲٱ�
        // ��Ŭ���� �� ������ �ൿ�� �ڵ带 �ٸ� ������ �ٲٱ�
        if (actCode == 0)
        {
            actCode = 1;
            actIndex1Run = 0; //�޸��� �׸��� ������ 0���� �縮��
        }
        else
        {
            actCode = 0;
            actIndex1 = 0; //�� �ֱ� �׸��� ������ �縮��
        }
    }

    //ȭ��ǥŰ�� ������ �� �ൿ �ڵ尡 (ĳ���� �����) �ٲ��

    if (KEY_DOWN(VK_LEFT))
    {
        actCode = 1; //�޸��� ����

        isLeft = true;
    }
    if (KEY_DOWN(VK_RIGHT))
    {
        actCode = 1; //�޸��� ����

        isLeft = false;
    }

    if (KEY_UP(VK_LEFT))
    {
        actCode = 0; //�޸��� ��, ���� ����
    }
    if (KEY_UP(VK_RIGHT))
    {
        actCode = 0;
    }

    // ȭ��ǥŰ�� ������ ���� ��, ĳ���Ͱ� �¿��

    if (KEY_PRESS(VK_LEFT))
    {
        characterArea->Pos().x -= moveSpeed;
    }
    if (KEY_PRESS(VK_RIGHT))
    {
        characterArea->Pos().x += moveSpeed;
    }

    if (KEY_DOWN(VK_LBUTTON))
    {
        if (actCode != 2)
        {
            actCode = 2;
            isATKing = true;

            fx->Start(characterHit, isLeft);
        }
    }

    //ȭ��ǥŰ�� ���� ������?
    if (KEY_DOWN(VK_UP)) // VK_SPACE�� ���� ��
    {
        //if (isJumping) // ������ �ƴ� ��
        if (jumpCount < 2) // ������ Ƚ���� 2ȸ �̸��� ��
        {
            isJumping = true; //������ �Ѵٰ� ��ȣ�� �ش�
            downForce = 0;    //������ �������� ������ 0���� �ʱ�ȭ
            jumpCount++;      // ������ Ƚ�� +1
        }
    }

    if (isJumping) //������� �ൿ�� �����ߴٸ�?
    {
        float offset = 1; //"�߰� ����"�� ���ϴ� ����

        downForce += gravity * DELTA * offset;
        // ������ �������� �� = �߷� * ��� �ð� * ���� �������� ��� ������Ų �� (�����ϴ� ���� ��� Ŀ����)
        // -> 2D, ���� ��Ģ�� �����ڰ� ���Ƿ� ���� ���

        characterArea->Pos().y -= (jumpPower - downForce);
        //ĳ������ ��ġ�� ������ �ɸ� ���� ������Ų��
        //������ �ɸ� �� = ĳ���� ������ ������ - ���� ������ �ɸ��� ��

        if (characterArea->Bottom() > WIN_HEIGHT) //�÷��̾� ������ �عٴ��� ������ ������ �Ѿ��?
        {
            isJumping = false; //���� ����

            //�÷��̾� ��ġ�� �عٴڿ� �� �°� ����
            characterArea->Pos().y = WIN_HEIGHT - characterArea->GetSize().y / 2;
            //ũ�� / 2�� �������Ѽ� ĳ������ ��ġ�� �� �°� ����

            jumpCount = 0; // ������ Ƚ���� 0���� �ʱ�ȭ
        }
    }

    // ---------------------�̵� ��, ���� �浹�� �Ͼ�� �������� �ϵ�

    if (characterHit->IsCollision(platform))
    {
        //�� �簢���� �ε��ƴ�!

        // �� �簢���� �浹 ���踦 �Ǵ��ϴ� ����� ���� ������ ������
        // ������ C++�� �̿��� ������ �Ǵ��ϴ� ����� ���
        // �߿��� ���� ������ �ƴ϶� ������ �����ϱ�

        // �浹�� �Ǵ��� �� �߿��� �� 1 : ������ ������谡 �߿�

        singleDir = GetCollisionDirection(characterHit, platform);
        //ĳ������ �浹 ������ ������ ��� �ִ����� "�޴´�"

        // 2 : �浹�� �ߴµ�, �� �� ĳ������ ��Ȳ�� ����� �߿�

        // �� : �������� �Ǵ� ��Ȳ�ΰ� �ƴѰ�? ������ �ϰ� �ִ� ���ΰ�?
        // -> "���� ���̶��?"

        // -> �� ���ư���, ĳ���Ͱ� ������ "��"�� ���� ��, �� ĳ���Ͱ� ���� ���� ���̾��°�? �ϴ÷�? ������?

        if (singleDir == ABOVE && isJumping && //�÷��̾ ���̰�, ���� ���̴�
            jumpPower - downForce < 0) //������ - ���Ϸ��� ������� = ĳ���ʹ� �������� ���̶��
        {
            //ĳ������ ��ġ�� ���ǿ� �°� �����ϰ�, ������ ������!

            isJumping = false;

            characterArea->Pos().y = platform->Top() - characterArea->GetSize().y / 2;

            jumpCount = 0;
        }
    }

    //�߰� �浹! (Ÿ�� vs �޸�2)
    if (fx->IsCollision(Vector2(350, 400))) //��ǥ ����
        //������ �޸�2���� ��Ʈ ������ �־ �� �簢���� �浹�ϴ� ���� �������Դϴ�. (����� ���� �浹)
    {
        //�޸�2�� �¾����� ������ ����
        human2isHit = true; //�¾Ҵ�!
        isFading = true;    //"����������!" Ȥ�� "���������!"
        hitTime = 0;        //���� �ð� üũ (0���� �ʱ�ȭ)
    }

    // ** 23. 08. 25. ����:
    //
    //  �޸�2�� "���� ����"�� ������Ʈ�ϴ� �ڵ带 ���� ����
    //  ������Ʈ �Լ� �ȿ��� ó���ϵ��� �ϰڽ��ϴ�.
    //  ���, �̰� �¾ƿ�. ��ũ���� �ǵ��� �� �����̰� �;
    //  ������ ���� �Լ����� �� ó����������... 
    // 
    // ** 23. 08. 25. ���� ��:

    if (human2isHit) // ���� ���¸�, ������ ���¸� �� �� �� ǥ���Ѵ�
    {
        // -> ���? ���ο� ȭ�� ó����!

        //1. �޸�2�� ���� ���
        if (isFading)
        {
            currentAlpha -= DELTA * 500;

            if (currentAlpha < 0)
            {
                isFading = false;
            }
        }
        else
        {
            currentAlpha += DELTA * 500;

            if (currentAlpha > 255.0f)
            {
                isFading = true;
            }
        }

        // ** 23. 08. 25. ����:
        //
        // �޸�2�� ���� �ð��� �߰��� ����ϰڽ��ϴ�.
        // �޸�1�� ����FX(����) ȿ���ֱ� 1�ʿ� ���߾
        // �޸�2�� �°� ���� 1�ʰ� ������ "�¾Ҵ�" ���¿��� ȸ���ϵ��� �ϰڽ��ϴ�. 
        // 
        // ** 23. 08. 25. ���� ��:

        //�޸�2�� ���� �ð��� üũ
        hitTime += DELTA;
        if (hitTime > span)
        {
            human2isHit = false;
        }
    }
    else // �޸��� ���� �ʾҴٸ�
    {
        currentAlpha = 255;
    }

    // �ڿ� ����
    if (!characterHit->IsCollision(platform) && //���� ���� �ƴѵ�
        characterArea->Bottom() < WIN_HEIGHT && // ĳ���� ���� ������ ���̺��� ���� �ִ�
        !isJumping) //���� �� ��Ȳ�� �ƴϾ���
    {
        isJumping = true; //"����" �� �ϴ� ������ �Ͼ�� �� ���� �Ͼ����
        downForce = jumpPower; // �����°� �Ȱ��� ���Ϸ� = ���Ϻ��� �����ϵ���
        //���� ī��Ʈ�� ������ �ְ� ������ �൵ �ǰ�, �� �൵ ���� (�ǵ��� ������ �ƴϴϱ�)
    }
}

void BitmapScene::Render(HDC hdc)
{
    //(���̳� �귯��ó��) �׸��� ����
    SelectObject(memDC, artist); //�� ���

    //�� (Ȥ�� �⺻ ��Ʈ��) ���
    //BitBlt(hdc,
    //    0, 0, //����� ������ ��ġ
    //    WIN_WIDTH, WIN_HEIGHT, //����� �� ũ��
    //    memDC, // ��𼭺��� ����� �����͸� (ȭ�� ������) ���������°�
    //    0, 0,  // ��𼭺��� ���������°�(x, y ��ǥ)
    //    SRCCOPY);  //"�ҽ��� ���� ���·� ����Ѵ�(������ ���� �������� �ʴ´�)"

    // ��Ʈ���� ����ϴ� �� �ٸ� ���(�Լ�)
    // ��Ʈ��ġ �� (�ÿ��� ����ϱ�) : ���� �׸��� �߰��� ������ ũ�Ⱚ�� ���߾ ����ϴ� �Լ�
    // �� �Լ����� �Ű����� �� ���� ũ��� ���� ������ �������� �ٲٸ� �׸��� ���¸� �ٲ� �� �ִ�
    StretchBlt(hdc,
        0, 0,                  //����� ������ ��ġ
        WIN_WIDTH, WIN_HEIGHT, //����� �� ũ��
        memDC,                 // ��𼭺��� ����� �����͸� (ȭ�� ������) ���������°�
        WIN_WIDTH, 0,          // ��𼭺��� ���������°�(x, y ��ǥ) : ������ ���� ��������
        -WIN_WIDTH, WIN_HEIGHT,// � ũ��� �ٲپ (Ȥ�� �� �ٲٰ�) ���������°�
        // Ȥ�� "������ ������ ����ΰ�?" : ���� "���� ������ ������ ũ��"��� ����
        SRCCOPY);              //"�ҽ��� ���� ���·� ����Ѵ�(������ ���� �������� �ʴ´�)"

    //�� �Լ��� Ȱ���ϸ� ��Ʈ���� �¿�����ϴ� ���� ���� (���ϵ�, ȸ�� �) * ȸ���� ��� �ٸ� ����� �� ȿ����������...

    //���̳� �귯�� ��üó�� �׸��� �Ȱ��� ��ü

    //���뿡�� ĳ������ (�׸�) ������ �ѹ� �׸���
    //characterArea->Render(hdc);
    // characterHit->Render(hdc);

    // ���� �������� �ִ� ������ �ִµ�, ������ ���� �׸��� ���ٸ�?
    // �������� �׸��� ������ �̴ϴ�. (1�� ���ô� ������)

    //ĳ���͸� �׸� ��, �¿������ ���Ѱ��鼭 �׸���

    //�ӽ� ���� �߰��� �����
    //1. ������ ���� ũ�� (�������� ����� �� ����������)
    int refSize_X = 128;
    //1. ������ �� �߰� ��ǥ ����
    int leftPlus = 0;
    //2. �¿���� ���ο� ���� ������ 1�� �����
    //   -> "�ش� ��¼��� �ð� ������ �� ���� ������ �׸�"
    HBITMAP stretched = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
    HBITMAP alpha = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);

    //���ǹ� (�����̸� int�� ����)
    if (isLeft)
    {
        refSize_X = -128; //���� ũ�⸦ ������
        leftPlus = 1;     //���� ��ǥ�� +1
    }

    //������� ���� fx�� ������ ���
    //if (fx->Active()) fx->Render(hdc);
    fx->Render(hdc);

    if (actCode == 0)
    {
        //�� ��� ��ҿ� ó���� (������) �׸� ������ �����մϴ�
        SelectObject(memDC, human);
        SelectObject(stretchDC, stretched);

        StretchBlt(stretchDC, //����� �������� �߰��� ��Ʈ��ġ DC��
            0, 0,        // ��� ���� ��ġ
            512, 512,    // ��� ũ��
            memDC,       // ���� ȭ��
            128 * (actIndex1 + leftPlus) - leftPlus, 0, //������ ������ ��
            refSize_X, 128,                  //������ ũ��� ����
            SRCCOPY);

        GdiTransparentBlt(hdc, //����� ȭ��(�����)
            //0, 0, // ����� ������ ��ġ
            characterArea->Left(), characterArea->Top(),
            512, 512,            // <- ����� �� ũ���ε�... "�������� ���� ���� �ִ�"
            stretchDC,           // ��� ȭ���� ������ ���ΰ� (�̹����� ��Ʈ��ġ����)
            0, 0,                // ��� ���������°� (128 �ȼ� �������� ǥ�� ��ü�� ������ �Դ°�?)
            512, 512,            // ������ �׸��� ��� ���� ũ��� ������ ���ΰ� (�ش� �ȵǸ� �ڸ���)
            RGB(255, 255, 255)); // �׸��� ������ ��, <- ���� ������ ������ �����ϰ� ������ ��
    }
    else if (actCode == 1)
    {
        SelectObject(memDC, humanRun);
        SelectObject(stretchDC, stretched);

        StretchBlt(stretchDC, //����� �������� �߰��� ��Ʈ��ġ DC��
            0, 0,        // ��� ���� ��ġ
            512, 512,    // ��� ũ��
            memDC,       // ���� ȭ��
            128 * (actIndex1Run + leftPlus) - leftPlus, 0, //������ ������ ��
            refSize_X, 128,                                //������ ũ��� ����
            SRCCOPY);

        GdiTransparentBlt(hdc, //����� ȭ��(�����)
            //0, 0, // ����� ������ ��ġ
            characterArea->Left(), characterArea->Top(),
            512, 512,          // <- ����� �� ũ���ε�... "�������� ���� ���� �ִ�"
            stretchDC,         // ��� ȭ���� ������ ���ΰ�
            0, 0,              // ��� ���������°� (128 �ȼ� �������� ǥ�� ��ü�� ������ �Դ°�?)
            512, 512,          // ������ �׸��� ��� ���� ũ��� ������ ���ΰ� (�ش� �ȵǸ� �ڸ���)
            RGB(255, 255, 255));
    }
    //ĳ���� �������� ���簢������ �׸���
    //characterArea->Render(hdc);

    // * �����ڿ��� ���� �Ҵ��� ����(actIndex)�� ���ؼ� �׸��� ǥ���ǵ��� �ڵ� ����

    else if (actCode == 2)
    {
        SelectObject(memDC, humanATK);
        SelectObject(stretchDC, stretched);

        StretchBlt(stretchDC, //����� �������� �߰��� ��Ʈ��ġ DC��
            0, 0,        // ��� ���� ��ġ
            512, 512,    // ��� ũ��
            memDC,       // ���� ȭ��
            128 * (actIndex1ATK + leftPlus) - leftPlus, 0, //������ ������ ��
            refSize_X, 128,                                //������ ũ��� ����
            SRCCOPY);

        GdiTransparentBlt(hdc, //����� ȭ��(�����)
            //0, 0, // ����� ������ ��ġ
            characterArea->Left(), characterArea->Top(),
            512, 512,     // <- ����� �� ũ���ε�... "�������� ���� ���� �ִ�"
            stretchDC,    // ��� ȭ���� ������ ���ΰ�
            0, 0,         // ��� ���������°� (128 �ȼ� �������� ǥ�� ��ü�� ������ �Դ°�?)
            512, 512,     // ������ �׸��� ��� ���� ũ��� ������ ���ΰ� (�ش� �ȵǸ� �ڸ���)
            RGB(255, 255, 255));
    }


    // ���2�� �׸��� ���� ������ �׷����ڽ��ϴ�

    //platform->Render(hdc);


    //���� �� �Լ��� ����?
    // 1. ū �׸��� �߶� �� �� �ִ� (���ϴ� �κи� �� �� �ִ�)
    // 2. �׸��� �ִ� ����� �����ϰ� ���� �˸��̸� �� �� �ִ�
    //    -> "���� �׸�" Ȥ�� "���� �� ĳ����" "UI" ���� �͵��� ǥ���ϱ⿡ ����

    SelectObject(memDC, human2);
    SelectObject(stretchDC, stretched);
    SelectObject(alphaDC, alpha);

    // ** 23. 08. 25. ����:
    // 
    // ���� �߿��� �߰��� ��� SelectObject�� �� ������ ��ҽ��ϴ�.
    // ��� �̷��� �½��ϴ�. ���� �߿�, (�� �׷��� �ڵ带 �������� �����鼭 �������)
    // ��ũ���� �����̴� ������ �����̶� �ٿ����� �;����.
    // 
    // ** 23. 08. 25. ���� ��:

    //�޸�2�� ������ ������ + ���� ���, "��������" ���¸� �׸����� ǥ��

    // -> ���� �Ŀ� �׸��� �����̴� ������ ǥ���Ϸ��� �Ѵ�!
    // -> �׸��� �����δٴ� ����? ������ �׸��� ������ٴ� ��! (�ܼ�)
    //    Ȥ�� �׸��� ������ ����������

    // * ���� R, G, B��� �ؼ� �� ���� ������ �ִٰ� �˷��� �ִµ�
    //   ����� ��ǻ�Ͱ� ó���ϴ� ���򿡴� �� ���� �Ӽ��� �� �ִ�.

    //   �װ��� �ٷ� "����"��� �Ҹ��� ����(��¥�δ� "���� �Ұ���") ��.

    //   �� ����=���úҰ����� ������ ���� ���������� (���̰�)
    //   ���úҰ����� ������ ���� ���������
    //   0�� �Ǹ� ���� ������ �ʰ� �ȴ�

    // ** 23. 08. 25. ����:
    // 
    //  ������ ��Ÿ���� ���ؼ��� ���� ������ ��Ĩ�ϴ�.
    //  1. �̹��� DC ����ϱ� (���߿� ���İ��� ����ϸ鼭 �׸����� ��Ƶ鿡 �ϱ� ����, ���� ȭ���� �޾ƿ��� ��)
    //     Bitblt�� �Ἥ ������ ������ �� �ֽ��ϴ�.
    //     ���� ������ hdc -> alphaDC
    //     (���� �߿��� ���θ����� �� ������ ���߷Ȱ�, �̰� ������ �׸��� "�ջ���" ������ ��� ��� ���� ��İ� ���Ծ��!)
    // 
    //  2. �׸����� �׸��� ���� �ڸ���, �ø��鼭 ������ �����ϱ�
    //     �¿������ ���  stretchBlt �Լ��� ������ �� �ֽ��ϴ�.
    //     ���� ������ memDC -> stretchDC
    //     ������ ���� �̹����� stretchDC�� ��Ʈ�� stretch�� ���ϴ�.
    // 
    //  3. ������ �� �׸����� �ٽ� Ư���� ���� ���� �ٽ� �׸���
    //     �ִϸ��̼� ��¿� ��� GdiTransparentBlt�� �����մϴ�.
    //     ���� ������ stretchDC -> alphaDC
    //     ��, ���� alphaDC�� �̹����� �� ���� ���Ȱ� �Ǿ����. ���� �־��� ������, ���� �� ���� ��¥ �̹���.
    // 
    //  4. ���� DC���� �������� ���� �̹����� ������ �����ϱ�
    //     GdiAlphaBlent�� ����մϴ�.
    //     �׸��� �׳� �����ϰԸ� ����� ���� �ƴ϶� ���� �־��� ȭ��� ��Ƶ�� ����� ����
    //     ���������� �׸��� ������ ���� ���ο� ȭ�Ҹ� �����, �ټ� ������ ������ ��Ĩ�ϴ�.
    //     (�׷��� ���� ������ �޾ƾ� �ߴ� �̴ϴ�.)
    //     �׸��� �� ��� ������ ������ ����, �ش� �������� ������� '������ �׸�'��
    //     ��¥ �����, hdc�� ������ݴϴ�.
    // 
    //     ���� ������ alphaDC -> hdc
    //
    // 
    // ** 23. 08. 25. ���� ��:

    //���� ��� �κ�, �Ű����� �ּ� ����

    BitBlt(alphaDC,
        0, 0,     //����DC�� ��𼭺��� ������� ä������ ���ΰ�?
        512, 512, //��� �������� ������� ����� ���ΰ� (�󸶳� �����ұ�?)
        hdc,
        200, 210, //��𼭺��� ������� ä������ ���ΰ�? (=���߿� ĳ���� �׷��� �� ��ġ!)
        SRCCOPY);

    // ** 23. 08. 25. ����:
    // 
    // ���߿�, �̷� ������� ����� ���� Ŭ������ �̾Ƴ� ���
    // SRCCOPY ���� �ִ� ��ǥ ������ �� �ؽ�ó�� ��ġ�� �ݿ����־�� �մϴ�.
    //
    // ** 23. 08. 25. ���� ��:

    StretchBlt(stretchDC, //����� �������� �߰��� ��Ʈ��ġ DC��
        0, 0,                         // ��� ���� ��ġ
        512, 512,                     // ��� ũ��
        memDC,                        // ���� ȭ��
        128 * (actIndex2 + 1) - 1, 0, //������ ������ �� (�׸��� �����ϴ� �Ŷ�, ���� BitBlt�� �Ű澲�� �ʾƵ� �˴ϴ�.)
        -128, 128,                    //������ ũ��� ����
        SRCCOPY);

    GdiTransparentBlt(alphaDC, //����� ȭ��(�����)
        0, 0,              // ����� ������ ��ġ
        512, 512,          // <- ����� �� ũ���ε�... "�������� ���� ���� �ִ�" (�׸��� �����ϴ� �Ŷ�, ���� BitBlt�� �Ű澲�� �ʾƵ� �˴ϴ�.)
        stretchDC,         // ��� ȭ���� ������ ���ΰ�
        0, 0,              // ��� ���������°�
        512, 512,          // ������ �׸��� ��� ���� ũ��� ������ ���ΰ� (�ش� �ȵǸ� �ڸ���)
        RGB(255, 0, 255)); // �׸��� ������ ��, <- ���� ������ ������ �����ϰ� ������ ��

    // �� human2 �׸����� ���� £�� ����� (��ȫ��) : 2D ���� ��� ���� ���� ���̴� ����
    // �Ϻη� �׸� ���Ͽ��� ����� �� ������ ĥ�ϰ�(�׸��� ������) -> �� ���� �����ϰ� �����
    // �� �ս� ���� ���� ȿ�������� �׸��� ǥ���س� ���ɼ��� ����

    // * ��ȫ���� RGB�� 255, 0, 255
    // winAPI������ MAGENTA ��� �Ѵ� (���� ����� �ҷ����ų�, #define���� �����ϸ� ��)
    // #define MEGENATA RGB(255, 0, 255) <- �뷫 �̷���

    /// * ���� �Լ��� ���� �������� ȣ��

    // BLENDFUNCTION : �׸� ����(Ư�� ���� ��)�� ���� ������ ����ü
    blend.SourceConstantAlpha = currentAlpha;

    GdiAlphaBlend(hdc,
        200, 210,   //��� ��� (=Ȥ�� ĳ������ ��ġ)
        512, 512,   //����� ũ�� (Ȥ�� �ؽ�ó�� ũ��)
        alphaDC,    //�̰� ����DC���� ������ ��� �����ϰ�, ���� hdc�� �ѷ��ݴϴ�!
        0, 0,       //0, 0 : ������ �������� ��� ����� ����� �°���
        512, 512,   //����� DC�� ũ�⵵��.
        blend);     // ������ ���� ���� ����ü�� �Ἥ ������ ����!

    DeleteObject(stretched);
    DeleteObject(alpha);
}