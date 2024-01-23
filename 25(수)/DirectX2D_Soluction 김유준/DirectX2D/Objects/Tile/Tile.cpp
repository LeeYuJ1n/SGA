#include "Framework.h"

Tile::Tile(Tile::Data data)
	: Button(data.textureFile), data(data) // <- �̴ϼȶ����� ���
{
	localPosition   = data.pos;
	localRotation.z = data.angle;
}

Tile::~Tile()
{
	// TODO : ���߿� �ʿ��ϸ� �߰�
}

void Tile::SetTexture(wstring file)
{
	Quad::SetTexture(file);  // ������ �׸��� �ٲٰ�
	data.textureFile = file; // Ÿ���� �������� �ؽ�ó ���� �̸� �ݿ�
}

void Tile::SetAngle(float angle)
{
	localRotation.z = angle;
	data.angle      = angle;
}