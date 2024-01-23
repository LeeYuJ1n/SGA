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
		// 선택되어 있었던 타일의 버튼으로서의 key( = 파일 이름)과 회전정보를 반영한다
		SetBGTiles(selected->GetTexture()->GetFile(), selected->Rot().z);
			break;

	case Tile::OBJ:
		SetOBJTiles(selected->GetTexture()->GetFile(), selected->Rot().z);
		break;
	}
}

void EditTileMap::Save(string file) // 파일 이름을 통해 세이브 작성
{
	// 바이너리 파일 출력용 데이터부터 만들기
	BinaryWriter* writer = new BinaryWriter(file);

	writer->UInt(width);  // 가로를 정수로 저장
	writer->UInt(height); // 세로도 저장

	for (Tile* tile : bgTiles)
	{
		Tile::Data data = tile->GetData(); // 데이터 정보 읽기

		// 각 데이터(구조체) 내 상세 정보를 자료형 따라 하나씩 저장하기
		writer->Wstring(data.textureFile);
		writer->Float(data.pos.x);
		writer->Float(data.pos.y);
		writer->Float(data.angle);
		writer->Int((int)data.type);

		// 여기까지 오면 배경 타일 저장 끝
	}

	for (Tile* tile : objTiles)
	{
		Tile::Data data = tile->GetData(); // 데이터 정보 읽기

		// 각 데이터(구조체) 내 상세 정보를 자료형 따라 하나씩 저장하기
		writer->Wstring(data.textureFile);
		writer->Float(data.pos.x);
		writer->Float(data.pos.y);
		writer->Float(data.angle);
		writer->Int((int)data.type);
	}

	// 여기까지 오면 모든 타일 정보를 하나씩 파일에 이어서 저장한 것

	// 각 자료형 쓰기 함수 호출 방식으로 중간에 자료형이 달라져도 바이너리 출력 가능

	delete writer; // 다 쓴 포인터 인스턴스 지우기
}

void EditTileMap::Load(string file)
{
	BinaryReader* load = new BinaryReader(file);

	for (Tile* tile : bgTiles)
	{
		Tile::Data data = tile->GetData(); // 데이터 정보 읽기

		// 각 데이터(구조체) 내 상세 정보를 자료형 따라 하나씩 저장하기
		data.textureFile = load->Wstring();
		data.pos.x = load->Float();
		data.pos.y = load->Float();
		data.angle = load->Float();
		data.type = (Tile::Type)load->Int();

		// 여기까지 오면 배경 타일 저장 끝
	}

	for (Tile* tile : objTiles)
	{
		Tile::Data data = tile->GetData(); // 데이터 정보 읽기

		// 각 데이터(구조체) 내 상세 정보를 자료형 따라 하나씩 저장하기
		data.textureFile = load->Wstring();
		data.pos.x = load->Float();
		data.pos.y = load->Float();
		data.angle = load->Float();
		data.type = (Tile::Type)load->Int();
	}

	// 여기까지 오면 모든 타일 정보를 하나씩 파일에 이어서 저장한 것

	// 각 자료형 쓰기 함수 호출 방식으로 중간에 자료형이 달라져도 바이너리 출력 가능

	delete load; // 다 쓴 포인터 인스턴스 지우기
}

void EditTileMap::CreateTiles()
{
	// 기본 (바탕) 타일 선정
	wstring baseTile = L"Textures/Tile/tile.png";
	Texture* texture = Texture::Add(baseTile);

	// 기본 타일에서 기준 크기 도출
	tileSize = texture->GetSize();

	bgTiles.reserve(width * height); // 벡터 예약

	for (UINT y = 0; y < height; ++y)
	{
		for (UINT x = 0; x < width; ++x)
		{
			Tile::Data data = {};
			data.textureFile = baseTile;
			data.pos = Vector2(tileSize.x * x, tileSize.y * y);

			Tile* tile = new Tile(data);
			tile->SetParent(this);
			bgTiles.push_back(tile); // 일단 배경에 몰아넣기
		}
	}

	// 이 부분이 끝나면 타일 기본 로딩 끝
}

// 그리고 내, 외부 어디서든 (현재 상태 : 주로 내부) 호출하면 타일의 정보를 갱신하도록

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
