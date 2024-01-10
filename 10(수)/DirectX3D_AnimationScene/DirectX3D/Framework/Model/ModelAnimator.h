#pragma once

class ModelAnimator : public Model
{
    // ���� �������� �����ϴ� Ŭ����, Ȥ�� �������� ������ �� �� ��ü���� ��Ī

protected:

    // ������ �����͸� ������ ���� ����ü
    struct Frame
    {
        int clip = 0;       // �����ӿ� ��ϵǾ��� Ŭ���� �ڵ�
        UINT curFrame = 0;  // ���� ������
        float time = 0;     // �ð�
        float scale = 1;    // ������

        // �������� ������ ������ �����͸� �� ���� ������
    };

    class FrameBuffer : public ConstBuffer
    {
    public:
        struct Data
        {
            float takeTime = 0.2f;  // ��ü �ð�
            float tweenTime = 0;    // ��ȯ �ð�
            float runningTime = 0;  // ��� �ð�
            float padding;          // ������ ���� ���� ��� (���� ���� �ʿ��ص�) ����

            Frame cur;  //���� ������
            Frame next; //���� ������
        };

    public:
        FrameBuffer() : ConstBuffer(&data, sizeof(Data))
        {
            data.next.clip = -1; // -1 : "�׷� �� ����"
        }
        Data& Get() { return data; }

    private:
        Data data;
    };

public:

    ModelAnimator(string name); // �ִϸ��̼�, Ȥ�� �������� ���� �� ��ü�� �̸� �ޱ�
    ~ModelAnimator();

    void Update();
    void Render();
    void GUIRender();

    //���� �غ��ϱ� (�б�)
    void ReadClip(string clipName, UINT clipNum = 0); // �Ű����� : Ŭ���� �̸��� ���� �ε���

    //���� ����ϱ�
    void PlayClip(int clip, float scale = 1.0f, float takeTime = 0.2f);

    //��忡�� ��� �ޱ�
    Matrix GetTransformByNode(int nodeIndex); // ����� �ε����� �ʿ�

    // 0109 : Ŭ�� �ۿ��� ȣ���ϱ�
    ModelClip* GetClip(UINT index) { return clips[index]; }

protected:

    // �ؽ�ó�� �ִϸ��̼ǿ� �°� �����
    void CreateTexture();

    // Ŭ������ Ʈ������ ���� �����
    void CreateClipTransform(UINT index); // �������κ��� ������ ���ΰ�

    //������ ������Ʈ
    void UpdateFrame();


    bool isPlay = true; //����� ����

    vector<ModelClip*> clips; // ������ ���

    FrameBuffer* frameBuffer; // ������ ���� �غ��ؼ� �ε��ϱ�

    ClipTransform* clipTransforms;
    ClipTransform* nodeTransforms;

    // �ؽ�ó Ŭ������ �� �ᵵ �Ǵµ� ���� ��� ���� � ���� ����, ����� �޽��� �ٸ� ��ɿ� �־
    // ���� ������� Ŭ������ �� �� �ᵵ �ϴ� DX ���� Ŭ������ �� �� �ִ�
    ID3D11Texture2D* texture = nullptr;
    ID3D11ShaderResourceView* srv; //���̴��� ���� ���ҽ� �翬�� ���

    //�ʿ��ϸ� �� �� ������ �ؽ�ó�� ����

};

