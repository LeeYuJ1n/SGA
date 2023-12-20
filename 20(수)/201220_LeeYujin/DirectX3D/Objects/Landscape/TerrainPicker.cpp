#include "Framework.h"

TerrainPicker::TerrainPicker()
{
    width = 10;
    height = 10;

    mesh = new Mesh<VertexType>(); //������ �⺻ �޽�
    //���� ���
    MakeMesh();
    MakeNormal();
    MakeTangent();
    mesh->CreateMesh();
}

TerrainPicker::~TerrainPicker()
{
    delete mesh;
    // delete heightMap; //�ؽ�ó�� �� �Ŵϱ� (������ �� �ؽ�ó���� ������)
}

void TerrainPicker::Update()
{

}

void TerrainPicker::Render()
{

}

void TerrainPicker::RenderUI()
{

}

void TerrainPicker::MakeMesh()
{
    //�ͷ��� (Ȥ�� ���� �ڷᰡ ���ٸ� �׳� �� ���̶�) �����

    //ȭ���� ���� ����� (�Ű������� ������ ũ��, �׸��� �⺻��)
    vector<Float4> pixels(width * height, Float4(0, 0, 0 ,0));

    //���� ���� ������ �����ϱ�
    if (heightMap)
    {
        //���� ���θ� (�׸� ũ�⿡ ���缭) �ٽ� �޾ƿ���
        width = (UINT)heightMap->GetSize().x;
        height = (UINT)heightMap->GetSize().y;

        heightMap->ReadPixels(pixels); //�ؽ��Ϳ��� �׸��� �ȼ� ���� ��������
    }

    //���� ���

    vector<VertexType>& vertices = mesh->GetVertices();

    vertices.reserve(width * height); //���� ũ�� ����

    for (UINT z = 0; z < height; ++z)
    {
        for (UINT x = 0; x < width; ++x)
        {
            VertexType vertex;
            vertex.pos = { (float)x, 0, (float)(height - z - 1) };
            //�ؽ�ó ��ġ�� ���ϱ�
            vertex.uv.x = x / (float)(width - 1);
            vertex.uv.y = z / (float)(height - 1);
            //�� �ڵ忡�� ��-��(z)�� �ؽ�ó y�� �����ϴ� ���� : �׸��� ���� �� �����ϱ� (�ͷ��δ��)

            //���� �ε��� �̸� ���س��� (���߿� �ε��� ¥��)
            UINT index = (width * z) + x;
            //���� �ʿ��� ���� ���� ���ϱ� (���� ���� ����̳� �������̶�� ����)
            vertex.pos.y = pixels[index].x * MAX_HEIGHT; //���� �⺻�� �̿� (�Ʊ� ���� ������ �⺻���� �����̳Ŀ� ����)
            //vertex.pos.y = 0 * MAX_HEIGHT; // �����ϰ�

            //�� ���� ���� ���Ϳ� �����ô�
            vertices.push_back(vertex);
        }
    }

    //�ε��� �ֱ� (�ؽ�ó ��� �� 4���� �� ä���� : �ͷ��ΰ� ť�� ����)
    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve((width - 1) * (height - 1) * 6);

    for (UINT z = 0; z < height - 1; ++z)
    {
        for (UINT x = 0; x < width - 1; ++x)
        {
            //���� ������ ���ƿ� ���� �� ���� ( 0 > 1 > 2 )
            indices.push_back(width * z + 1);
            indices.push_back(width * z + x + 1);
            indices.push_back(width * (z + 1) + x);

            //�ٽ� �� ����� �밢�� ���� ������! ( 2 > 1 > 3 )
            indices.push_back(width * (z + 1) + x);
            indices.push_back(width * z + x + 1);
            indices.push_back(width * (z + 1) + x + 1);

            //�̷��� �ﰢ�� �� �� ������ �簢�� ����
        }
    }
}

void TerrainPicker::MakeNormal()
{

}

void TerrainPicker::MakeTangent()
{

}