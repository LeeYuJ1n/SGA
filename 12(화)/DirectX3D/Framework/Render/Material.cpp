#include "Framework.h"

Material::Material()
{
}

Material::Material(wstring shaderFile)
{
    SetShader(shaderFile);
}

Material::~Material()
{
}

void Material::Set()
{
    if (diffuseMap)
        diffuseMap->PSSet(0);
    else
        Texture::Add(L"Textures/Color/White.png")->PSSet(0);

    vertexShader->Set();
    pixelShader->Set();
}

void Material::RenderUI()
{
    string title = name + "_Material";

    if (ImGui::TreeNode(title.c_str()))
    {
        ImTextureID textureID = diffuseMap->GetSRV();

        if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
        {
            DIALOG->OpenDialog("Map", "Select Texture File", ".*", ".");
        }

        ImGui::TreePop();
    }

    if (DIALOG->Display("Map"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            char path[128];
            GetCurrentDirectoryA(128, path);                        //*작업중...
            file = file.substr(strlen(path) + 1, file.length());    //*작업중...

            SetDiffuseMap(ToWString(file));
        }

        DIALOG->Close();
    }
}

void Material::SetShader(wstring shaderFile)
{
    vertexShader = Shader::AddVS(shaderFile);
    pixelShader = Shader::AddPS(shaderFile);
}

void Material::SetDiffuseMap(wstring textureFile)
{
    if(textureFile.length() > 0)
        diffuseMap = Texture::Add(textureFile);
    else
        diffuseMap = nullptr;
}
