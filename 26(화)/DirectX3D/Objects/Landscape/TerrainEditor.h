#pragma once

class TerrainEditor : public GameObject
{
	// Ŭ������ ���� : �ͷ��� ��Ŀ�� ����� ���� Ȯ���ؼ�, 
	//                Ŭ���� ���� ������ ���� ����� �� �������� �ٲ� �� �ֵ��� �����

private:
    // �귯���� ����
    enum BrushType
    {
        CIRCLE,        // ��
        SOFT_CIRCLE,   // ���� �ڸ��� �帰 ( �߽��� ���� �� )
        RECT,          // ���簢��
    };

    enum EditType     // �귯�ø� ������ ��� �Ǵ°�?
    {
        HEIGHT,       // ���� ���� ( �⺻ )
        ALPHA,        // ���� ����
        NONE,         // �ƹ� �ϵ� ���� ( �� �������� )
    };

private:
    typedef VertexUVNormalTangent VertexType;
    const float MAX_HEIGHT = 20.0f;  // �ִ� ���� �̸� ���س��� ( Value : 20.0 )
    const float MIN_HEIGHT = -1.0f;  // �ּ� ���� ���� ���س��� ( Value : -1.0 )

    // �����ӿ�ũ ����� �ִ� �����͸� �̰����� �����´ٸ� �Ʒ� �ּ��� Ȱ��ȭ
    // -> ���� �ڵ�
    // const UINT MAX_SIZE = 30;

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

    // ��ü ������ �Ѱ�
    void MakeComputeData();  // ���� ������ �����
    void Reset();            // ������ �ʱ�ȭ
    void Resize();           // ������ ũ�� �ʱ�ȭ

    // ���� ����
    void UpdateHeight();   // ���� ������Ʈ ( ������ ���� ��� �ݿ�, Ȥ�� ���� ���� ���� ) 
    void AdjustHeight();   // ���� "����" ( ����, Ȥ�� ������Ʈ �� ���� )
    // * ���� �ܰ迡���� ��� ���� �������� Ȯ���� �� ������, �ϴ� �� �� �Լ��� ����
    //   �׷��鼭�� �� ��Ʈ��� ���� �и��ϴ�

    void UpdateAlpha();    // ���� ������Ʈ
    void AdjustAlpha();    // ���� ����
    
    // ImGUI ������ ���� ������ �߰� ���
    // ���� ���̺� �ε�
    void SaveHeightMap();
    void LoadHeightmap();

    // ���� ���̺� �ε�
    void SaveAlphaMap();
    void LoadAlphaMap();

    // ImGUI ���̺� �ε忡 �� ��θ� ������ ( ���ϸ��� ȣ���� �� ���� �״ϱ� )
    string projectPath;

    UINT width;
    UINT height;
    UINT triangleSize; // �ﰢ���� ũ�� : Ŭ�� �� ó���� ����

    // �귯�� ���� ������ ( �⺻���� ���� )
    float     adjustValue = 10.0f; // ������ �� ( ����, Ȥ�� ���� ) ( Value : 10.0 )
    BrushType brushType   = BrushType::CIRCLE;
    EditType  editType    = EditType::HEIGHT;   // ���̺��� ���ϱ�

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

    // �ʿ� �� �ؽ�ó �̸� �غ�
    Texture* heightMap;
    Texture* secondMap;
    Texture* thirMap;

    Vector3 pickingPos;

    // ������ ������ ����� ����ϱ� ���� ������ ���� ���̴� ( ��ǻƮ ���̴� )
    // * ���� ���̴�
    ComputeShader* computeShader;
};

