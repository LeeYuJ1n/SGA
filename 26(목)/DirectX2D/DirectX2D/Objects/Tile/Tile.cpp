#include "Framework.h"

Tile::Tile(Tile::Data data)
	: Button(data.textureFile), data(data) // <- 이니셜라이저 사용
{
	localPosition   = data.pos;
	localRotation.z = data.angle;
}

Tile::~Tile()
{
	// TODO : 나중에 필요하면 추가
}

void Tile::SetTexture(wstring file)
{
	Quad::SetTexture(file);  // 실제로 그림을 바꾸고
	data.textureFile = file; // 타일의 정보에도 텍스처 파일 이름 반영
}

void Tile::SetAngle(float angle)
{
	localRotation.z = angle;
	data.angle      = angle;
}