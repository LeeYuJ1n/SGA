#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
    // 원형 FBX에서 모델을 추출해서 빨리 읽을 수 있는 포맷으로 다시 저장하는 것이 목적인 씬

    // 이 안에서 어떤 업데이트나 렌더가 돌아야 할 필요....없을 듯

    // 딱 만들기만

    string name = "Fox";
    string file = "Models/FBX/" + name + ".fbx";

    // 익스포터 호출 후, 매티리얼과 메쉬 순으로 포맷 다시 만들기
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
