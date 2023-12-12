#pragma once

class Camera : public Transform
{
public:
    Camera();
    ~Camera();

    void Update();
    void RenderUI();

    void SetView();

    void SetTarget(Transform* target) { this->target = target; }    

    Vector3 ScreenToWorld(Vector3 pos);
    Vector3 WorldToScreen(Vector3 pos);

    
private:
    void FreeMode();
    void FollowMode();

private:
    MatrixBuffer* viewBuffer;
    Matrix view;

    float moveSpeed = 50.0f;
    float rotSpeed = 10.0f;

    Transform* target = nullptr;    
};