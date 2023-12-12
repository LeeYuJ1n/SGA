#pragma once

class Material
{
public:
    Material();
    Material(wstring shaderFile);
    ~Material();

    void Set();

    void RenderUI();

    void SetShader(wstring shaderFile);
    void SetDiffuseMap(wstring textureFile);
    
private:
    // ��Ƽ���� Ŭ������ �⺻������ ������ ��
    // -> ���� �׸��̳� (���� �߿��� ����) : �ڵ� ������ ���ϸ� �� ������ ���� nullptr�� ���������� �� �ȴ�
    // -> �� �׸��� ��� ǥ���� ���ΰ�
    //    : ���̴� ����
    //    : �ڵ峪 ���� ��� �߰��� ���ϴ� ���� ������(�̹��� �ĺ���, ä��, ���, �Ｎ ���� ǥ�� ��...)
    //    : �׷��� ��Ƽ������� ������ �� �ۿ��� ��� ���ǵǴ����� ���� ��, �ڵ�, �������� �ٸ���

    string name; // �̸��̶�� ����

    VertexShader* vertexShader; // � ���̴��� ����� ���ΰ�
    PixelShader* pixelShader;   // � ���̴��� ����� ���ΰ�

    Texture* diffuseMap = nullptr; // �ʱⰪ�� �̷��� ������, ��ü�� ������� ���� �ݵ�� �����ϴ� �׸��� �־�� �Ѵ�
};