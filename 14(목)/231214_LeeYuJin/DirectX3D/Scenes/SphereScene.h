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
    Sphere* earth; // 지구

    GameObject* Pivot;   // 화성 중심점
    GameObject* Pivot2;   // 딜 중심점
    GameObject* Pivot3;   // 해왕성 중심점
    GameObject* Pivot4;   // 목성 중심점

    Sphere* baseball;    // 야구공
    Sphere* mars;        // 화성
    Sphere* mercury;     // 달
    Sphere* neptune;     // 해왕성
    Sphere* jupiter;     // 목성
};