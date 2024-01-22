#include "Framework.h"
#include "GBuffer.h"

GBuffer::GBuffer()
{
    //���� Ÿ�� Ŭ������ ��ü��
    diffuseRender = new RenderTarget(WIN_WIDTH, WIN_HEIGHT, DXGI_FORMAT_R32G32B32A32_FLOAT);
                                    //�⺻ �Ű����� �״��, �Ʒ��� ȣ���� �Ű����� ����
    specularRender = new RenderTarget();
    normalRender = new RenderTarget();

    //����-���ٽ� �����
    depthStencil = new DepthStencil(WIN_WIDTH, WIN_HEIGHT, true);
                                  //�⺻ �Ű����� 2��(ȭ�� ũ��) + ���ٽ� ���� ����(�ڸ��°� �ڸ��� �ʴ°�)

    //���� Ÿ�� �� ������ ������ ���� �Ҵ�
    rtvs[0] = diffuseRender;    //���⼭�� ���� �ؽ�ó�� ����ؾ���
    rtvs[1] = specularRender;   //���⼭�� �ݻ簭���� ����ؾ���
    rtvs[2] = normalRender;     //���⼭�� ���������� ����ؾ���

    //���̴� ���ҽ� �䵵 �Ҵ�(���� �׸� ��� ���� �غ�)
    srvs[0] = depthStencil->GetSRV();
    srvs[1] = diffuseRender->GetSRV();
    srvs[2] = specularRender->GetSRV();
    srvs[3] = normalRender->GetSRV();

    //��µ� �׸��� ������ ȭ�鿡 ������(���������� �����) �ڸ��� �����
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
    // ���� Ÿ�� ���� �� ����� �Լ��� ȣ��
    RenderTarget::SetMulti(rtvs, 3, depthStencil);
    // �Ű����� : ���� Ÿ��..�� �迭, 3����ŭ, ����-���ٽ� ���� �����Ϳ� ���� �����
}

void GBuffer::PostRender()
{
    //�� ���� (���� ��� ����ϴ�) ���� Ÿ�� ������ ����� ���
    for (Quad* quad : quads)
        quad->Render(); //���� ����
}

void GBuffer::SetSRVs()
{
    FOR(4)
    {
        //10+i �� ������ ������ 1��ŭ ���̴� ���ҽ��� ����ϰ� srv�� ����
        DC->PSSetShaderResources(10 + i, 1, &srvs[i]);
    }
}
