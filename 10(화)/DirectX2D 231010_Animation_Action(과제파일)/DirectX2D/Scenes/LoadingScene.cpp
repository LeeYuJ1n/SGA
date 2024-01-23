#include "Framework.h"
#include "LoadingScene.h"

LoadingScene::LoadingScene()
{
    //progressBar = new Quad(L"Textures/yellow.png");
    //progressBar->Pos() = { CENTER_X, CENTER_Y / 2 };

    progressBar = new ProgressBar(L"Textures/yellow.png");
    progressBar->SetPosition( { CENTER_X, CENTER_Y/2 } );

    //pressStart = new Quad(L"Textures/start.png");
    pressStart = new Button(L"Textures/start.png");
    pressStart->Pos() = { CENTER_X, CENTER_Y };

    Init(); //������ ���ÿ� �ʱ�ȭ
}

LoadingScene::~LoadingScene()
{
    delete progressBar;
    delete pressStart;
}

void LoadingScene::Update()
{
    //�ð��� üũ

    // �ð��� ������ �� �Ѿ����� ����ð� ���� ����
    if (timePassed < timeTotal) timePassed += DELTA;

    // ���� ����� �����Ͽ�, ���ѽð��� �Ѱ����� �� ���ѽð��� ���߱�
    if (timePassed > timeTotal) timePassed = timeTotal;

    // �ٽ� ���� ����� �����Ͽ�, ���ѽð��� ����ٸ� ���⼭ � �ڵ带 �ۼ��ؾ� �� ����...
    if (timePassed == timeTotal)
    {
        if (!pressStart->Active()) pressStart->Active() = true;
    }

    // ���� ���⼭ else if ���� ������ if�� ���� �ִ� ���� :
    // �� ���ǹ��� �������Ѽ�, ���ʷ� ������ ������ ��� 1ȸ ������Ʈ ������ ��� ������ �������� �ϰ� �ǵ��߱� ����
    // -> �׷��� �� ���� �ϳ��� ���길�� �����ϰ� �ʹٸ� �ݵ�� else�� ���� �־���� �Ѵ�

    // �׸��� �� ���ǹ��� ������ ���, �ش� ������ ����� ���α׷��� ���� ���¿� �ݿ�������
    progressBar->Scale() = { timePassed / timeTotal, 1 };

    progressBar->Update(); // �� ����� ������Ʈ
    pressStart->Update();


    // �� �Ŵ����� �� �ǰ� �ִ��� Ȯ�� �Է�
    if (LoadComplete())
    {
        if (KEY_DOWN(VK_RETURN))
        {
            SceneManager::Get()->ChangeScene("PlaneScene");
        }
    }
}

void LoadingScene::Render()
{
    progressBar->Render();
    pressStart->Render();
}

void LoadingScene::PostRender() {}

void LoadingScene::Init()
{
    //���� ������ �ʱ�ȭ ��Ȳ�� �̷������ �� �ڵ尡 �ִٸ� ���⼭

    //�ϴ� ��ŸƮ ǥ�ô� ��������
    //���� �� ��Ȳ = ũ�� ����
    //������ �ð��� ����

    pressStart->Active() = false;
    progressBar->Scale() = {0, 1};
    timePassed = 0;

    //��ŸƮ �׸��� ��ư�� ���, ���⿡ �Լ��� �Ҵ�
    // pressStart->SetEvent(&LoadingScene::StartPlaneScene); // �Լ� �����ʹ� �ٸ� Ŭ������ ��� �������� �״�� �̾ƾ��� ����� (�߰���ġ �ʿ�)
    // -> �Լ� �����Ͱ� Ŭ������ ��︮�� ���ϰ� �ִٸ�, Ŭ������ �� ���� �ǰڳ�? -> �������� ���ư��� �͵� ���(C, C++�� �׷���)

    // pressStart->SetEvent(bind(GlobalEvent(), "Start"));
    // bind : c, c++�� ȣ������ void() Ȥ�� std::function���� ������ ������ ������ ��ó�� ����ϴ� ����
    //        Ư�� ������ ��ġ ���� �Ű������� �ٿ���, �ش� �Ű������� ȣ�� �ÿ� �̸� ����
    //        ���� �� �Լ��� ���� ��ư�� event ������ "GlobalEvent("Start")" �� ��ü ȣ���� �Ҵ�
    //        -> event(); �̷��Ը� ȣ���ص� ���Ŵ����� ��� ��ȯ�� �Ű��������� �� ��Ʈ�� ���� ȣ��

    //pressStart->SetEvent(bind(GlobalEvent(), "LoadScene", "PlaneScene"));
    //bind�� ��� �Ű������� ���� ���� ��� �̷��� ���ʷ� �Ҵ�

    // -> ��, bind�� �Ű������� �ְ� �װ� �� ��Ʈ�� ��ӽ�Ű�� �� ������ �Ѵ� -> �Ű������� ���� �� �ҷ����� ���� ����
    //    (�׸��� �Ű������� ������ �׳� �״�� ���� ���� �� ���⵵ �ϴ�)

    // -> bind�� ���������� ��� �Լ����� �״�δ� ������ �� �ȴ�

    // -> �׷��ٸ�, bind��, std::function��, ���ʿ� �Լ� ������ ��ü�� �� ��� �Լ��� ������ �� �ɱ�?
    
    // -> ��� �Լ��� �޸� �ּҴ� �� �Լ����� ������ ���� �ƴ϶�, �Լ��� �� �ִ� Ŭ����...
    //    �׸��� �� Ŭ������ ������� �� �ν��Ͻ��� �޸� �ּҸ� ������ ����
    //    -> �ٸ� ����, Ŭ����(�� �ν��Ͻ�, Ȥ�� ���ļ� "��ü")�� ���� �ְ� �� �ȿ� �Լ��� �ִ�
    //    -> �׷��� �Լ��� �޸� ��ġ�� ������ �����ϸ� ��ǻ�Ͱ� �� ������ ��Ȯ�� �𸣱� ����

    // �� �κ��� �ذ��� ��� A. ȣ���� ����, �Լ� �̸��� ȣ���� ������ Ŭ���� �̸��� ���ָ� �ȴ�

    // ���� �� �� Ŭ������ StartScene�̶��
    // �Լ��� �ҷ��´ٸ� StartScene(x) &LoadingScene::StartScene (o)

    // �� ��Ȱ� ���Ҿ (���� ���� x) ������ ���������� ��ü������ ������ ���ָ� �ȴ�

    // -> ���� ���� �ܰ迡�� Ȯ���ϰ� ��� �ִ�, �׸��� � ������ �Լ��� �ҷ��� ������ ��Ȯ�� �Ѵ�

    //��: Ŭ����(����)�� �Լ��� �������� ��Ƽ�, �ش� Ŭ������ �Լ��� �����ͷ� �޴� ����
    std::function<void(LoadingScene&)> testFuncPtr = &LoadingScene::StartPlaneScene;
    // �ν��Ͻ��� �ʿ��ϴٸ� �ν��Ͻ��� ���� �� �� �ν��Ͻ��� ��ġ�� �־ �ȴ�

    // ��ư�� function<void(void*)>�� �̿��ϰ�, object ������ (��������) Ȱ���ϱ�
    pressStart->SetObejct(this);
    //pressStart->SetParamEvent(&LoadingScene::StartPlaneScene); // <- void(void*) �κа� void(LoadingScene&) �浹 ����
    pressStart->SetParamEvent(bind(&LoadingScene::StartPlaneScene, this)); // void() ���� () �ڸ��� this�� ä���� �Ű������� �̺�Ʈ�� ���
    // -> �̷��� �ϸ� ���߿� �� �̺�Ʈ�� ȣ��� ��, �ν��Ͻ��� �ִ� StartPlaneScene �Լ���, object�� ����� �ν��Ͻ��� ��������, ȣ��



    //progressBar->Scale() = { timePassed / timeTotal, 1 };
}

void LoadingScene::Quit()
{
    // �� �Լ��� ����� ������ �� ������ �ڵ�

    // ���� �� ���� �� �� �ٽ� ����� �ʿ䰡 ���ٸ�, ���⼭ ���� �Ҵ�� ������ ���� ����...
    // delete progressBar;
    // delete pressStart;

    // �ٸ� �ٽ� ����� �� �ִ� ������ �̷� ���� �ڵ带 �����ϸ� -> �翬�� ����
    // -> �� ��� ������ ���� �ʰų�, �ݴ�� �ʱ�ȭ���� (������ ����) �� ������ �����ϰų�...
}

void LoadingScene::StartPlaneScene()
{
    SceneManager::Get()->ChangeScene("PlaneScene");
}