#include "Framework.h"

TerrainEditor::TerrainEditor() 
    : GameObject(L"Landscape/TerrainEditor.hlsl"),
    width(MAX_SIZE), 
    height(MAX_SIZE)
{
    // �޽� ����� ( �⺻, ������ )
    mesh = new Mesh<VertexType>();

    // �޽� ����� ( ���� )
    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData(); // ������ ����� ���� �������� ���� �����

    mesh->CreateMesh();

    // ���� ���̴��� ���̴� ���� ���� ���Ͽ��� ����
    computeShader = Shader::AddCS(L"Compute/ComputePicking.hlsl");

    // ������ �� �������� �ʱ�ȭ
    brushBuffer = new BrushBuffer();

    // ���� �������� ������ �����͸� ���� �� ������ ����
    structuredBuffer = new StructuredBuffer(
        inputs.data(), sizeof(InputDesc), triangleSize,
                       sizeof(OutputDesc), triangleSize);

    // ��Ʈ��ó ���� ( ���� ���� ) �� �� �Ű����� : 
    // �Է¿� �� ������ / �Է��� ������ �Ը� / �Է¿� �Ը�
    //                     / ����� ������ �Ը� / ����� �Ը�

    rayBuffer = new RayBuffer();
}

TerrainEditor::~TerrainEditor()
{
    delete mesh;
    delete brushBuffer;
    delete rayBuffer;
    delete structuredBuffer;
}

void TerrainEditor::Update()
{
    if (KEY_PRESS(VK_LBUTTON))
    {
        brushBuffer->Get().pickingPos = ComputePick();
    }
}

void TerrainEditor::Render()
{
    // ���� ��� Ȯ��
    brushBuffer->SetPS(10);

    SetRender();

    mesh->Draw();
}

void TerrainEditor::RenderUI()
{
    // ����� �ǿ��� Ȯ��

    // Ÿ��Ʋ
    ImGui::Text("Terrain Editor ( Option )");

    if (ImGui::DragInt("Width", (int*)&width, 1.0f, 2, MAX_SIZE))
        Resize(); // ũ�Ⱑ �ٲ�� ��������

    if (ImGui::DragInt("Height", (int*)&height, 1.0f, 2, MAX_SIZE))
        Resize(); // ũ�Ⱑ �ٲ�� ��������

    // ���߿� �� �κ� �̸�
    ImGui::DragFloat("Range", &brushBuffer->Get().range, 1.0f, 1.0f, 20.0f);
    ImGui::ColorEdit3("Color", (float*)& brushBuffer->Get().color);

    // ��Ŀ���� ���� ��ǥ ���� ��ġ
    ImGui::Text("Terrain Pick Position");
    ImGui::Text("X : %.1f, Y : %.1f, Z : %.1f",
        brushBuffer->Get().pickingPos.x,
        brushBuffer->Get().pickingPos.y, 
        brushBuffer->Get().pickingPos.z);
}

Vector3 TerrainEditor::Pick()
{
    Ray ray = CAM->ScreenPointToRay(mousePos);

    for (UINT z = 0; z < height - 1; ++z)
    {
        for (UINT x = 0; x < width - 1; ++x)
        {
            UINT index[4];

            index[0] = width * z + x;
            index[1] = width * z + (x + 1);
            index[2] = width * (z + 1) + x;
            index[3] = width * (z + 1) + (x + 1);

            // ���� �ޱ�
            vector<VertexType> vertices = mesh->GetVertices();

            Vector3 p[4];

            for (UINT i = 0; i < 4; ++i)
            {
                p[i] = vertices[index[i]].pos;
            }

            float distance = 0;
               
            if (TriangleTests::Intersects(ray.pos, ray.dir, p[0], p[1], p[2], distance))
            {
                return ray.pos + ray.dir * distance;
            }

            if (TriangleTests::Intersects(ray.pos, ray.dir, p[3], p[1], p[2], distance))
            {
                return ray.pos + ray.dir * distance;
            }
        }
    }

    // ������� �Դٸ� �׸��� ������ ���� ������ �׸��� ������ ������

    // �׷��Ƿ� �ƹ��ų� ��ȯ
    return Vector3(0, 0, 0); // 0, 0, 0 �⺻ ����� ��ȯ
}

Vector3 TerrainEditor::ComputePick()
{
    // ���� : ����� ��, ��ġ�� �ٷ� ��ȯ�� �ϱ⺸��, �ƿ� �� ��������
    // ��ǻƮ �����Ϳ� �ݿ����� �غ��⸦ ��ǥ��

    Ray ray = CAM->ScreenPointToRay(mousePos);

    // ���� ���ۿ� ���� ���� ���� ����
    rayBuffer->Get().pos = ray.pos;
    rayBuffer->Get().dir = ray.dir;
    rayBuffer->Get().triangleSize = triangleSize; // ������ �Է±Ը� �������ۿ���
    rayBuffer->SetCS(0); // 0���� �Ҵ�

    DC->CSSetShaderResources(0, 1, &structuredBuffer->GetSRV());
    // ���ҽ����� ���̴� �����ϱ� ( ���̴� ����, ������ ����Ʈ ����, ���� ���ҽ� )

    // ��¿�û, ���� ���� �״�� ����ϴ� ���
    DC->CSSetUnorderedAccessViews(0, 1, &structuredBuffer->GetUAV(), nullptr);

    // ������ ���� ���̴��� ����
    computeShader->Set();

    UINT x = ceil((float)triangleSize / 64.0f); // �Է� �Ը𿡼� �� x�� ���� �ٵ�, �ø�(ceil) ������� �ޱ�

    DC->Dispatch(x, 1, 1); // ���� ���̴� ��� ȯ�濡�� �ش� CS�� �۾� ����, ũ��, �� ���� �����ϴ� ���

    structuredBuffer->Copy(outputs.data(), sizeof(OutputDesc) * triangleSize); // ���� ���� �����͸� ��¿� ����

    float minDistance = FLT_MAX; // �ּҰŸ� �ӽð� ����
    int minIndex = -1; // �ּ� ���� �ӽð� ����

    UINT index = 0; // ���� �ӽð����� �ʱ�ȭ

    // ������ ���� ��� ��� ��� �ݺ������� ȣ��
    for (OutputDesc output : outputs)
    {
        if (output.picked) // ���� ���ΰ� �ڵ�� �����ִ� = true
        {
            if (output.distance < minDistance) // ���������� ������ �ּ� �Ÿ����� ���� ��µ����� �Ÿ��� �۴ٸ�
            {
                minDistance = output.distance; // ����
                minIndex    = index;           // ���ŵ� �Ÿ��� ���� ��� �������� ����
            }
        }

        ++index; // �ݺ��� ���� �ø��� �ε��� +1

        // �� �ݺ����� ���������ν� ��� ������ ���̿��� "�Ÿ�"�� ���� ª�� ��� ����� �� �� �ִ�
        // -> �������� ǥ�鿡 �ٴٸ��� �ּ� �Ÿ� = ���� �Ÿ��� ���� ����
    }

    // ������� ���� �� index�� ���� -1�� �ƴϸ� ( index�� "�ִٸ�" )
    // �������� ��ü�� ���� ���� �浹�� ���ٴ� �̾߱�
    // �ش� ��ġ�� �Ǻ��ϴ� �������� output�� ���۸� ���� ������ �Ǳ⵵ �ߴ�

    // �׷��Ƿ� �ش� ����� ��ȯ���� ���ָ� �ȴ�

    // * �߰� ��Ʈ : ���뿡�� �޽��� ������ �ٲ��� �� �ִٸ�, 
    //              ������ ����� ��� ���� �ٲ��ִ� �� ������ �̴ϴ�!!

    if (minIndex > -1)
    {
        return ray.pos + ray.dir * minDistance; // ����, ���� ����, ������ �����Ÿ�
    }

    // �׷��� �ʴٸ� �浹�� ������ �� ( ���� �ݿ��� �ٸ� �Է� ����� ������ �� )
    return Vector3();
}

void TerrainEditor::MakeMesh()
{
    vector<Float4> pixels(width * height, Float4(0, 0, 0, 0));

    if (heightMap)
    {
        width = (UINT)heightMap->GetSize().x;
        height = (UINT)heightMap->GetSize().y;

        heightMap->ReadPixels(pixels);
    }

    vector<VertexType>& vertices = mesh->GetVertices();

    vertices.reserve(width * height);

    for (UINT z = 0; z < height; ++z)
    {
        for (UINT x = 0; x < width; ++x)
        {
            VertexType vertex;
            vertex.pos = { (float)x, 0, (float)(height - z - 1) };
            
            vertex.uv.x = x / (float)(width - 1);
            vertex.uv.y = z / (float)(height - 1);
            
            UINT index = (width * z) + x;

            vertex.pos.y = pixels[index].x * MAX_HEIGHT;

            vertices.push_back(vertex);
        }
    }

    vector<UINT>& indices = mesh->GetIndices();

    indices.reserve((width - 1) * (height - 1) * 6);

    for (UINT z = 0; z < height - 1; ++z)
    {
        for (UINT x = 0; x < width - 1; ++x)
        {
            indices.push_back(width * z + x);
            indices.push_back(width * z + x + 1);
            indices.push_back(width * (z + 1) + x);

            indices.push_back(width * (z + 1) + x);
            indices.push_back(width * z + x + 1);
            indices.push_back(width * (z + 1) + x + 1);
        }
    }
}

void TerrainEditor::MakeNormal()
{
    vector<VertexType>& vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    for (UINT i = 0; i < indices.size() / 3; ++i)
    {
        UINT index0 = indices[i * 3];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 v0 = vertices[index0].pos;
        Vector3 v1 = vertices[index1].pos;
        Vector3 v2 = vertices[index2].pos;

        Vector3 e0 = v1 - v0;
        Vector3 e1 = v2 - v0;

        Vector3 normal = Cross(e0, e1).GetNormalized();

        vertices[index0].normal = normal + vertices[index0].normal;
        vertices[index1].normal = normal + vertices[index1].normal;
        vertices[index2].normal = normal + vertices[index2].normal;
    }
}

void TerrainEditor::MakeTangent()
{
    vector<VertexType>&vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    for (UINT i = 0; i < indices.size() / 3; ++i)
    {
        UINT index0 = indices[i * 3];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        Vector3 p0 = vertices[index0].pos;
        Vector3 p1 = vertices[index1].pos;
        Vector3 p2 = vertices[index2].pos;

        Vector2 uv0 = vertices[index0].uv;
        Vector2 uv1 = vertices[index1].uv;
        Vector2 uv2 = vertices[index2].uv;

        Vector3 e0 = p1 - p0;
        Vector3 e1 = p2 - p0;

        float u1 = uv1.x - uv0.x;
        float v1 = uv1.y - uv0.y;
        float u2 = uv2.x - uv0.x;
        float v2 = uv2.y - uv0.y;

        float d = 1.0f / (u1 * v2 - u2 * v1);

        Vector3 tangent = d * (e0 * v2 - e1 * v1);

        vertices[index0].tangent += tangent;
        vertices[index1].tangent += tangent;
        vertices[index2].tangent += tangent;
    }
}

void TerrainEditor::MakeComputeData()
{
    // ������ �̷�����ų� �̷�����ٰ� �ϰ� �ش� ��ȹ���� �ݿ��� ������ �����

    vector<VertexType>vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    triangleSize = indices.size() / 3;

    // ���� �� �ൿ�� ���ؼ� inputs�� outputs�� ����� �޶��� ���� �ִ�
    // -> �ٲ�� �κп� ���� ���� ó���� �ʿ��ϴ�

    inputs.resize(triangleSize); // ���� �ﰢ�� ũ�⿡ ���߾ ���� ������
    outputs.resize(triangleSize);

    // .clear() ���� �Լ��� �ϰ� ������ �ع����� �͵� ����̴� ( Ȯ���ϴ� )

    for (UINT i = 0; i < triangleSize; ++i) // ���� �ﰢ���� ��ŭ
    {
        UINT index0 = indices[i * 3 + 0];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        // �Է��� ����� ������ �Է��� ������ �ݿ��ϱ�
        // ( ���߿� ����� ��� ȣ���ϴ��� -> "����" �Լ���, ������Ʈ, ���� ��� ���� ���� �� )
        // �Է��� ����� ���� �ܰ迡��, ȣ���� ������� ����

        inputs[i].v0 = vertices[index0].pos;
        inputs[i].v1 = vertices[index1].pos;
        inputs[i].v2 = vertices[index2].pos;
    }

    // ������� ���� �Է��� ���� �ݿ� �Ϸ�
}

void TerrainEditor::Reset()
{
    // ���� : ����Ʈ���� ( �Ը� ���� �ٲ��� �ʰ� ���� ���� �ʱ�ȭ )
    //        �׷��� �޽� ���� �� �̹� ���� ���ΰ� �ݿ��ǰ� �ִ� ���̶�
    //        �ϴ��� ȣ����� �ٸ��� �ϴ� ���� Resize()�� �����ϰ�

    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData();

    mesh->UpdateVertex(); // ���� ���� ������Ʈ
    mesh->UpdateIndex();  // �ε��� ���� ������Ʈ

    structuredBuffer->UpdateInput(inputs.data()); // ���� ������ �޾ƿͼ� �ݿ��ϱ�
}

void TerrainEditor::Resize()
{
    // ���� ������ ���� ( ũ�Ⱑ ���� �����Ǵ� ��� )

    // �޽� �ٽ� ����� ( �� �������� ���� ���ΰ� �ݿ� )
    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData();

    mesh->UpdateVertex(); // ���� ���� ������Ʈ
    mesh->UpdateIndex();  // �ε��� ���� ������Ʈ

    structuredBuffer->UpdateInput(inputs.data()); // ���� ������ �޾ƿͼ� �ݿ��ϱ�
}
