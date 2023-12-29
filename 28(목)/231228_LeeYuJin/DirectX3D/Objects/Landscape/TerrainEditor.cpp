#include "Framework.h"

TerrainEditor::TerrainEditor()
    : GameObject(L"Landscape/TerrainEditor.hlsl"),
    //: GameObject(L"Light/NormalMapping.hlsl"),
    width(MAX_SIZE),
    height(MAX_SIZE)
{
    // ��Ƽ���� ����
    material->SetDiffuseMap(L"Textures/Landscape/Dirt.png");
    secondMap = Texture::Add(L"Textures/Landscape/Dirt2.png");
    thirdMap = Texture::Add(L"Textures/Landscape/Dirt3.png");

    //�޽� ����� (�⺻, ������)
    mesh = new Mesh<VertexType>();

    //�޽� ����� (����)
    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData(); //������ ����� ���� �������� ���� �����

    mesh->CreateMesh();

    //���� ���̴��� ���̴� ���� ���� ���Ͽ��� ����
    computeShader = Shader::AddCS(L"Compute/ComputePicking.hlsl");

    // ������ �� �������� �ʱ�ȭ
    brushBuffer = new BrushBuffer();

    // ���� �������� ������ �����͸� ���� �� ������ ����
    structuredBuffer = new StructuredBuffer(
        inputs.data(), sizeof(InputDesc), triangleSize,
                       sizeof(OutputDesc), triangleSize);
    // ��Ʈ��ó ����(���� ����)�� �� �Ű�����:
    // �Է¿� �� ������ / �Է��� ������ �Ը� / �Է��� �Ը�
    //                     / ����� ������ �Ը� / ����� �Ը�

    rayBuffer = new RayBuffer();

    //������Ʈ ��θ� �˻��ؼ� �Ҵ��ϱ�
    char pathName[256]; // ���ڿ� �̸� �غ��ϱ� : �̰ͺ��� ū ���ڿ� ���ʿ� (������ 128�ڸ����ε� ���)
    GetCurrentDirectoryA(256, pathName); // ���� ���� ���� �������� ������ �Ҵ��ϱ�
    projectPath = pathName; //�Ҵ�� ������ ��� ������ �ֱ�
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
    if (CAM->GetTarget())
    {
        return;
    }
    
    if (IsComputePick(pickingPos)) // ���� ���� �ʾƵ� ���콺 ��ġ(��ŷ ��� ����)�� �Ź� �����鼭
                                   // ���� ��ŷ�� �� �ƴ��� ���α��� ��� �Ǻ��ϴ� ���ǹ��� ���
    {
        // ������ ���콺 Ŀ���� �ö� �ִ� ��Ȳ (��ǻƮ ���� true ��ȯ)
        brushBuffer->Get().pickingPos = pickingPos;
    }
    else
    {
        // ���� ��ŷ�� �� �� ���¿��� �Ʒ� ��� �ڵ带 �ߴ� (�ӵ� Ȯ��)
        return;
    }

    //if (KEY_PRESS(VK_LBUTTON))
    if (KEY_PRESS(VK_LBUTTON) && !ImGui::GetIO().WantCaptureMouse) // �� ������ ����� ���� ����
                                                                   // ���� : ����� �г� �߿���
                                                                   // ���콺 ��ġ�� ������ ���ĵ�
                                                                   // ������ �� �Ǳ⸦ �ٶ�
    {
        //brushBuffer->Get().pickingPos = ComputePick();
        //pickingPos = brushBuffer->Get().pickingPos;
        // ��ġ ã��

        switch (editType) //�귯�ø� �׾��� �� Ÿ�Կ� ����...
        {
        case TerrainEditor::HEIGHT: // ���� �����̶��...
            AdjustHeight(); // ���� �ٲٱ�
            //UpdateHeight(); // ���� ������Ʈ
            break;

        case TerrainEditor::ALPHA:
            AdjustAlpha();
            //UpdateAlpha();
            break;
        }
    }

    //���콺�� ���� �� ���� ���� �ݿ�
    if (KEY_UP(VK_LBUTTON))
    {
        UpdateHeight();
        UpdateAlpha();
    }
}

void TerrainEditor::Render()
{
    // ���� ��� Ȯ��

    //�귯�� ����
    brushBuffer->SetPS(10);
    
    //�߰� �ؽ�ó�� ���̾�� �����
    secondMap->PSSet(11); // ���߿� �� �ؽ�ó�� ���� �� �ִٸ� �귯�ú��� �� ���� (�ʺ��ٵ�) ���� ��
    thirdMap->PSSet(12);

    //��ü �� ����
    SetRender();

    mesh->Draw();
}

void TerrainEditor::RenderUI()
{
    //����� �ǿ��� Ȯ��

    //Ÿ��Ʋ
    ImGui::Text("Terrain Editor (Option)");
    if (ImGui::DragInt("Width", (int*)&width, 1.0f, 2, MAX_SIZE))
        Resize(); // ũ�Ⱑ �ٲ�� ��������
    if (ImGui::DragInt("Height", (int*)&height, 1.0f, 2, MAX_SIZE))
        Resize();

    //��Ŀ���� ���� ��ǥ ���� ��ġ
    ImGui::Text("Terrain Pick Position");
    ImGui::Text("X : %.1f, Y : %.1f, Z : %.1f",
        brushBuffer->Get().pickingPos.x,
        brushBuffer->Get().pickingPos.y,
        brushBuffer->Get().pickingPos.z);
    ImGui::Text("Height : %.1f",
        GetHeightByPos(pickingPos));

    const char* editList[] = { "Height", "Alpha" };
    ImGui::Combo("EditType", (int*)&editType, editList, 2);

    const char* brushList[] = { "Circle", "SoftCircle", "Rect" };
    if (ImGui::Combo("BrushType", (int*)&brushType, brushList, 3))
        brushBuffer->Get().type = brushType;

    ImGui::DragFloat("Range", &brushBuffer->Get().range, 1.0f, 1.0f, 20.0f);
    ImGui::DragFloat("AdjustValue", &adjustValue, 1.0f, -50.0f, 50.0f);
    ImGui::ColorEdit3("Color", (float*)&brushBuffer->Get().color);

    ImGui::DragInt("SelectMap", (int*)&selectMap, 1.0f, 0, 2);

    SaveHeightMap();
    ImGui::SameLine();
    LoadHeightMap();

    SaveAlphaMap();
    ImGui::SameLine();
    LoadAlphaMap();
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

            //�����ޱ�
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

    return Vector3();
}

Vector3 TerrainEditor::ComputePick()
{
    // ���� : ����� ��, ��ġ�� �ٷ� ��ȯ�� �ϱ⺸��, �ƿ� �� ��������
    // ��ǻƮ �����Ϳ� �ݿ����� �غ��⸦ ��ǥ��

    Ray ray = CAM->ScreenPointToRay(mousePos);

    //���� ���ۿ� ���� ���� ����
    rayBuffer->Get().pos = ray.pos;
    rayBuffer->Get().dir = ray.dir;
    rayBuffer->Get().triangleSize = triangleSize; // ���� ���� �Է±Ը� �������ۿ���

    rayBuffer->SetCS(0);

    DC->CSSetShaderResources(0, 1, &structuredBuffer->GetSRV());
    // ���ҽ����� ���̴� �����ϱ� (���̴� ����, ������ ����Ʈ ����, ���� ���ҽ�)

    //��¿�û, ���� ���� �״�� ����ϴ� ���
    DC->CSSetUnorderedAccessViews(0, 1, &structuredBuffer->GetUAV(), nullptr);

    //������ ���� ���̴��� ����
    computeShader->Set();

    UINT x = ceil((float)triangleSize / 64.0f); // �Է� �Ը𿡼� �� x�� ���� �ٵ�, �ø�(ceil) ������� �ޱ�

    DC->Dispatch(x, 1, 1); // ���� ���̴� ��� ȯ�濡�� �ش� CS�� �۾� ����, ũ��, �� ���� �����ϴ� ���

    structuredBuffer->Copy(outputs.data(), sizeof(OutputDesc) * triangleSize); // ���� ���� �����͸� ��¿� ����

    float minDistance = FLT_MAX; // �ּҰŸ� �ӽð� ����
    int minIndex = -1; //�ּ� ���� �ӽð� ����

    UINT index = 0; // ���� �ӽð����� �ʱ�ȭ

    //������ ���� ��� ��� ��� �ݺ������� ȣ��
    for (OutputDesc output : outputs)
    {
        if (output.picked) // ���� ���ΰ� �ڵ�� �����ִ� = ���̴�
        {
            if (output.distance < minDistance) // ���������� ������ �ּ� �Ÿ����� ���� ��µ����� �Ÿ��� �۴ٸ�
            {
                minDistance = output.distance; //����
                minIndex = index; //���ŵ� �Ÿ��� ���� ��� �������� ����
            }
        }
        ++index; // �ݺ��� ���� �ø��� �ε��� +1

        // �� �ݺ����� ���������ν� ��� ������ ���̿��� "�Ÿ�"�� ���� ª�� ��� ����� �� �� �ִ�
        // -> �������� ǥ�鿡 �ٴٸ��� �ּҰŸ� = �����Ÿ��� ���� ����
    }

    // ������� ���� �� index�� ���� -1�� �ƴϸ� (index�� "�ִٸ�")
    // �������� ��ü�� ���� ���� �浹�� ���ٴ� �̾߱�
    // �ش� ��ġ�� �Ǻ��ϴ� ���������� output�� ���۸� ���� ������ �Ǳ⵵ �ߴ�

    // �׷��Ƿ� �ش� ����� ��ȯ���� ���ָ� �ȴ�


    // * �߰� ��Ʈ: ���뿡�� �޽��� ������ �ٲ��� �� �ִٸ�,
    //              ������ ����� ��� ���� �ٲ��ִ� ��
    //              ������ �̴ϴ�!!


    if (minIndex > -1)
    {
        return ray.pos + ray.dir * minDistance; // ����, ���� ����, ������ �����Ÿ�
    }

    // �׷��� �ʴٸ� �浹�� ������ �� (���� �ݿ��� �ٸ� �Է� ����� ������ ��)
    return Vector3();
}

// �� �Լ��� �Ű����� ������ (mousePos ����)
Vector3 TerrainEditor::ComputePick(Vector3 sourcePos)
{
    // ���� : ����� ��, ��ġ�� �ٷ� ��ȯ�� �ϱ⺸��, �ƿ� �� ��������
    // ��ǻƮ �����Ϳ� �ݿ����� �غ��⸦ ��ǥ��

    //�Ű������� ���� ��ġ���� ���� ������ ����
    Ray ray;
    ray.pos = sourcePos;  // ���� : �Ű������� ��ġ
    ray.dir = Vector3::Down(); // ������ ������ ������ �Ʒ� (ĳ���ͷ� ġ�� �� �Ʒ�)

    //���� ���ۿ� ���� ���� ����
    rayBuffer->Get().pos = ray.pos;
    rayBuffer->Get().dir = ray.dir;
    rayBuffer->Get().triangleSize = triangleSize; // ���� ���� �Է±Ը� �������ۿ���

    rayBuffer->SetCS(0);

    DC->CSSetShaderResources(0, 1, &structuredBuffer->GetSRV());
    // ���ҽ����� ���̴� �����ϱ� (���̴� ����, ������ ����Ʈ ����, ���� ���ҽ�)

    //��¿�û, ���� ���� �״�� ����ϴ� ���
    DC->CSSetUnorderedAccessViews(0, 1, &structuredBuffer->GetUAV(), nullptr);

    //������ ���� ���̴��� ����
    computeShader->Set();

    UINT x = ceil((float)triangleSize / 64.0f); // �Է� �Ը𿡼� �� x�� ���� �ٵ�, �ø�(ceil) ������� �ޱ�

    DC->Dispatch(x, 1, 1); // ���� ���̴� ��� ȯ�濡�� �ش� CS�� �۾� ����, ũ��, �� ���� �����ϴ� ���

    structuredBuffer->Copy(outputs.data(), sizeof(OutputDesc) * triangleSize); // ���� ���� �����͸� ��¿� ����

    float minDistance = FLT_MAX; // �ּҰŸ� �ӽð� ����
    int minIndex = -1; //�ּ� ���� �ӽð� ����

    UINT index = 0; // ���� �ӽð����� �ʱ�ȭ

    //������ ���� ��� ��� ��� �ݺ������� ȣ��
    for (OutputDesc output : outputs)
    {
        if (output.picked) // ���� ���ΰ� �ڵ�� �����ִ� = ���̴�
        {
            if (output.distance < minDistance) // ���������� ������ �ּ� �Ÿ����� ���� ��µ����� �Ÿ��� �۴ٸ�
            {
                minDistance = output.distance; //����
                minIndex = index; //���ŵ� �Ÿ��� ���� ��� �������� ����
            }
        }
        ++index; // �ݺ��� ���� �ø��� �ε��� +1

        // �� �ݺ����� ���������ν� ��� ������ ���̿��� "�Ÿ�"�� ���� ª�� ��� ����� �� �� �ִ�
        // -> �������� ǥ�鿡 �ٴٸ��� �ּҰŸ� = �����Ÿ��� ���� ����
    }

    // ������� ���� �� index�� ���� -1�� �ƴϸ� (index�� "�ִٸ�")
    // �������� ��ü�� ���� ���� �浹�� ���ٴ� �̾߱�
    // �ش� ��ġ�� �Ǻ��ϴ� ���������� output�� ���۸� ���� ������ �Ǳ⵵ �ߴ�

    // �׷��Ƿ� �ش� ����� ��ȯ���� ���ָ� �ȴ�


    // * �߰� ��Ʈ: ���뿡�� �޽��� ������ �ٲ��� �� �ִٸ�,
    //              ������ ����� ��� ���� �ٲ��ִ� ��
    //              ������ �̴ϴ�!!


    if (minIndex > -1)
    {
        return ray.pos + ray.dir * minDistance; // ����, ���� ����, ������ �����Ÿ�
    }

    // �׷��� �ʴٸ� �浹�� ������ �� (���� �ݿ��� �ٸ� �Է� ����� ������ ��)
    return Vector3();
}

//���� ��ǻƮ ��(���콺 ��ġ���� ���� ��ǥ ���) �Լ��� bool ��ȯ�� (+pos ����)
bool TerrainEditor::IsComputePick(Vector3& pos)
{
    Ray ray = CAM->ScreenPointToRay(mousePos);

    rayBuffer->Get().pos = ray.pos;
    rayBuffer->Get().dir = ray.dir;
    rayBuffer->Get().triangleSize = triangleSize;

    rayBuffer->SetCS(0);

    DC->CSSetShaderResources(0, 1, &structuredBuffer->GetSRV());
    DC->CSSetUnorderedAccessViews(0, 1, &structuredBuffer->GetUAV(), nullptr);

    computeShader->Set();

    UINT x = ceil((float)triangleSize / 64.0f);

    DC->Dispatch(x, 1, 1);

    structuredBuffer->Copy(outputs.data(), sizeof(OutputDesc) * triangleSize);

    float minDistance = FLT_MAX;
    int minIndex = -1;

    UINT index = 0;
    for (OutputDesc output : outputs)
    {
        if (output.picked)
        {
            if (minDistance > output.distance)
            {
                minDistance = output.distance;
                minIndex = index;
            }
        }
        index++;
    }

    if (minIndex >= 0)
    {
        pos = ray.pos + ray.dir * minDistance;
        return true;
    }

    return false;
}

// �Ű������� �޾� ���� ��ǥ�� ������ ��, �ش� ��ǥ�� Y (����) ���� �Ҽ��� ��ȯ�ϴ� �Լ�
float TerrainEditor::GetHeightByPos(Vector3 myPos)
{
    // ��ǻƮ ��(������ ��� ���� ��ġ�⸦ ���ؼ� �ش� ������ ���̸� ����)
    // �ش� �Լ��� ��� = ����, ������ Y = ����
    float result = ComputePick(myPos).y;

    return result;
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
            vertex.pos = { (float)x, 0.0f, (float)(height - z - 1) };
            vertex.uv.x = x / (float)(width - 1);
            vertex.uv.y = z / (float)(height - 1);

            UINT index = width * z + x;
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
        UINT index0 = indices[i * 3 + 0];
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
    vector<VertexType>& vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    for (UINT i = 0; i < indices.size() / 3; ++i)
    {
        UINT index0 = indices[i * 3 + 0];
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
    //������ �̷�����ų� �̷�����ٰ� �ϰ� �ش� ��ȹ���� �ݿ��� ������ �����

    vector<VertexType> vertices = mesh->GetVertices();
    vector<UINT> indices = mesh->GetIndices();

    triangleSize = indices.size() / 3;

    // ���� �� �ൿ�� ���ؼ� inputs�� outputs�� ����� �޶��� �� �ִ�
    // -> �ٲ�� �κп� ���� ���� ó���� �ʿ��ϴ�

    inputs.resize(triangleSize); // ���� �ﰢ�� ũ�⿡ ���߾ ���� ������
    outputs.resize(triangleSize);

    //.clear() ���� �Լ��� �ϰ� ������ �ع����� �͵� ����̴� (Ȯ���ϴ�)

    for (UINT i = 0; i < triangleSize; ++i) // ���� �ﰢ���鸸ŭ
    {
        UINT index0 = indices[i * 3 + 0];
        UINT index1 = indices[i * 3 + 1];
        UINT index2 = indices[i * 3 + 2];

        // �Է��� ����� ������ �Է��� ������ �ݿ��ϱ�
        // (���߿� ����� ��� ȣ���ϴ��� -> "����" �Լ���, ������Ʈ, ���� ��� ���� ���� ��)
        // �Է��� ����� ���� �ܰ迡��, ȣ���� ������� ����

        inputs[i].v0 = vertices[index0].pos;
        inputs[i].v1 = vertices[index1].pos;
        inputs[i].v2 = vertices[index2].pos;
    }

    //������� ���� �Է��� ���� �ݿ� �Ϸ�
}

void TerrainEditor::Reset()
{
    // ���� : ����Ʈ ���� (�Ը� ���� �ٲ��� �ʰ� ���� ���� �ʱ�ȭ)
    //        �׷��� �޽� ���� �� �̹� ���μ��ΰ� �ݿ��ǰ� �ִ� ���̶�...
    //        �ϴ��� ȣ����� �ٸ��� �ϴ� ���� ��������� �����ϰ�

    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData();

    mesh->UpdateVertex(); // ���� ���� ������Ʈ
    mesh->UpdateIndex(); // �ε��� ���� ������Ʈ

    structuredBuffer->UpdateInput(inputs.data()); //���� ������ �޾ƿͼ� �ݿ��ϱ�
}

void TerrainEditor::Resize()
{
    // ���� ������ ���� (ũ�Ⱑ ���� �����Ǵ� ���)

    //�޽� �ٽ� ����� (�� �������� ���μ��ΰ� �ݿ�)
    MakeMesh();
    MakeNormal();
    MakeTangent();
    MakeComputeData();

    mesh->UpdateVertex(); // ���� ���� ������Ʈ
    mesh->UpdateIndex(); // �ε��� ���� ������Ʈ

    structuredBuffer->UpdateInput(inputs.data()); //���� ������ �޾ƿͼ� �ݿ��ϱ�
}

void TerrainEditor::UpdateHeight()
{
    // �Ʒ� �Լ����� ������ ������ �߰� ���� �ݿ��� ����

    vector<VertexType>& vertices = mesh->GetVertices();
    for (VertexType& vertex : vertices)
    {
        vertex.normal = {};
        vertex.tangent = {};
    }

    //������ �ʱ�ȭ�� �� ������ ������ ź��Ʈ�� �ؿ��� �����
    MakeNormal();
    MakeTangent();
    MakeComputeData();

    //������ ���̸� ���� �����ݿ��ϱ� (���� ������Ʈ �ѹ� ��)
    mesh->UpdateVertex();

    structuredBuffer->UpdateInput(inputs.data());
}

void TerrainEditor::AdjustHeight()
{
    // ���� ��ǥ ����, �귯�� ����, �귯�� Ÿ���� ����
    // -> �̿� ���� �ش� ��ǥ�� ���� ������ ����

    // ���� ������ ���ؼ��� ���� �����Ͱ� �ʿ��ϹǷ� �޾ƿ���
    vector<VertexType>& vertices = mesh->GetVertices();

    // �귯�� Ÿ�Կ� ���� ���� �����ϱ�
    switch (brushType)
    {
    case TerrainEditor::CIRCLE:

        //���� ���
        for (VertexType& vertex : vertices)
        {
            Vector3 pos = Vector3(vertex.pos.x, 0, vertex.pos.z); // �޽� �������� ���� ���θ� ���
            pickingPos.y = 0; //���� 0���� ����

            float distance = Distance(pos, pickingPos); // ���� ��ǥ�� �߽ɿ��� ���� ������ �Ÿ� ���ϱ�

            if (distance <= brushBuffer->Get().range) // �Ÿ��� �귯�� ���� ���� ���̶�� (*��Ÿ���� : 1227)
            {
                vertex.pos.y += adjustValue * DELTA; // ������ ���̿� ������ �ð������ �ݿ�
                // * DELTA�� �Է������ν� FPS ���� ���� ������ ���ֹ��� �ʰ� ������ �ӵ��� ������Ʈ ���� ����
                
                vertex.pos.y = Clamp(MIN_HEIGHT, MAX_HEIGHT, vertex.pos.y);
                //���� ȣ��� �Լ� : clamp �Լ� (���⼭�� GameMath Ŭ���� �ȿ� ���ǵ�,
                //                              c++ Ȥ�� ��Ÿ ���α׷��� �� ����� �Լ� ������)
                //                  -> (ȣ�� ����) 3��°�� �� �Ű�������
                //                  �ּҰ��� �ִ밪 ���̿� �׻� �ֵ��� �����ϰ�,
                //                  �������� ���� ��� �ּҰ���, �������� Ŭ ��� �ִ밪�� ��ȯ
            }
        }
        break;

    case TerrainEditor::SOFT_CIRCLE:
        //�۰ų� �帴�� ���� ���
        for (VertexType& vertex : vertices)
        {
            Vector3 pos = Vector3(vertex.pos.x, 0, vertex.pos.z); // �޽� �������� ���� ���θ� ���
            pickingPos.y = 0; //���� 0���� ����

            float distance = Distance(pos, pickingPos); // ���� ��ǥ�� �߽ɿ��� ���� ������ �Ÿ� ���ϱ�

            //�۰ų� �帴�� ���� ���
            float temp = adjustValue * max(MIN_HEIGHT, cos(distance / brushBuffer->Get().range));
            // �ܼ� �� �������� ������ �ƴ϶�, �ش� ���� �ȿ��� ��� ������ ����ġ�� �߰��� �޴����� �������� ����
            // -> �߽ɿ� �������� �Ÿ��� ª������ ������ �ڻ����� Ŀ����

            if (distance <= brushBuffer->Get().range) // �Ÿ��� �귯�� ���� ���� ���̶�� (*��Ÿ���� : 1227)
            {
                vertex.pos.y += temp * DELTA; // ������ ���̿� ������ ���� �ӽð��� �ð������ �ݿ�
                // * DELTA�� �Է������ν� FPS ���� ���� ������ ���ֹ��� �ʰ� ������ �ӵ��� ������Ʈ ���� ����

                vertex.pos.y = Clamp(MIN_HEIGHT, MAX_HEIGHT, vertex.pos.y);
                // Ŭ�������� �ִ� �ּ� �����ϱ�
            }
        }
        break;

    case TerrainEditor::RECT:

        // ���簢���� ���
        for (VertexType& vertex : vertices)
        {
            Vector3 pos = Vector3(vertex.pos.x, 0, vertex.pos.z); // �޽� �������� ���� ���θ� ���
            pickingPos.y = 0; //���� 0���� ����

            // "��" ���ϱ� (���簢���� ũ�⸦ ������ �ɰ��� ����� ���ϵ���)
            float half = brushBuffer->Get().range * 0.5f;

            //���μ��� �������� ��Ʈ ������� ���ϱ�
            float left = max(0, pickingPos.x - half);
            float right = max(0, pickingPos.x + half);
            float top = max(0, pickingPos.z + half);
            float bottom = max(0, pickingPos.z - half);

            for (UINT z = (UINT)bottom; z <= (UINT)top; ++z)
            {
                for (UINT x = (UINT)left; x <= (UINT)right; ++x)
                {
                    UINT index = width * (height - z - 1) + x; // ���� ���� �������� ������ �ִ� �ε����� �ٽ� ���ϱ�

                    if (index >= vertices.size()) continue; // �ε����� ������ ��Ͽ� ������ ����

                    vertices[index].pos.y = adjustValue * DELTA;
                    vertices[index].pos.y = Clamp(MIN_HEIGHT, MAX_HEIGHT, vertices[index].pos.y);
                }
            }
        }

        break;
    }

    // ������� ���� ����ġ����, �� ���� �ݺ�������� ��� ����
    // ���� ����� �޽ÿ��� ������Ʈ
    mesh->UpdateVertex();
}


void TerrainEditor::UpdateAlpha()
{
    // TODO : ���ĸ� ������...?
}

void TerrainEditor::AdjustAlpha() //���� �����ϱ�
{
    //�⺻�����δ� ���� ������ ���� ������ ����
    // �귯�� ������ ���� ���̿� ��ġ�� �κ��� �����Ѵ�

    vector<VertexType>& vertices = mesh->GetVertices();

    switch (brushType)
    {
    case TerrainEditor::CIRCLE:
        for (VertexType& vertex : vertices)
        {
            Vector3 pos = Vector3(vertex.pos.x, 0, vertex.pos.z);
            pickingPos.y = 0.0f;

            float distance = Distance(pos, pickingPos);

            if (distance <= brushBuffer->Get().range)
            {
                // ������ ���� ��� ����� ���İ��� �ٲ۴�
                // ��� : �ؽ�ó ǥ���� �Ǿ� �ִ� ������ ���, �ش� �ؽ�ó�� ���̰� ������ �ʴ� ������ �ٲ۴�
                vertex.alpha[selectMap] += adjustValue * DELTA;
                vertex.alpha[selectMap] = Clamp(0.0f, 1.0f, vertex.alpha[selectMap]);
            }
        }
        break;
    case TerrainEditor::SOFT_CIRCLE:
        for (VertexType& vertex : vertices)
        {
            Vector3 pos = Vector3(vertex.pos.x, 0, vertex.pos.z);
            pickingPos.y = 0.0f;

            float distance = Distance(pos, pickingPos);

            float temp = adjustValue * max(0, cos(distance / brushBuffer->Get().range));

            if (distance <= brushBuffer->Get().range)
            {
                vertex.alpha[selectMap] += temp * DELTA;
                vertex.alpha[selectMap] = Clamp(0.0f, 1.0f, vertex.alpha[selectMap]);
            }
        }
        break;
    case TerrainEditor::RECT:
    {
        float size = brushBuffer->Get().range * 0.5f;

        float left = max(0, pickingPos.x - size);
        float right = max(0, pickingPos.x + size);
        float top = max(0, pickingPos.z + size);
        float bottom = max(0, pickingPos.z - size);

        for (UINT z = (UINT)bottom; z <= (UINT)top; z++)
        {
            for (UINT x = (UINT)left; x <= (UINT)right; x++)
            {
                UINT index = width * (height - z - 1) + x;

                if (index >= vertices.size()) continue;

                vertices[index].alpha[selectMap] += adjustValue * DELTA;
                vertices[index].alpha[selectMap] = Clamp(0.0f, 1.0f, vertices[index].alpha[selectMap]);
            }
        }
    }
    break;
    }

    mesh->UpdateVertex();
}

void TerrainEditor::SaveHeightMap()
{
    if (ImGui::Button("SaveHeight"))
        DIALOG->OpenDialog("SaveHeight", "SaveHeight", ".png", ".");

    if (DIALOG->Display("SaveHeight"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            file = file.substr(projectPath.size() + 1, file.size());

            // �ȼ� �迭 ����� (�ȼ� : 8����Ʈ �� ���� = ����)
            // ��� �ȼ��� 8����Ʈ���� �Ѵ� x
            // ���� ���̶� ���� �پ��ϰ� ���� �ʿ䰡 ����
            UINT size = width * height * 4;
            uint8_t* pixels = new uint8_t[size];

            // ���� ������ ��������
            vector<VertexType> vertices = mesh->GetVertices();

            // �� ������ ��� ����ؼ� "����"�� ����ϰ� �ȼ����� �� ������(=�� ����) �ֱ�
            for (UINT i = 0; i < size / 4; i++)
            {
                float y = vertices[i].pos.y;

                uint8_t height = (y - MIN_HEIGHT) / (MAX_HEIGHT - MIN_HEIGHT) * 255;

                pixels[i * 4 + 0] = height;
                pixels[i * 4 + 1] = height;
                pixels[i * 4 + 2] = height;
                pixels[i * 4 + 3] = 255;
            }

            //�̹����� �����ؼ� �ش� �� �ϳ��ϳ��� ���� ������ �ȼ��� ������ ����ؼ� �ֱ�
            Image image; //DX ������ ����ü (Directx::Image�� �˻��ϴ� ���� ��õ)
            image.width = width;
            image.height = height;
            image.format = DXGI_FORMAT_R8G8B8A8_UNORM;
            image.rowPitch = width * 4;
            image.slicePitch = size;
            image.pixels = pixels;

            //������ ���� �̹����� DX ���� �Լ��� ���ؼ� �̹��� ����
            SaveToWICFile(image, WIC_FLAGS_FORCE_RGB,
                GetWICCodec(WIC_CODEC_PNG), ToWString(file).c_str());

            delete[] pixels;
        }

        DIALOG->Close();
    }
}

void TerrainEditor::LoadHeightMap()
{
    if (ImGui::Button("LoadHeight"))
        DIALOG->OpenDialog("LoadHeight", "LoadHeight", ".png", ".");

    if (DIALOG->Display("LoadHeight"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            file = file.substr(projectPath.size() + 1, file.size());

            // ���� �ʿ� �ҷ��� �̹����� �����ϰ�
            heightMap = Texture::Add(ToWString(file));

            //�������� (���� ����)
            Resize();
        }

        DIALOG->Close();
    }
}

//���� ��� ���� ������ 8����Ʈ �̹����� ���� ���� (�׸��� �Ʒ� �Լ����� �б�)
void TerrainEditor::SaveAlphaMap()
{
    if (ImGui::Button("SaveAlpha"))
        DIALOG->OpenDialog("SaveAlpha", "SaveAlpha", ".png", ".");

    if (DIALOG->Display("SaveAlpha"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            file = file.substr(projectPath.size() + 1, file.size());

            UINT size = width * height * 4;
            uint8_t* pixels = new uint8_t[size];

            vector<VertexType> vertices = mesh->GetVertices();

            for (UINT i = 0; i < size / 4; i++)
            {
                pixels[i * 4 + 0] = vertices[i].alpha[0] * 255;
                pixels[i * 4 + 1] = vertices[i].alpha[1] * 255;
                pixels[i * 4 + 2] = vertices[i].alpha[2] * 255;
                pixels[i * 4 + 3] = 255;
            }

            Image image;
            image.width = width;
            image.height = height;
            image.format = DXGI_FORMAT_R8G8B8A8_UNORM;
            image.rowPitch = width * 4;
            image.slicePitch = size;
            image.pixels = pixels;

            SaveToWICFile(image, WIC_FLAGS_FORCE_RGB,
                GetWICCodec(WIC_CODEC_PNG), ToWString(file).c_str());

            delete[] pixels;
        }

        DIALOG->Close();
    }
}

void TerrainEditor::LoadAlphaMap()
{
    if (ImGui::Button("LoadAlpha"))
        DIALOG->OpenDialog("LoadAlpha", "LoadAlpha", ".png", ".");

    if (DIALOG->Display("LoadAlpha"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            file = file.substr(projectPath.size() + 1, file.size());

            Texture* alphaMap = Texture::Add(ToWString(file));

            vector<Float4> pixels;
            alphaMap->ReadPixels(pixels);

            vector<VertexType>& vertices = mesh->GetVertices();

            for (UINT i = 0; i < vertices.size(); i++)
            {
                vertices[i].alpha[0] = pixels[i].z;
                vertices[i].alpha[1] = pixels[i].y;
                vertices[i].alpha[2] = pixels[i].x;
                vertices[i].alpha[3] = pixels[i].w;
            }

            mesh->UpdateVertex();
        }

        DIALOG->Close();
    }
}
