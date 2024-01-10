#pragma once

class Crowbar : public Model
{
	// CrowBar : 畴风规给惶捞, 艰瘤房措

public:
	Crowbar();
	~Crowbar();

	void Update();
	void Render();
	void GUIRender();

private:
	BoxCollider* collider;
};

