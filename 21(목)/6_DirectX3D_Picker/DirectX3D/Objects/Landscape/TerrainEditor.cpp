#include "Framework.h"

TerrainEditor::TerrainEditor()
{

}

TerrainEditor::~TerrainEditor()
{
    delete mesh;
    delete brushBuffer;
    delete rayBuffer;
    delete structuredBuffer;
}

void TerrainEditor::Update()
{

}

void TerrainEditor::Render()
{

}

void TerrainEditor::RenderUI()
{

}

Vector3 TerrainEditor::Pick()
{
    return Vector3(0, 0, 0);
}

Vector3 TerrainEditor::ComputePick()
{
    return Vector3(0, 0, 0);
}

void TerrainEditor::MakeMesh()
{

}

void TerrainEditor::MakeNormal()
{

}

void TerrainEditor::MakeTangent()
{

}

void TerrainEditor::MakeComputeData()
{

}

void TerrainEditor::Reset()
{

}

void TerrainEditor::Resize()
{

}
