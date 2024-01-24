#pragma once

class LeeYuJin_240124 : public Scene
{
public:
	LeeYuJin_240124();
	~LeeYuJin_240124();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    Terrain* level;
    Quad* image;
};

