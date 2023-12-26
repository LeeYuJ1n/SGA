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
    // Pick �Լ� ȣ�� : �׸��� Ŭ���ϸ� ��ǥ�� �� �� �ֵ���
    if (KEY_PRESS(VK_LBUTTON))
    {
        pickingPos = Pick(); // ��� �ִ� ��ǥ�� ��� �Լ��� �����
    }
}

void TerrainPicker::Render()
{
    // ������ ������� �޽ø� �״�� Draw ȣ��� �׷��� �ָ� �ȴ�

    // ���� ���� ( ���ӿ�����Ʈ���� ������ ��� )
    GameObject::SetRender();

    // �޽ÿ��� �׸��� ȣ��
    mesh->Draw();
}

void TerrainPicker::RenderUI()
{
    ImGui::Text("Terrain Pick Position");
    ImGui::Text("X : %.1f, Y : %.1f, Z : %.1f", pickingPos.x, pickingPos.y, pickingPos.z);
    // ���� ���ڸ� ����ؼ� ������ ����� �гο� �ؽ�Ʈ ���
}

Vector3 TerrainPicker::Pick()
{
    // ���� : ȣ��Ǹ� ȣ��� ���� ��ǥ�� ��ȯ�ϱ�
    // -> ���콺 Ŀ������ ���۵� ���� ( ����ĳ��Ʈ ) �� ��ü�� �ε��ļ� ���� ������ ��ǥ��
    //    ��ǻ�Ϳ��� ��ȯ�ϱ�

    // ����ĳ��Ʈ �ʿ� : 
    Ray ray = CAM->ScreenPointToRay(mousePos);

    // ������� �ͷ����� ���� ���θ� ��� �˻��ؼ� �浹�� �Ͼ���� �˻� �ؾ� �ϴµ�
    // ���� �ͷ����� ���� �浹ü�� ���� : ����� �� �ִ� "�� ��ħ"�̶�� ���� ȣ�� ( �ӽ� �ϱ�� �� �Լ� ���� )

    for (UINT z = 0; z < height - 1; ++z)
    {
        for (UINT x = 0; x < width - 1; ++x)
        {
            UINT index[4]; // ���� �˻�� �� 4�� = �簢���� ������ �ʿ�
            
            index[0] = width * z + x;
            index[1] = width * z + (x + 1);
            index[2] = width * (z + 1) + x;
            index[3] = width * (z + 1) + (x + 1);

            // ���� �ޱ�
            vector<VertexType> vertices = mesh->GetVertices();

            // ������ �ε��� ( ���� ���� ��ǥ ) �� �����ؼ� ���� ��ġ �ޱ�
            Vector3 p[4];

            for (UINT i = 0; i < 4; ++i)
            {
                p[i] = vertices[index[i]].pos; // ������ ���� �ε����� i��°�� ���ͻ� ��ġ
            }

            float distance = 0; // �Ÿ� ���� �غ��ϰ� �ʱ�ȭ

            // TruangleTests : DX���� �ִ� ����ĳ��Ʈ �� ������ ( 3���� ǥ�� ���� ) ���� �浹�� �����ϱ� ���� ����� ��� ����
            //                 ( DX�� ����ĳ��Ʈ�� �����ϰ� �����ﵵ ����������, �̵� ���� ��ȣ�ۿ� ������ �⺻�����δ� ���� �ʴ´�... ���������� �̷��� ����� ���� )
            //                 
            if (TriangleTests::Intersects(ray.pos, ray.dir, p[0], p[1], p[2], distance))
            {
                // ������ �� ���� ( ����ĳ��Ʈ ) ������ �������� �ش� ������ �״�� ����ؼ� ���ͷ� ��ȯ
                return ray.pos + ray.dir * distance; // �������� �������� �Ÿ���ŭ, ���� �������� ���� �ش� ���� ����
                // return height - (ray.pos + ray.dir * distance); // �׸��� �������� ��
            }

            // ������� ���� �簢���� �̷�� 0-1-2 �ﰢ���� ���� �� �浹 �Ǻ��� �̷���� ��
            // �׷��Ƿ� ���� 3-1-2 �ﰢ���� Ȯ��

            if (TriangleTests::Intersects(ray.pos, ray.dir, p[3], p[1], p[2], distance))
            {
                return ray.pos + ray.dir * distance;
                // return height - (ray.pos + ray.dir * distance);
            }
        }
    }

    // ������� �Դٸ� �׸��� ������ ���� ������ �׸��� ������ ������

    // �׷��Ƿ� �ƹ��ų� ��ȯ
    return Vector3(0, 0, 0); // 0, 0, 0 �⺻ ����� ��ȯ
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

            // ���� �����ϱ�
            // if (x == 5 && z == 5) vertex.pos.y = 30.0f;

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
            indices.push_back(width * z + x);
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
    vector<VertexType>& vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    for (UINT i = 0; i < indices.size() / 3; ++i)
        // 3���� ������ ���� : �� �ϳ����� ���ο� ���� 1�� ����Ⱑ �����ε�
        // ���� 3���� ���� �� �������� �� �� �ϳ��� �����ϱ�
    {
        // �� �ݺ������� i�� �ݺ����� ���� �ε���,
        // �ڵ忡�� ������ ��� �� �ε����� i���� �ٽ� ���
        UINT index0 = indices[i * 3];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 v0 = vertices[index0].pos;
        Vector3 v1 = vertices[index1].pos;
        Vector3 v2 = vertices[index2].pos;

        // �������� ���� �̷�� �� ���� (���������� ����) ��������
        // �ﰢ���� �� ���̶�� ������ ����
        Vector3 e0 = v1 - v0;
        Vector3 e1 = v2 - v0;

        // �� ������ ���ο� ����(�ݻ��, ���) �����ϰ� ����ȭ
        Vector3 normal = Cross(e0, e1).GetNormalized(); // ����ȭ

        // ���� ������� ������ ������ ���� ���̴� ������ ���Ե� ���� ������ ����
        vertices[index0].normal = normal + vertices[index0].normal;
        vertices[index1].normal = normal + vertices[index1].normal;
        vertices[index2].normal = normal + vertices[index2].normal;
        // �� ������ ��� ���� ������ �������Ѽ�, �ش� ������ ���� ��� ������ �ϼ�

        // ������� ���� ��, ������ 1�� ����� ���� �� �ִ�
        // = ������ ��� �� ��ü���� ����� �������� ���� ����
    }
}

void TerrainPicker::MakeTangent()
{
    // ���� �ִ� ���� ������ �⺻ ������ ������ ���� : ���ظ� �ٸ���
    // ���� ������� ���� : ���� ( ��¥ ��� )
    // �� �Լ��� ���� : �ؽ�óUV ( �׸��� ���� )
    // = �׸��� ��ָ� ���� �͵��� ����ǰų�, Ÿ�� ������ ������ �޶�����
    //   �ű⼭ ������ ������ ��� ǥ�ÿ� �ݿ��� �ϱ� ����

    vector<VertexType>& vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    for (UINT i = 0; i < indices.size() / 3; ++i)
    {
        UINT index0 = indices[i * 3];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        // �Ȱ��� ���� �������� ( ������ ���ϸ� ������ �ƴϹǷ� p����Ʈ�� ��Ī )
        Vector3 p0 = vertices[index0].pos;
        Vector3 p1 = vertices[index1].pos;
        Vector3 p2 = vertices[index2].pos;

        // �׸��� ������ �Ƿ��� �ϴϱ� �׸� = UV��ǥ�� ��������
        Vector2 uv0 = vertices[index0].uv;
        Vector2 uv1 = vertices[index1].uv;
        Vector2 uv2 = vertices[index2].uv;

        // �� �Լ��� ���� �� �� ���� ���ϱ�
        Vector3 e0 = p1 - p0;
        Vector3 e1 = p2 - p0;

        // ź��Ʈ ������ ���� UV ������� ( UV�� ���� ) ���ϱ�
        float u1 = uv1.x - uv0.x; // u : �ؽ�ó�� x�� �ǹ�
        float v1 = uv1.y - uv0.y; // v : �ؽ�ó�� y�� �ǹ�
        float u2 = uv2.x - uv0.x;
        float v2 = uv2.y - uv0.y;

        // �� ����� ���ؼ� ����, Ȥ�� ��Ÿ UV������ �ٲ��

        // �ش� UV�� ���̸� ������ ��꿡�� ����
        float d = 1.0f / (u1 * v2 - u2 * v1); // ���� ( ���� ) ����
        
        // ���� ���� d�� ���� ������ ��ġ�� ( ��Į�� ���� )
        Vector3 tangent = d * (e0 * v2 - e1 * v1);

        // ����� �ؽ�ó ���� ���� ( ź��Ʈ ) �� ������ ���� ������ �� �ջ�
        vertices[index0].tangent += tangent;
        vertices[index1].tangent += tangent;
        vertices[index2].tangent += tangent;
    }
}