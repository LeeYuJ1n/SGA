#include "Framework.h"

EditTileMap::EditTileMap(UINT width, UINT height)
{
	this->width  = width;
	this->height = height;

	CreateTiles();
}

EditTileMap::~EditTileMap()
{
	for (Tile* tile : bgTiles)
	{
		delete tile;
	}

	for (Tile* tile : objTiles)
	{
		delete tile;
	}
}

void EditTileMap::Update()
{
	for (Tile* tile : bgTiles)
	{
		tile->Update();
	}

	for (Tile* tile : objTiles)
	{
		tile->Update();
	}

	Transform::UpdateWorld();
}

void EditTileMap::Render()
{
	for (Tile* tile : bgTiles)
	{
		tile->Render();
	}

	for (Tile* tile : objTiles)
	{
		tile->Render();
	}
}

void EditTileMap::ClickTile(Quad* selected, Tile::Type type)
{
	switch (type)
	{
	case Tile::BG:
		// ���õǾ� �־��� Ÿ���� ��ư���μ��� key( = ���� �̸�)�� ȸ�������� �ݿ��Ѵ�
		SetBGTiles(selected->GetTexture()->GetFile(), selected->Rot().z);
			break;

	case Tile::OBJ:
		SetOBJTiles(selected->GetTexture()->GetFile(), selected->Rot().z);
		break;
	}
}

void EditTileMap::Save(string file) // ���� �̸��� ���� ���̺� �ۼ�
{
	// ���̳ʸ� ���� ��¿� �����ͺ��� �����
	BinaryWriter* writer = new BinaryWriter(file);

	writer->UInt(width);  // ���θ� ������ ����
	writer->UInt(height); // ���ε� ����
	writer->UInt(bgTiles.size());

	for (Tile* tile : bgTiles)
	{
		Tile::Data data = tile->GetData(); // ������ ���� �б�

		// �� ������(����ü) �� �� ������ �ڷ��� ���� �ϳ��� �����ϱ�
		writer->Wstring(data.textureFile);
		writer->Float(data.pos.x);
		writer->Float(data.pos.y);
		writer->Float(data.angle);
		writer->Int((int)data.type);

		// ������� ���� ��� Ÿ�� ���� ��
	}

	writer->UInt(bgTiles.size());

	for (Tile* tile : objTiles)
	{
		Tile::Data data = tile->GetData(); // ������ ���� �б�

		// �� ������(����ü) �� �� ������ �ڷ��� ���� �ϳ��� �����ϱ�
		writer->Wstring(data.textureFile);
		writer->Float(data.pos.x);
		writer->Float(data.pos.y);
		writer->Float(data.angle);
		writer->Int((int)data.type);
	}

	// ������� ���� ��� Ÿ�� ������ �ϳ��� ���Ͽ� �̾ ������ ��

	// �� �ڷ��� ���� �Լ� ȣ�� ������� �߰��� �ڷ����� �޶����� ���̳ʸ� ��� ����

	delete writer; // �� �� ������ �ν��Ͻ� �����
}

void EditTileMap::Load(string file)
{
	BinaryReader* reader = new BinaryReader(file);

	width  = reader->UInt(); // ������ ù �����͸� int��ŭ �о U-int�� ���ο� ����
	height = reader->UInt(); // ���� �����͸� �� �о ���ο� ����. ���� �ݺ�

	UINT size = reader->UInt(); // �о�� �� ������ �����ϱ�

	for (Tile* tile : bgTiles)
	{
		Tile::Data data; // �� ����ü �ϴ� �����α�

		data.textureFile = reader->Wstring();
		data.pos.x       = reader->Float();
		data.pos.y       = reader->Float();
		data.angle       = reader->Float();
		data.type        = (Tile::Type)reader->Int();

		// �̾Ƴ� ������ ���� Ÿ�Ͽ� �����ϱ�
		tile->SetTexture(data.textureFile);
		tile->Pos()   = data.pos;
		tile->Rot().z = data.angle;
	}

	size = reader->UInt();

	for (Tile* tile : objTiles)
	{
		Tile::Data data; // �� ����ü �ϴ� �����α�
			             // * {} �ۿ��� ����� ȿ���� ����
		                 // ��� ���⼭ ����� {}�� ���� �� �������� �ڵ�����

		data.textureFile = reader->Wstring();
		data.pos.x       = reader->Float();
		data.pos.y       = reader->Float();
		data.angle       = reader->Float();
		data.type        = (Tile::Type)reader->Int();

		// �̾Ƴ� ������ ���� Ÿ�Ͽ� �����ϱ�
		tile->SetTexture(data.textureFile);
		tile->Pos()   = data.pos;
		tile->Rot().z = data.angle;
	}

	delete reader;
}

void EditTileMap::CreateTiles()
{
	// �⺻ (����) Ÿ�� ����
	wstring baseTile = L"Textures/Tile/tile.png";
	Texture* texture = Texture::Add(baseTile);

	// �⺻ Ÿ�Ͽ��� ���� ũ�� ����
	tileSize = texture->GetSize();

	bgTiles.reserve(width * height); // ���� ����

	for (UINT y = 0; y < height; ++y)
	{
		for (UINT x = 0; x < width; ++x)
		{
			Tile::Data data = {};
			data.textureFile = baseTile;
			data.pos = Vector2(tileSize.x * x, tileSize.y * y);

			Tile* tile = new Tile(data);
			tile->SetParent(this);
			bgTiles.push_back(tile); // �ϴ� ��濡 ���Ƴֱ�
		}
	}

	// �� �κ��� ������ Ÿ�� �⺻ �ε� ��
}

// �׸��� ��, �ܺ� ��𼭵� (���� ���� : �ַ� ����) ȣ���ϸ� Ÿ���� ������ �����ϵ���

void EditTileMap::SetBGTiles(wstring file, float angle)
{
	for (Tile* tile : bgTiles)
	{
		if (tile->GetCollider()->IsPointCollision(mousePos))
		{
			tile->SetTexture(file);
			tile->SetAngle(angle);
		}
	}
}

void EditTileMap::SetOBJTiles(wstring file, float angle)
{

}
