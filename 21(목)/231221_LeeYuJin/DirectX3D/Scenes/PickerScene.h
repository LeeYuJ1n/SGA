#pragma once

class PickerScene : public Scene
{
public:
	PickerScene();
	~PickerScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    TerrainPicker* picker;

    vector<Collider*> colliders;
};

