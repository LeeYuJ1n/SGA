#pragma once

class EditTileMap : public Transform
{
    // Ÿ���� ��ġ�ؼ� ���� ����� + �� ������ �����ϱ�

    // ���ο� ��ġ ������ �ִ� ������� �־�� �ϹǷ�, �ڱ� �ڽŵ� ������ �������� �Ѵ�
    // -> ���� �� ���� ���� �׷����� �ϳ��� �Ŵ��� ������ ����� �� ���� ������ �� �ʿ��� ���

public:
    EditTileMap(UINT width, UINT height);
    ~EditTileMap();

    void Update();
    void Render();

    //Ÿ���� Ŭ������ �� �Ͼ �ϵ�
    void ClickTile(Quad* selected, Tile::Type type);
    void DeleteObjTile();

    //������ ����� ���̺�, �ε��ϱ� ���� �Լ�
    void Save(string file);
    void Load(string file);

private:

    UINT width;
    UINT height;

    //Ÿ�ϵ��� ���� (��� ���� ������Ʈ ����)
    vector<Tile*> bgTiles;
    vector<Tile*> objTiles;

    Vector2 tileSize; //Ÿ�� ũ�� ���� (Ÿ�ϸ��� ũ�Ⱑ 100% ������ ���� ������, 100% ���� �� �������� ȿ���� �ش�ȭ)

    void CreateTiles();

    void SetBGTiles(wstring file, float angle); // �ؽ�ó ������ Ž���⿡�� �ٷ� ���� �Ŷ� wstring
    void SetOBJTiles(wstring file, float angle);

};

