#pragma once

class Crowbar : public Model
{
	// CrowBar : ���������, ��������

public:
	Crowbar();
	~Crowbar();

	void Update();
	void Render();
	void GUIRender();

private:
	BoxCollider* collider;
};

