#include "Framework.h"
#include "GBuffer.h"

GBuffer::GBuffer()
{
    //렌더 타겟 클래스를 객체로
    diffuseRender = new RenderTarget(WIN_WIDTH, WIN_HEIGHT, DXGI_FORMAT_R32G32B32A32_FLOAT);
                                    //기본 매개변수 그대로, 아래쪽 호출은 매개변수 생략
    specularRender = new RenderTarget();
    normalRender = new RenderTarget();

    //뎁스-스텐실 만들기
    depthStencil = new DepthStencil(WIN_WIDTH, WIN_HEIGHT, true);
                                  //기본 매개변수 2종(화면 크기) + 스텐실 버퍼 여부(자르는가 자르지 않는가)

    //렌더 타겟 뷰 정보를 변수에 따로 할당
    rtvs[0] = diffuseRender;    //여기서는 색조 텍스처만 출력해야지
    rtvs[1] = specularRender;   //여기서는 반사강도만 출력해야지
    rtvs[2] = normalRender;     //여기서는 법선정보만 출력해야지

    //셰이더 리소스 뷰도 할당(실제 그림 출력 과정 준비)
    srvs[0] = depthStencil->GetSRV();
    srvs[1] = diffuseRender->GetSRV();
    srvs[2] = specularRender->GetSRV();
    srvs[3] = normalRender->GetSRV();

    //출력된 그림을 실제로 화면에 투사할(물리적으로 출력할) 자리를 만들기
    FOR(4)
    {
        quads[i] = new Quad(Vector2(200, 200));
        quads[i]->Pos() = {100 + ((float)i * 200), 100, 0};
        Texture* texture = Texture::Add(L"G" + to_wstring(i), srvs[i]);
        quads[i]->GetMaterial()->SetDiffuseMap(texture);
        quads[i]->UpdateWorld();
    }
}

GBuffer::~GBuffer()
{
    delete diffuseRender;
    delete specularRender;
    delete normalRender;
    delete depthStencil;

    for (Quad* quad : quads)
        delete quad;

}

void GBuffer::SetMultiRenderTarget()
{
    // 렌더 타겟 여러 개 만들기 함수를 호출
    RenderTarget::SetMulti(rtvs, 3, depthStencil);
    // 매개변수 : 렌더 타겟..의 배열, 3개만큼, 뎁스-스텐실 변수 데이터에 의해 만들기
}

void GBuffer::PostRender()
{
    //다 만든 (이후 계속 계산하는) 렌더 타겟 정보를 쿼드로 출력
    for (Quad* quad : quads)
        quad->Render(); //쿼드 렌더
}

void GBuffer::SetSRVs()
{
    FOR(4)
    {
        //10+i 번 슬롯의 연산을 1만큼 셰이더 리소스로 취급하고 srv에 저장
        DC->PSSetShaderResources(10 + i, 1, &srvs[i]);
    }
}
