#pragma once

// 적이 나오지 않는, 비행기만 있는 "임시 장면"을 연출

class TempScene : public Scene
{
public:
    TempScene();
    ~TempScene();

    virtual void Update() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void Init() override;
    virtual void Quit() override;

private:

    Plane* plane;

};

