#include "Framework.h"
#include "Shadow.h"

Shadow::Shadow(UINT width, UINT height) : width(width), height(height)
{
    //렌더타겟
    renderTarget = new RenderTarget(width, height); //매개변수로 받은 가로 세로 전달
    depthStencil = new DepthStencil(width, height);

    //출력정보(뷰+투사)
    viewBuffer = new ViewBuffer();
    projectionBuffer = new MatrixBuffer();

    //쿼드준비
    quad = new Quad(Vector2(200, 200)); // 작업용 겸 확인용 (확인을 위한 소형 쿼드)
    quad->Pos() = { 100, 100, 0 }; //화면 한구석으로
    quad->UpdateWorld();
    Texture* texture = Texture::Add(L"DepthMap", renderTarget->GetSRV());
    quad->GetMaterial()->SetDiffuseMap(texture);
}

Shadow::~Shadow()
{
    delete renderTarget;
    delete depthStencil;
    delete viewBuffer;
    delete projectionBuffer;
    delete quad;
}

void Shadow::SetRenderTarget()
{
    renderTarget->Set(depthStencil); // 뎁스 스텐실 정보를 렌더 타겟에 세팅
    SetViewProjection();             // 밑에 있는 함수를 끌어와서 호출
}

void Shadow::SetRender()
{
    viewBuffer->SetVS(11);          // 11, 12 : 디퍼드 셰이더가 적용되면 특정한 텍스처 정보만 나가게
    projectionBuffer->SetVS(12);    // 11 : 디퓨즈, 12 : 스페큘러

    DC->PSSetShaderResources(10, 1, &renderTarget->GetSRV()); // 뎁스 스텐실이 이 클래스에 적용되게
}

void Shadow::PostRender()
{
    quad->Render();
}

void Shadow::GUIRender()
{
    //이후 그림자 크기 비율을 바꿀 때
    ImGui::SliderFloat("Scale", &scale, 1, 10);
}

void Shadow::SetViewProjection()
{
    // 목적 : 가시영역(뷰포트)와 실제 공간(투사된 행렬)을 적용한다
    //        -> 그림자 연산 결과를 실제로 월드에 투사하기

    //선행 호출 : 빛 버퍼
    LightBuffer::Light* light = Environment::Get()->GetLight(0);
                                // 세부 설명은 다음 시간에 : 여기서는 간단히 표현하면 "햇빛 묘사"
                                // 이렇게 호출된 빛의 방향이나 정보를 조정하면 그림자도 조정 가능

    //뷰 포트 내기
    Matrix view = XMMatrixLookAtLH(Vector3(light->pos), Vector3(), Vector3(0, 1, 0));
                //왼손을 바라보는 행렬 좌표를 내기 : 매개변수는 원점, 초점, 기준축(위)

    //행렬공간 내기
    Matrix projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1, 0.1f, 5000);
                        //왼손좌표계 행렬을 일부 잘라서 대입 : 매개변수는 기본회전값
                        //                                            + 크기비율
                        //                                            + 가까운 거리(출력 최소거리)
                        //                                            + 먼 거리 (출력 최대거리)

    viewBuffer->Set(view, XMMatrixInverse(nullptr, view)); // 뷰 버퍼 세팅
    projectionBuffer->Set(projection); //행렬공간 (투사된 행렬) 세팅

    //두 버퍼를 셰이더 연산에 등록
    viewBuffer->SetVS(1);
    projectionBuffer->SetVS(2);
}
