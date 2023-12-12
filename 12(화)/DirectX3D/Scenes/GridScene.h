#pragma once

class GridScene : public Scene
{
private:
    const int MAX_VALUE = 100;

public:
    GridScene();
    ~GridScene();
        
    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    void CreateMesh();

private:
    Material* material; 
    // 매티리얼, 머티리얼, 머트리얼
    // : 그림과, 그림을 표현할 때 렌더러(출력 과정)가 따라야 할 규칙들을 포함하는 정보
    //   다른 말로는 "어떤 그림을 어떻게 표현할지 정한 클래스(코드) / 컴포넌트(엔진)"

    Mesh<VertexColor>* mesh;

    UINT width, height;

    MatrixBuffer* worldBuffer;
};