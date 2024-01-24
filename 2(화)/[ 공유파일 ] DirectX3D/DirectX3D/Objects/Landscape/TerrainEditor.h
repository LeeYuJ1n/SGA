#pragma once

class TerrainEditor : public GameObject
{
    // Ŭ������ ���� : �ͷ��� ��Ŀ�� ����� ���� Ȯ���ؼ�,
    //                Ŭ���� ���� ������ ���� ����� �� �������� �ٲ� �� �ֵ��� �����

private:
    //�귯���� ����
    enum BrushType
    {
        CIRCLE, // ��
        SOFT_CIRCLE, // �����ڸ��� �帰 (�߽��� ����) ��
        RECT, // ���簢��
    };

    enum EditType // �귯�ø� ������ ��� �Ǵ°�?
    {
        HEIGHT, // ���� ���� (�⺻)
        ALPHA, // ���� ����
        NONE, // �ƹ� �ϵ� ���� (�� ��������)
    };

private:
    typedef VertexUVNormalTangentAlpha VertexType;
    const float MAX_HEIGHT = 20.0f; // �ִ� ���� �̸� ���س���
    const float MIN_HEIGHT = -20.0f; // �ּ� ���� ���� ���س���

    //�����ӿ�ũ ����� �ִ� �����͸� �̰����� �����´ٸ� �Ʒ� �ּ��� Ȱ��ȭ
    // -> ���� �ڵ�
    //const UINT MAX_SIZE = 30;


    //�귯�� ���ۿ� ���� ����

    class BrushBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            int type = 0; // �� �귯���� Ÿ��
            Float3 pickingPos; // ��� �ִ� ��ǥ
            float range = 5.0f; //�⺻ ����
            Float3 color = { 0, 0, 1 }; //�Ķ���. 0, 1, 0�̸� �ʷϻ�
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
            Float3 pos; //����
            int triangleSize; //�������

            Float3 dir; //����
            float padding; //"����" : �ٸ��� ���� ����
        };
        Data data;

    public:
        RayBuffer() : ConstBuffer(&data, sizeof(Data)) {}
        Data& Get() { return data; }
    };

    //����� ����� ����ü��
    struct InputDesc //desc : ����� ���� �ǹ̼���
    {
        //��� ����°�?
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

    Vector3 Pick();
    Vector3 ComputePick(); //��� ����ϱ� (�ʿ��ϸ� ó���ϱ�)
    Vector3 ComputePick(Vector3 sourcePos); // �Ű������� �ִ� �����ε� �Լ�
                                            // ���뿡�� �� �Լ��� ���� ������
                                            // ���콺 ��ġ ��� �Ű������� �޴´�
                                            // �ڿ����� �Ҹ������� (��ȿ���� �����ε�)
                                            // ������ ����� ������ �ϱ� ���� ���
    
    bool IsComputePick(Vector3& pos);     // ��ǻƮ �Ȱ� ���� ���� ����,
                                          // ��� �̸� ���ص� ������ ����� �����ϸ鼭
                                          // ��ȯ���� boolean�� �ִ� �Լ�

    float GetHeightByPos(Vector3 myPos);  // �Ű������� �־����� �ش� �����Ϳ� �´� ������ ���̸� ����

private:
    //�ʱ� ����
    void MakeMesh();
    void MakeNormal();
    void MakeTangent();

    //���� ���� �����
    
    // ��ü ������ �Ѱ�
    void MakeComputeData(); //���� ������ �����
    void Reset();  //������ �ʱ�ȭ
    void Resize(); //������ ũ�� �ʱ�ȭ

    // ���� ����
    void UpdateHeight(); // ���� ������Ʈ (������ ���� ��� �ݿ�, Ȥ�� ���� ���� ����)
    void AdjustHeight(); // ���� "����"   (����, Ȥ�� ������Ʈ �� ����)
    // * ���� �ܰ迡���� ��� ���� �������� Ȯ���� �� ������, �ϴ� �� �� �Լ��� ����,
    //   �׷��鼭�� �� ��Ʈ��� ���� �и��ϴ� (������ ����, ������ ���� Ȯ��)
    
    void UpdateAlpha(); // ���� ������Ʈ
    void AdjustAlpha(); // ���� ����

    // ImGUI ������ ���� ������ �߰� ���
    // ���� ���̺� �ε�
    void SaveHeightMap();
    void LoadHeightMap();

    // ���� ���̺� �ε�
    void SaveAlphaMap();
    void LoadAlphaMap();

    // ImGUI ���̺� �ε忡 �� ��θ� ������ (���ϸ��� ȣ���� �� ���� �״ϱ�)
    string projectPath;

    UINT width;
    UINT height;
    UINT triangleSize; // �ﰢ���� ũ�� : Ŭ�� �� ó���� ����

    UINT selectMap = 0;

    //�귯�� ���� ������ (�⺻���� ����)
    float adjustValue = 10.0f; //������ �� (����, Ȥ�� ����)
    BrushType brushType = BrushType::CIRCLE;
    EditType editType = EditType::HEIGHT; // ���̺��� ���ϱ�

    Mesh<VertexType>* mesh;

    // ���� ���� �߿� �ʿ��� �����͵�
    // * �귯�� ���� : ���� ��ŭ�� ��� �ٲ� �ǰ�?
    // * ���� ���� : ���콺 Ŀ���� �Է��� ��� ������ ���� �ǰ�?
    BrushBuffer* brushBuffer;
    RayBuffer* rayBuffer;
    StructuredBuffer* structuredBuffer; //������ ����ȭ�� ����� ������ ����

    //������ ���� ������
    // * �Է� ���
    // * ��� ���
    // �ش� ������� ���� (����)
    vector<InputDesc> inputs;
    vector<OutputDesc> outputs;

    // �ʿ� �� �ؽ�ó �̸� �غ�
    Texture* heightMap;
    Texture* secondMap;
    Texture* thirdMap;

    Vector3 pickingPos;

    //������ ������ ����� ����ϱ� ���� ������ ��� ���� ���̴�(��ǻƮ ���̴�)
    // *���� ���̴�
    ComputeShader* computeShader;

};