#pragma once

class TerrainEditor : public GameObject
{
	// Ŭ������ ���� : �ͷ��� ��Ŀ�� ����� ���� Ȯ���ؼ�, 
	//                Ŭ���� ���� ������ ���� ����� �� �������� �ٲ� �� �ֵ��� �����
private:
    typedef VertexUVNormalTangent VertexType;
    const float MAX_HEIGHT = 20.0f; // �ִ� ���� �̸� ���س���

    // �귯�� ���ۿ� ���� ����
    class BrushBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            int type = 0;               // �� �귯���� Ÿ��
            Float3 pickingPos;          // ��� �ִ� ��ǥ
            float range = 5.0f;         // �⺻ ����
            Float3 color = { 0, 0, 1 }; // �Ķ���, 0, 1, 0�̸� �ʷϻ�
        };

        Data data;

    public:
        BrushBuffer() : ConstBuffer(&data, sizeof(Data)) {}
        Data& Get() { return data; }
    };

    class RayBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Float3 pos;         // ����
            int triangleSize;   // ���� ����

            Float3 dir;         // ����
            float padding;      // "����" : �ٸ��� ���� ����
        };

        Data data;

    public:
        RayBuffer() : ConstBuffer(&data, sizeof(Data)) {}
        Data& Get() { return data; }
    };

    // ����� ����� ����ü��
    struct InputDesc // desc : ����� ���� �ǹ� ����
    {
        // ��� ����°�?
        Float3 v0;
        Float3 v1;
        Float3 v2;
    };

    struct OutputDesc
    {
        int picked;
        float distance;
    };

public:
    TerrainEditor();
    ~TerrainEditor();

    void Update();
    void Render();
    void RenderUI();

    Vector3 Pick();        // ��� �ൿ
    Vector3 ComputePick(); // ��� ����ϱ� ( �ʿ��ϸ� ó���ϱ� )

private:
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();

    // ���� ���� �����
    void MakeComputeData();  // ���� ������ �����
    void Reset();            // ������ �ʱ�ȭ
    void Resize();           // ������ ũ�� �ʱ�ȭ

    UINT width;
    UINT height;
    UINT triangleSize; // �ﰢ���� ũ�� : Ŭ�� �� ó���� ����

    Mesh<VertexType>* mesh;

    // ���� ���� �߿� �ʿ��� �����͵�
    // * �귯�� ���� : ���� �󸶸�ŭ�� ��� �ٲ� �ǰ�?
    // * ���� ����   : ���콺 Ŀ���� �Է��� �󸶳� ��� ������ ���� �ǰ�?
    BrushBuffer* brushBuffer;
    RayBuffer* rayBuffer;
    StructuredBuffer* structuredBuffer; // ������ ����ȭ�� ����� �����ϴ� ����

    // ������ ���� ������
    // * �Է� ���
    // * ��� ���
    // �ش� ������� ���� ( ���� )

    vector<InputDesc> inputs;
    vector<OutputDesc> outputs;

    Texture* heightMap;

    Vector3 pickingPos;

    // ������ ������ ����� ����ϱ� ���� ������ ���� ���̴� ( ��ǻƮ ���̴� )
    // * ���� ���̴�
    ComputeShader* computeShader;
};

