#pragma once

class PixelScene : public Scene
{
    //�ȼ� �浹 ���� ���� ��

public:
    PixelScene();
    ~PixelScene();

    virtual void Update() override;
    virtual void Render(HDC hdc) override;

private:
    //�÷��̾�
    PixelCharacter* player;

    // ��� (�ܼ��� ��� �׸�x, �����ϸ� �ٴ��� ���� �ֵ��� �غ��� �ͽ��ϴ�!)
    Landscape* land;


/////////////////////////////////////////////////////////////////
    //���൵ (�� ���൵ ��ġ�� �ӽ��Դϴ�)
private:

    float totalProcess = 300.0f;

    float currentProcess = 0;
    float lastProcess = 0;

    bool ProcessChanged()
    {
        if (currentProcess != lastProcess)
        {
            lastProcess = currentProcess;
            return true;
        }
        else return false;
    }
};

