#pragma once

class SphereScene : public Scene
{
public:
    SphereScene();
    ~SphereScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Sphere* sphere;
    Sphere* earth; // ����

    GameObject* Pivot;   // ȭ�� �߽���
    GameObject* Pivot2;   // �� �߽���
    GameObject* Pivot3;   // �ؿռ� �߽���
    GameObject* Pivot4;   // �� �߽���

    Sphere* baseball;    // �߱���
    Sphere* mars;        // ȭ��
    Sphere* mercury;     // ��
    Sphere* neptune;     // �ؿռ�
    Sphere* jupiter;     // ��
};