#include "Framework.h"
#include "TankScene.h"

TankScene::TankScene()
{
    gameTileMap = new GameTileMap("TextData/Test.map"); // Ÿ�� ������ ���� ��� �� ����
    aStar = new AStar(gameTileMap); // Ÿ�� ������ �ְ� �̿� �´� �� ã�� �˰��� �����

    tank = new Tank();
}

TankScene::~TankScene()
{
    delete tank;
    delete gameTileMap;
    delete aStar;
}

void TankScene::Update()
{
    //��ã�� �Է�
    if (KEY_DOWN(VK_LBUTTON))
    {
        int start = aStar->FindCloseNode(tank->Pos()); // ���� ��ũ���� ���� ����� ���� ��ǥ�� ����
        int end = aStar->FindCloseNode(mousePos); // ���� ���콺 Ŀ������ ���� ����� ���� �������� ����

        aStar->GetPath(start, end, tank->GetPath()); // �������� �������� ���� �ִܰ�θ� ���� ��ũ�� ��������Ʈ�� �Է��ϱ�
    }

    aStar->Update(); // �ʿ�� ���� �� ������ �ϴ� ȣ�⸸ (���߿� A*���� �ڵ尡 �߰��� ���� ���)
    tank->Update();
}

void TankScene::Render()
{
    gameTileMap->Render();
    aStar->Render();
    tank->Render();
}

//�ɼ� �Լ� 4��
void TankScene::Init() {}
void TankScene::Quit() {}
void TankScene::PreRender() {}
void TankScene::PostRender() { tank->RenderUI(); } //ImGUI�� ��ũ ���