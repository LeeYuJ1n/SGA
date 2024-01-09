#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    // ���� FBX���� ���� �����ؼ� ���� ���� �� �ִ� �������� �ٽ� �����ϴ� ���� ������ ��

    // �� �ȿ��� � ������Ʈ�� ������ ���ƾ� �� �ʿ�....���� ��

    // �� ����⸸

    string name = "Fox";
    string file = "Models/FBX/" + name + ".fbx";

    // �ͽ����� ȣ�� ��, ��Ƽ����� �޽� ������ ���� �ٽ� �����
    ModelExporter* exporter = new ModelExporter(name, file);
    // exporter->ExportMaterial();
    exporter->ExportMesh();

    delete exporter;

}

ModelExportScene::~ModelExportScene()
{
}

void ModelExportScene::Update()
{
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
}

void ModelExportScene::PostRender()
{
}

void ModelExportScene::GUIRender()
{
}
