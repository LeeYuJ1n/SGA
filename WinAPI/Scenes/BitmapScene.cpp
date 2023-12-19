#include "Framework.h"
#include "BitmapScene.h"

// 주말의 과제 : 진행했던 내용들의 총 복습
// 
// 그림 출력, 이동, 충돌, 동작 교체, 충돌의 방향, 조건, 점프... 그리고 상호충돌까지
// 가능하면 알파도

BitmapScene::BitmapScene()
{
    //memDC부터 값을 할당 (새로운 영역 생성)
    HDC _hdc = GetDC(_hWnd);              //실제 모니터 정보를 받아와서
    memDC = CreateCompatibleDC(_hdc);
    stretchDC = CreateCompatibleDC(_hdc); //스트레치용 출력소도 만들기
    alphaDC = CreateCompatibleDC(_hdc);

    //해당 모니터 정보와 같은 정보를 가진, 가상의 출력 장소를 만든다
    ReleaseDC(_hWnd, _hdc); // 이 데이터의 등록을 해제(메모리를 쓰기 가능하게)
    // 생성된 모니터 정보가 메모리를 차지하지 않게

//출력 장소를 만든 후, 그림 데이터 불러오기

    artist = (HBITMAP)LoadImage(hInst, L"Textures/background.bmp",
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    // (HBITMAP) : 형변환, 비트맵으로 아래 결과를 바꾸기
    // LoadImage : 그림 파일을 비트 데이터로 읽기
    // 매개변수 - hInst : 이 앱
    //           L"Textures/doggo.bmp" : 파일의 전체 경로. 솔루션 폴더 기준, 폴더 기호는 /
    //           IMAGE_BITMAP : 대상의 형식
    //           0, 0 : 읽기를 시작할 위치 (=처음부터)
    //           LR_LOADFROMFILE : "파일로부터 열기" 방식으로 읽기

    // 위 함수로, 디스크에 있던 그림 데이터를 RAM에 올린다
    // 더 세련된 함수나 기능을 통해서 효율적으로 (혹은 위치를 VRAM 등으로) 데이터를 올릴 수도 있지만,
    // 기본적으로 앱에서 그림을 다룰 때는 대체로 이런 "메모리에 그림 올리기" 방식을 쓴다는 건 같다
    // ---> 그래서 고성능 그래픽 카드일수록 VRAM이 많고, RAM이 많을수록 게임이 잘 돌아간다

    human = (HBITMAP)LoadImage(hInst, L"Textures/Idle.bmp",
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    humanRun = (HBITMAP)LoadImage(hInst, L"Textures/Run.bmp",
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    humanATK = (HBITMAP)LoadImage(hInst, L"Textures/Idle_1_Attack.bmp",
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    human2 = (HBITMAP)LoadImage(hInst, L"Textures/Idle_2.bmp",
        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    // 그림 파일 이름은 각자가 올린 그림 파일 명을 따를 것

    //----------------------

    // 그림 순번 초기화 (0으로)

    actIndex1 = 0;
    actIndex2 = 0;

    // 추가 그림 순번 초기화
    actIndex1Run = 0;
    actIndex1ATK = 0;

    actCode = 0; //서 있기

    // 역행 여부를 초기화
    isReverseIndex1 = false;
    isReverseIndex1Run = false;
    isReverseIndex2 = false;

    // 시간에 대한 변수를 초기화
    currentTimeElapsed = 0; //현재 경과 시간 0
    interval = 1;           //간격은 1
    animateSpeed = 10;      //속도는 반 (필요하면 더 낮출 수도, 높일 수도)

    //캐릭터의 위치 (받아서) 설정하기
    characterPosition = { 0, 0 };
    characterArea = new Rect(Vector2(256, 256), Vector2(512, 512));

    float sizeX = 200;
    float sizeY = 300;
    float posX = 256;             // 256 : 위에 있는 캐릭터 (그림) 영역의 위치
    float posY = 512 - sizeY / 2; //512 : 캐릭터 (그림) 영역의 크기에서 캐릭터 (충돌) 영역의 크기를 뺀 것

    characterHit = new Rect(Vector2(posX, posY), Vector2(sizeX, sizeY));

    //발판 만들기

    platform = new Rect(Vector2(CENTER_X, WIN_HEIGHT - 100), Vector2(300, 300));

    //타격 fx 만들기

    fx = new HitFX(Vector2(-1000, -1000), Vector2(300, 600));
    //만들고 숨기기
    fx->Active() = false;
}

BitmapScene::~BitmapScene()
{
    // 이 씬이 끝날 때
    DeleteDC(memDC); // 이 데이터 전체를 메모리에서 없애기
    DeleteDC(stretchDC);

    // 비트맵도 펜이나 브러시처럼 출력 도구라, 지워야 될 때 지우면 좋다
    DeleteObject(artist);
    DeleteObject(human);

    //포인터 인스턴스 지우기
    delete characterArea;
    delete platform;
    delete fx;
}

void BitmapScene::Update()
{
    // 경과 시간을 변수에 누적시킵시다.

    currentTimeElapsed += DELTA * animateSpeed; //경과된 시간만큼이 누적 (속도 보정)

    // 다른 연산 전에 캐릭터의 그림과 충돌 영역을 동기화부터
    UpdateHitToAreaPos();
    //만약 캐릭터가 별도의 클래스로 분리된다면, 위 함수도 캐릭터를 따라 가야 합니다.
    //fx 업데이트
    fx->UpdateThis();

    if (currentTimeElapsed >= interval)
        //if (KEY_DOWN(VK_LBUTTON)) //마우스 좌클릭(수동)
    {
        //시간이 기준을 넘어갔으니, 넘어간 만큼을 다시 빼거나, 0으로 리셋
        currentTimeElapsed -= interval;


        //행동 코드에 따라 다른 그림 순번 돌리기
        // 보강 : 역재생인지 여부를 확인하고 인덱스를 1 더하거나 1 뺀다
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


        // +1 마다 자기 옆의 동작을 표현함으로써 자기를 표현하는데...
        // -> 순번이 그림의 최대 순번을 넘어가면 안 될것!
        //위쪽에 조건문으로 보정하거나...
        //...혹은 계산 직후에 검증
        if (actIndex1 > lastIndex1)
        {
            //actIndex1 = actIndex1 - lastIndex1; // 감산보정
            //actIndex1 = 0; //직접보정

            //역재생으로 설정할 경우
            actIndex1 = lastIndex1; //마지막 순번으로 리셋
            isReverseIndex1 = true; //역재생 시작
        }
        if (actIndex2 > lastIndex2)
        {
            //actIndex2 = actIndex2 - lastIndex2; // 감산보정
            //actIndex1 = 0; //직접보정

            actIndex2 = lastIndex2;
            isReverseIndex2 = true;
        }
        if (actIndex1Run > lastIndex1Run)
        {
            //actIndex1Run -= lastIndex1Run; //감산보정

            actIndex1Run = lastIndex1Run;
            isReverseIndex1Run = true;
        }
        if (actIndex1 < 0)
        {
            actIndex1 = 0; //역재생일 때는 리셋 값이 (보정 값이) 가장 가까운 경계
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

        if (actIndex1ATK > lastIndex1ATK) //애니메이션 사이클(공격)이 끝까지 간 것
        {
            actCode = 0;      //공격이 아닌 서 있기로 행동 변화 (=공격 종료)
            isATKing = false; //공격 중 변수도 거짓으로
            actIndex1ATK = 0; //인덱스도 리셋
        }
    }

    // 우클릭을 하면 그림이 다른 걸로 바뀔 수도??
    if (KEY_DOWN(VK_RBUTTON))
    {
        // 간이 코드 : 행동 코드 바꾸기
        // 우클릭을 할 때마다 행동의 코드를 다른 쪽으로 바꾸기
        if (actCode == 0)
        {
            actCode = 1;
            actIndex1Run = 0; //달리기 그림의 순번을 0으로 재리셋
        }
        else
        {
            actCode = 0;
            actIndex1 = 0; //서 있기 그림의 순번을 재리셋
        }
    }

    //화살표키를 눌렀을 때 행동 코드가 (캐릭터 출력이) 바뀌도록

    if (KEY_DOWN(VK_LEFT))
    {
        actCode = 1; //달리기 시작

        isLeft = true;
    }
    if (KEY_DOWN(VK_RIGHT))
    {
        actCode = 1; //달리기 시작

        isLeft = false;
    }

    if (KEY_UP(VK_LEFT))
    {
        actCode = 0; //달리기 끝, 서기 시작
    }
    if (KEY_UP(VK_RIGHT))
    {
        actCode = 0;
    }

    // 화살표키를 누르고 있을 때, 캐릭터가 좌우로

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

    //화살표키를 위로 누르면?
    if (KEY_DOWN(VK_UP)) // VK_SPACE도 좋을 듯
    {
        //if (isJumping) // 점프가 아닐 때
        if (jumpCount < 2) // 점프한 횟수가 2회 미만일 때
        {
            isJumping = true; //점프를 한다고 신호를 준다
            downForce = 0;    //밑으로 떨어지는 힘으로 0으로 초기화
            jumpCount++;      // 점프한 횟수 +1
        }
    }

    if (isJumping) //점프라는 행동을 시작했다면?
    {
        float offset = 1; //"추가 보정"을 뜻하는 변수

        downForce += gravity * DELTA * offset;
        // 밑으로 떨어지는 힘 = 중력 * 경과 시간 * 최종 보정값을 계속 누적시킨 힘 (점프하는 동안 계속 커진다)
        // -> 2D, 물리 법칙을 개발자가 임의로 만든 경우

        characterArea->Pos().y -= (jumpPower - downForce);
        //캐릭터의 위치에 점프에 걸린 힘을 누적시킨다
        //점프에 걸린 힘 = 캐릭터 본래의 점프력 - 현재 밑으로 걸리는 힘

        if (characterArea->Bottom() > WIN_HEIGHT) //플레이어 영역의 밑바닥이 윈도우 밑으로 넘어가면?
        {
            isJumping = false; //점프 종료

            //플레이어 위치를 밑바닥에 딱 맞게 조정
            characterArea->Pos().y = WIN_HEIGHT - characterArea->GetSize().y / 2;
            //크기 / 2를 보정시켜서 캐릭터의 위치를 딱 맞게 조정

            jumpCount = 0; // 점프한 횟수를 0으로 초기화
        }
    }

    // ---------------------이동 후, 영역 충돌이 일어나면 벌어지는 일들

    if (characterHit->IsCollision(platform))
    {
        //두 사각형이 부딪쳤다!

        // 두 사각형의 충돌 관계를 판단하는 방법은 여러 가지가 있지만
        // 지금은 C++을 이용해 간단히 판단하는 방법을 사용
        // 중요한 것은 공식이 아니라 공식의 이유니까

        // 충돌을 판단할 때 중요한 것 1 : 서로의 방향관계가 중요

        singleDir = GetCollisionDirection(characterHit, platform);
        //캐릭터의 충돌 영역이 발판의 어디에 있는지를 "받는다"

        // 2 : 충돌을 했는데, 그 때 캐릭터의 상황이 어떤지가 중요

        // 예 : 떨어져도 되는 상황인가 아닌가? 무엇을 하고 있는 중인가?
        // -> "점프 중이라면?"

        // -> 더 나아가서, 캐릭터가 발판의 "위"에 있을 때, 그 캐릭터가 어디로 가던 중이었는가? 하늘로? 땅으로?

        if (singleDir == ABOVE && isJumping && //플레이어가 위이고, 점프 중이다
            jumpPower - downForce < 0) //점프력 - 낙하력이 음수라면 = 캐릭터는 떨어지는 중이라면
        {
            //캐릭터의 위치를 발판에 맞게 조정하고, 점프를 끝낸다!

            isJumping = false;

            characterArea->Pos().y = platform->Top() - characterArea->GetSize().y / 2;

            jumpCount = 0;
        }
    }

    //추가 충돌! (타격 vs 휴먼2)
    if (fx->IsCollision(Vector2(350, 400))) //좌표 기준
        //원래는 휴먼2에도 히트 영역이 있어서 두 사각형이 충돌하는 것이 보편적입니다. (현재는 간이 충돌)
    {
        //휴먼2가 맞았음을 변수에 저장
        human2isHit = true; //맞았다!
        isFading = true;    //"몽롱해진다!" 혹은 "희미해진다!"
        hitTime = 0;        //맞은 시간 체크 (0으로 초기화)
    }

    // ** 23. 08. 25. 보충:
    //
    //  휴먼2의 "맞은 상태"를 업데이트하는 코드를 따로 빼서
    //  업데이트 함수 안에서 처리하도록 하겠습니다.
    //  사실, 이게 맞아요. 스크롤을 되도록 덜 움직이고 싶어서
    //  낮에는 렌더 함수에서 다 처리했지만요... 
    // 
    // ** 23. 08. 25. 보충 끝:

    if (human2isHit) // 맞은 상태면, 투명한 상태를 한 번 더 표현한다
    {
        // -> 어떻게? 새로운 화면 처리로!

        //1. 휴먼2의 투명도 계산
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

        // ** 23. 08. 25. 보충:
        //
        // 휴먼2가 맞은 시간을 추가로 계산하겠습니다.
        // 휴먼1의 공격FX(간이) 효과주기 1초에 맞추어서
        // 휴먼2도 맞고 나서 1초가 지나면 "맞았다" 상태에서 회복하도록 하겠습니다. 
        // 
        // ** 23. 08. 25. 보충 끝:

        //휴먼2가 맞은 시간을 체크
        hitTime += DELTA;
        if (hitTime > span)
        {
            human2isHit = false;
        }
    }
    else // 휴먼이 맞지 않았다면
    {
        currentAlpha = 255;
    }

    // 자연 낙하
    if (!characterHit->IsCollision(platform) && //발판 위도 아닌데
        characterArea->Bottom() < WIN_HEIGHT && // 캐릭터 발이 윈도우 높이보다 높이 있다
        !isJumping) //점프 한 상황이 아니었다
    {
        isJumping = true; //"점프" 즉 하늘 위에서 일어나야 할 일이 일어나도록
        downForce = jumpPower; // 점프력과 똑같은 낙하력 = 낙하부터 시작하도록
        //점프 카운트는 별도로 주고 싶으면 줘도 되고, 안 줘도 무방 (의도한 점프는 아니니까)
    }
}

void BitmapScene::Render(HDC hdc)
{
    //(펜이나 브러시처럼) 그림도 선택
    SelectObject(memDC, artist); //개 출력

    //개 (혹은 기본 비트맵) 출력
    //BitBlt(hdc,
    //    0, 0, //출력을 시작할 위치
    //    WIN_WIDTH, WIN_HEIGHT, //출력을 할 크기
    //    memDC, // 어디서부터 출력할 데이터를 (화면 정보를) 가져오려는가
    //    0, 0,  // 어디서부터 가져오려는가(x, y 좌표)
    //    SRCCOPY);  //"소스를 복사 형태로 출력한다(원본을 굳이 지우지는 않는다)"

    // 비트맵을 출력하는 또 다른 방법(함수)
    // 스트레치 블릿 (늘여서 출력하기) : 원본 그림을 추가로 설정된 크기값에 맞추어서 출력하는 함수
    // 이 함수에서 매개변수 중 참조 크기와 원본 참조의 시작점을 바꾸면 그림의 형태를 바꿀 수 있다
    StretchBlt(hdc,
        0, 0,                  //출력을 시작할 위치
        WIN_WIDTH, WIN_HEIGHT, //출력을 할 크기
        memDC,                 // 어디서부터 출력할 데이터를 (화면 정보를) 가져오려는가
        WIN_WIDTH, 0,          // 어디서부터 가져오려는가(x, y 좌표) : 오른쪽 끝을 기준으로
        -WIN_WIDTH, WIN_HEIGHT,// 어떤 크기로 바꾸어서 (혹은 안 바꾸고) 가져오려는가
        // 혹은 "참조의 방향이 어디인가?" : 현재 "왼쪽 밑으로 윈도우 크기"라는 지정
        SRCCOPY);              //"소스를 복사 형태로 출력한다(원본을 굳이 지우지는 않는다)"

    //위 함수를 활용하면 비트맵을 좌우반전하는 것이 가능 (상하도, 회전 등도) * 회전의 경우 다른 방법이 더 효율적이지만...

    //펜이나 브러시 교체처럼 그림도 똑같이 교체

    //이쯤에서 캐릭터의 (그림) 영역을 한번 그리기
    //characterArea->Render(hdc);
    // characterHit->Render(hdc);

    // 왼쪽 오른쪽이 있는 게임이 있는데, 왼쪽을 보는 그림이 없다면?
    // 렌더에서 그림을 뒤집을 겁니다. (1차 예시는 위에서)

    //캐릭터를 그릴 때, 좌우반전을 시켜가면서 그리기

    //임시 변수 추가로 만들기
    //1. 참조할 가로 크기 (왼쪽으로 계산할 때 뒤집으려고)
    int refSize_X = 128;
    //1. 참조할 때 추가 좌표 조정
    int leftPlus = 0;
    //2. 좌우반전 여부에 따라 나오는 1차 결과물
    //   -> "해당 출력소의 시각 정보를 다 담은 가상의 그림"
    HBITMAP stretched = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
    HBITMAP alpha = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);

    //조건문 (왼쪽이면 int값 수정)
    if (isLeft)
    {
        refSize_X = -128; //참조 크기를 음수로
        leftPlus = 1;     //참조 좌표에 +1
    }

    //사람으로 인한 fx가 있으면 출력
    //if (fx->Active()) fx->Render(hdc);
    fx->Render(hdc);

    if (actCode == 0)
    {
        //각 출력 장소에 처리할 (참조할) 그림 정보를 선택합니다
        SelectObject(memDC, human);
        SelectObject(stretchDC, stretched);

        StretchBlt(stretchDC, //출력의 목적지를 중간의 스트레치 DC로
            0, 0,        // 출력 시작 위치
            512, 512,    // 출력 크기
            memDC,       // 원본 화면
            128 * (actIndex1 + leftPlus) - leftPlus, 0, //참조를 시작할 곳
            refSize_X, 128,                  //참조의 크기와 방향
            SRCCOPY);

        GdiTransparentBlt(hdc, //출력할 화면(모니터)
            //0, 0, // 출력을 시작할 위치
            characterArea->Left(), characterArea->Top(),
            512, 512,            // <- 출력을 할 크기인데... "수동으로 정할 수도 있다"
            stretchDC,           // 어디서 화면을 가져올 것인가 (이번에는 스트레치에서)
            0, 0,                // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가?)
            512, 512,            // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
            RGB(255, 255, 255)); // 그림을 가져올 때, <- 여기 지정된 색깔은 투명하게 만들라는 뜻
    }
    else if (actCode == 1)
    {
        SelectObject(memDC, humanRun);
        SelectObject(stretchDC, stretched);

        StretchBlt(stretchDC, //출력의 목적지를 중간의 스트레치 DC로
            0, 0,        // 출력 시작 위치
            512, 512,    // 출력 크기
            memDC,       // 원본 화면
            128 * (actIndex1Run + leftPlus) - leftPlus, 0, //참조를 시작할 곳
            refSize_X, 128,                                //참조의 크기와 방향
            SRCCOPY);

        GdiTransparentBlt(hdc, //출력할 화면(모니터)
            //0, 0, // 출력을 시작할 위치
            characterArea->Left(), characterArea->Top(),
            512, 512,          // <- 출력을 할 크기인데... "수동으로 정할 수도 있다"
            stretchDC,         // 어디서 화면을 가져올 것인가
            0, 0,              // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가?)
            512, 512,          // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
            RGB(255, 255, 255));
    }
    //캐릭터 영역으로 직사각형으로 그리기
    //characterArea->Render(hdc);

    // * 생성자에서 값을 할당한 순번(actIndex)에 의해서 그림이 표현되도록 코드 수정

    else if (actCode == 2)
    {
        SelectObject(memDC, humanATK);
        SelectObject(stretchDC, stretched);

        StretchBlt(stretchDC, //출력의 목적지를 중간의 스트레치 DC로
            0, 0,        // 출력 시작 위치
            512, 512,    // 출력 크기
            memDC,       // 원본 화면
            128 * (actIndex1ATK + leftPlus) - leftPlus, 0, //참조를 시작할 곳
            refSize_X, 128,                                //참조의 크기와 방향
            SRCCOPY);

        GdiTransparentBlt(hdc, //출력할 화면(모니터)
            //0, 0, // 출력을 시작할 위치
            characterArea->Left(), characterArea->Top(),
            512, 512,     // <- 출력을 할 크기인데... "수동으로 정할 수도 있다"
            stretchDC,    // 어디서 화면을 가져올 것인가
            0, 0,         // 어디서 가져오려는가 (128 픽셀 기준으로 표시 주체가 어디까지 왔는가?)
            512, 512,     // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
            RGB(255, 255, 255));
    }


    // 사람2를 그리기 전에 발판을 그려보겠습니다

    //platform->Render(hdc);


    //따라서 위 함수를 쓰면?
    // 1. 큰 그림을 잘라서 쓸 수 있다 (원하는 부분만 볼 수 있다)
    // 2. 그림에 있는 배경을 투명하게 만들어서 알맹이만 볼 수 있다
    //    -> "작은 그림" 혹은 "게임 속 캐릭터" "UI" 같은 것들을 표현하기에 유용

    SelectObject(memDC, human2);
    SelectObject(stretchDC, stretched);
    SelectObject(alphaDC, alpha);

    // ** 23. 08. 25. 보충:
    // 
    // 강의 중에는 중간에 썼던 SelectObject를 한 곳으로 모았습니다.
    // 사실 이래야 맞습니다. 강의 중에, (안 그래도 코드를 차근차근 나가면서 어지러운데)
    // 스크롤을 움직이는 과정을 조금이라도 줄여보고 싶었어요.
    // 
    // ** 23. 08. 25. 보충 끝:

    //휴먼2도 왼쪽을 보도록 + 맞은 경우, "몽롱해진" 상태를 그림으로 표현

    // -> 맞은 후에 그림이 깜빡이는 것으로 표현하려고 한다!
    // -> 그림이 깜빡인다는 것은? 눈에서 그림이 사라진다는 뜻! (단순)
    //    혹은 그림의 색깔이 투명해진다

    // * 색깔에 R, G, B라고 해서 세 가지 성분이 있다고 알려져 있는데
    //   사실은 컴퓨터가 처리하는 색깔에는 한 가지 속성이 더 있다.

    //   그것이 바로 "알파"라고 불리는 투명도(진짜로는 "투시 불가도") 값.

    //   이 투명도=투시불가도가 높으면 색이 선명해지고 (보이고)
    //   투시불가도가 낮으면 색이 희미해진다
    //   0이 되면 눈에 보이지 않게 된다

    // ** 23. 08. 25. 보충:
    // 
    //  투명도를 나타내기 위해서는 다음 과정을 거칩니다.
    //  1. 이미지 DC 백업하기 (나중에 알파값을 계산하면서 그림들을 녹아들에 하기 위해, 원본 화면을 받아오는 것)
    //     Bitblt를 써서 간단히 수행할 수 있습니다.
    //     복사 방향은 hdc -> alphaDC
    //     (강의 중에는 서두르느라 이 과정을 빠뜨렸고, 이것 때문에 그림을 "합산할" 기준이 없어서 배경 색이 까맣게 나왔어요!)
    // 
    //  2. 그리려는 그림을 먼저 자르고, 늘리면서 적절히 가공하기
    //     좌우반전에 썼던  stretchBlt 함수로 수행할 수 있습니다.
    //     복사 방향은 memDC -> stretchDC
    //     가공이 끝난 이미지가 stretchDC의 비트맵 stretch에 들어갑니다.
    // 
    //  3. 가공이 된 그림에서 다시 특정한 색을 빼고 다시 그리기
    //     애니메이션 출력에 썼던 GdiTransparentBlt로 수행합니다.
    //     복사 방향은 stretchDC -> alphaDC
    //     넵, 이제 alphaDC는 이미지를 두 개를 떠안게 되었어요. 원래 있었던 원본과, 지금 막 받은 진짜 이미지.
    // 
    //  4. 알파 DC에서 마지막에 받은 이미지에 투명값을 적용하기
    //     GdiAlphaBlent를 사용합니다.
    //     그림을 그냥 투명하게만 만드는 것이 아니라 원래 있었던 화면과 녹아들게 만들기 위해
    //     반투명해진 그림과 원본을 섞어 새로운 화소를 만드는, 다소 복잡한 과정을 거칩니다.
    //     (그래서 먼저 기준을 받아야 했던 겁니다.)
    //     그리고 이 모든 과정이 끝나고 나면, 해당 연산으로 만들어진 '반투명 그림'을
    //     진짜 모니터, hdc에 출력해줍니다.
    // 
    //     복사 방향은 alphaDC -> hdc
    //
    // 
    // ** 23. 08. 25. 보충 끝:

    //투명도 계산 부분, 매개변수 주석 포함

    BitBlt(alphaDC,
        0, 0,     //알파DC의 어디서부터 결과물을 채워나갈 것인가?
        512, 512, //어느 정도까지 결과물을 출력할 것인가 (얼마나 복사할까?)
        hdc,
        200, 210, //어디서부터 결과물을 채워나갈 것인가? (=나중에 캐릭터 그려야 할 위치!)
        SRCCOPY);

    // ** 23. 08. 25. 보충:
    // 
    // 나중에, 이런 투명출력 기능을 따로 클래스로 뽑아낼 경우
    // SRCCOPY 위에 있는 좌표 변수는 그 텍스처의 위치를 반영해주어야 합니다.
    //
    // ** 23. 08. 25. 보충 끝:

    StretchBlt(stretchDC, //출력의 목적지를 중간의 스트레치 DC로
        0, 0,                         // 출력 시작 위치
        512, 512,                     // 출력 크기
        memDC,                        // 원본 화면
        128 * (actIndex2 + 1) - 1, 0, //참조를 시작할 곳 (그림을 참조하는 거라, 위의 BitBlt는 신경쓰지 않아도 됩니다.)
        -128, 128,                    //참조의 크기와 방향
        SRCCOPY);

    GdiTransparentBlt(alphaDC, //출력할 화면(모니터)
        0, 0,              // 출력을 시작할 위치
        512, 512,          // <- 출력을 할 크기인데... "수동으로 정할 수도 있다" (그림을 가공하는 거라, 위의 BitBlt는 신경쓰지 않아도 됩니다.)
        stretchDC,         // 어디서 화면을 가져올 것인가
        0, 0,              // 어디서 가져오려는가
        512, 512,          // 원본의 그림을 어느 정도 크기로 가져올 것인가 (해당 안되면 자르기)
        RGB(255, 0, 255)); // 그림을 가져올 때, <- 여기 지정된 색깔은 투명하게 만들라는 뜻

    // 위 human2 그림에서 쓰인 짙은 보라색 (양홍색) : 2D 게임 등에서 가장 많이 쓰이는 배경색
    // 일부러 그림 파일에서 배경을 저 색으로 칠하고(그림판 등으로) -> 이 색을 투명하게 만들면
    // 색 손실 없이 가장 효율적으로 그림을 표현해낼 가능성이 높다

    // * 양홍색은 RGB로 255, 0, 255
    // winAPI에서는 MAGENTA 라고도 한다 (관련 기능을 불러오거나, #define으로 지정하면 편리)
    // #define MEGENATA RGB(255, 0, 255) <- 대략 이렇게

    /// * 투명도 함수는 제일 마지막에 호출

    // BLENDFUNCTION : 그림 조합(특히 투명도 등)에 사용된 데이터 구조체
    blend.SourceConstantAlpha = currentAlpha;

    GdiAlphaBlend(hdc,
        200, 210,   //출력 장소 (=혹은 캐릭터의 위치)
        512, 512,   //출력할 크기 (혹은 텍스처의 크기)
        alphaDC,    //이곳 알파DC에서 연산을 모두 수행하고, 위의 hdc에 뿌려줍니다!
        0, 0,       //0, 0 : 연산의 원점부터 모두 출력을 해줘야 맞겠죠
        512, 512,   //연산된 DC의 크기도요.
        blend);     // 위에서 만든 블렌드 구조체를 써서 투명도를 적용!

    DeleteObject(stretched);
    DeleteObject(alpha);
}