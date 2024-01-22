#pragma once
class Shadow
{
public:
    // 그림자의 원래는 그래서 결국 뭐냐?
    // ->그림자의 구현 방법은 정말 여러 가지가 있지만...
    //   (그리고 오늘 할 부분은 사실 이제 별로 안 쓰지만)

    // -> 오늘 여기서 구현할 방법은 렌더 타겟의 연장, 뎁스 스텐실 클래스의 응용
    //    모델과 똑같은 형태를(=똑같은 모델을, 또 다른 곳에) 한 번 더 그린다 (단 흑백으로)
    //    그리고 그려진 흑백의 실루엣을 월드에 또 투사해서 "겹치게" 만든다

    Shadow(UINT width = 2000, UINT height = 2000);
    ~Shadow();

    void SetRenderTarget();
    void SetRender();
    void PostRender();
    void GUIRender();

private:
    void SetViewProjection();

private:
    // 그림자의 크기(가로, 세로, 크기비율)
    UINT width;
    UINT height;
    float scale = 100;

    // 렌더 타겟 정보
    RenderTarget* renderTarget;
    DepthStencil* depthStencil;

    // 뷰 포트와 실제 행렬공간(프로젝션 행렬) 정보
    ViewBuffer* viewBuffer;
    MatrixBuffer* projectionBuffer;

    class Quad* quad;

};

