#include "Framework.h"
#include "Shadow.h"

Shadow::Shadow(UINT width, UINT height) : width(width), height(height)
{
    //����Ÿ��
    renderTarget = new RenderTarget(width, height); //�Ű������� ���� ���� ���� ����
    depthStencil = new DepthStencil(width, height);

    //�������(��+����)
    viewBuffer = new ViewBuffer();
    projectionBuffer = new MatrixBuffer();

    //�����غ�
    quad = new Quad(Vector2(200, 200)); // �۾��� �� Ȯ�ο� (Ȯ���� ���� ���� ����)
    quad->Pos() = { 100, 100, 0 }; //ȭ�� �ѱ�������
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
    renderTarget->Set(depthStencil); // ���� ���ٽ� ������ ���� Ÿ�ٿ� ����
    SetViewProjection();             // �ؿ� �ִ� �Լ��� ����ͼ� ȣ��
}

void Shadow::SetRender()
{
    viewBuffer->SetVS(11);          // 11, 12 : ���۵� ���̴��� ����Ǹ� Ư���� �ؽ�ó ������ ������
    projectionBuffer->SetVS(12);    // 11 : ��ǻ��, 12 : ����ŧ��

    DC->PSSetShaderResources(10, 1, &renderTarget->GetSRV()); // ���� ���ٽ��� �� Ŭ������ ����ǰ�
}

void Shadow::PostRender()
{
    quad->Render();
}

void Shadow::GUIRender()
{
    //���� �׸��� ũ�� ������ �ٲ� ��
    ImGui::SliderFloat("Scale", &scale, 1, 10);
}

void Shadow::SetViewProjection()
{
    // ���� : ���ÿ���(����Ʈ)�� ���� ����(����� ���)�� �����Ѵ�
    //        -> �׸��� ���� ����� ������ ���忡 �����ϱ�

    //���� ȣ�� : �� ����
    LightBuffer::Light* light = Environment::Get()->GetLight(0);
                                // ���� ������ ���� �ð��� : ���⼭�� ������ ǥ���ϸ� "�޺� ����"
                                // �̷��� ȣ��� ���� �����̳� ������ �����ϸ� �׸��ڵ� ���� ����

    //�� ��Ʈ ����
    Matrix view = XMMatrixLookAtLH(Vector3(light->pos), Vector3(), Vector3(0, 1, 0));
                //�޼��� �ٶ󺸴� ��� ��ǥ�� ���� : �Ű������� ����, ����, ������(��)

    //��İ��� ����
    Matrix projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1, 0.1f, 5000);
                        //�޼���ǥ�� ����� �Ϻ� �߶� ���� : �Ű������� �⺻ȸ����
                        //                                            + ũ�����
                        //                                            + ����� �Ÿ�(��� �ּҰŸ�)
                        //                                            + �� �Ÿ� (��� �ִ�Ÿ�)

    viewBuffer->Set(view, XMMatrixInverse(nullptr, view)); // �� ���� ����
    projectionBuffer->Set(projection); //��İ��� (����� ���) ����

    //�� ���۸� ���̴� ���꿡 ���
    viewBuffer->SetVS(1);
    projectionBuffer->SetVS(2);
}
