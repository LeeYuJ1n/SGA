#include "Framework.h"

Material::Material()
{
    diffuseMap  = Texture::Add(L"Textures/Color/White.png", L"DM");
    specularMap = Texture::Add(L"Textures/Color/White.png", L"SM");
    normalMap   = Texture::Add(L"Textures/Color/White.png", L"NM");

    buffer = new MaterialBuffer();
}

Material::Material(wstring shaderFile)
{
    SetShader(shaderFile);

    diffuseMap  = Texture::Add(L"Textures/Color/White.png", L"DM");
    specularMap = Texture::Add(L"Textures/Color/White.png", L"SM");
    normalMap   = Texture::Add(L"Textures/Color/White.png", L"NM");

    buffer = new MaterialBuffer();
}

Material::~Material()
{
    delete buffer;
}

void Material::Set()
{
    diffuseMap->PSSet(0);
    specularMap->PSSet(1);
    normalMap->PSSet(2);

    buffer->SetPS(1);

    vertexShader->Set();
    pixelShader->Set();
}

void Material::RenderUI()
{
    string title = name + "_Material";

    if (ImGui::TreeNode(title.c_str()))
    {
        ImGui::ColorEdit3("Diffuse", (float*)&buffer->Get().diffuse);
        ImGui::ColorEdit3("Specular", (float*)&buffer->Get().specular);
        ImGui::ColorEdit3("Ambient", (float*)&buffer->Get().ambient);

        ImGui::SliderFloat("Shininess", &buffer->Get().shininess, 1, 50);
        
        SelectMap("DM", DIFFUSE);   
        ImGui::SameLine();
        UnselectMap(DIFFUSE);
        SelectMap("SM", SPECULAR);        
        ImGui::SameLine();
        UnselectMap(SPECULAR);
        SelectMap("NM", NORMAL);
        ImGui::SameLine();
        UnselectMap(NORMAL);

        ImGui::TreePop();
    }    
}

void Material::SetShader(wstring shaderFile)
{
    vertexShader = Shader::AddVS(shaderFile);
    pixelShader  = Shader::AddPS(shaderFile);
}

void Material::SetDiffuseMap(wstring textureFile)
{
    if(textureFile.length() > 0)
        diffuseMap = Texture::Add(textureFile);
    else
        diffuseMap = Texture::Add(L"Textures/Color/White.png", L"DM");
}

void Material::SetSpecularMap(wstring textureFile)
{
    if (textureFile.length() > 0)
        specularMap = Texture::Add(textureFile);
    else
        specularMap = Texture::Add(L"Textures/Color/White.png", L"SM");
}

void Material::SetNormalMap(wstring textureFile)
{
    if (textureFile.length() > 0)
    {
        normalMap = Texture::Add(textureFile);
        buffer->Get().hasNormalMap = 1;
    }
    else
    {
        normalMap = Texture::Add(L"Textures/Color/White.png", L"NM");
        buffer->Get().hasNormalMap = 0;
    }        
}

void Material::SelectMap(string name, MapType type)
{
    ImGui::SetWindowFontScale(2.0f);    
    ImGui::TextColored(ImVec4(1, 0.5f, 0.8f, 1), name.c_str());    
    ImGui::SetWindowFontScale(1.0f);
    ImGui::SameLine();

    ImTextureID textureID = nullptr;

    switch (type)
    {
    case Material::DIFFUSE:
        textureID = diffuseMap->GetSRV();
        break;
    case Material::SPECULAR:
        textureID = specularMap->GetSRV();
        break;
    case Material::NORMAL:
        textureID = normalMap->GetSRV();
        break;
    default:
        break;
    }

    if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
    {
        DIALOG->OpenDialog(this->name + name, name, ".png,.jpg,.tga", ".");
    }

    if (DIALOG->Display(this->name + name))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            char path[128];
            GetCurrentDirectoryA(128, path);

            file = file.substr(strlen(path) + 1, file.length());

            switch (type)
            {
            case Material::DIFFUSE:
                SetDiffuseMap(ToWString(file));
                break;
            case Material::SPECULAR:
                SetSpecularMap(ToWString(file));
                break;
            case Material::NORMAL:
                SetNormalMap(ToWString(file));
                break;
            default:
                break;
            }            
        }

        DIALOG->Close();
    }
}

void Material::UnselectMap(MapType type)
{
    ImTextureID textureID = nullptr;

    switch (type)
    {
    case Material::DIFFUSE:
        textureID = Texture::Add(L"Textures/UI/Cancel.png", L"DMCancel")->GetSRV();
        break;
    case Material::SPECULAR:
        textureID = Texture::Add(L"Textures/UI/Cancel.png", L"SMCancel")->GetSRV();
        break;
    case Material::NORMAL:
        textureID = Texture::Add(L"Textures/UI/Cancel.png", L"NMCancel")->GetSRV();
        break;
    default:
        break;
    }

    if (ImGui::ImageButton(textureID, ImVec2(20, 20)))
    {
        switch (type)
        {
        case Material::DIFFUSE:
            SetDiffuseMap(L"");
            break;
        case Material::SPECULAR:
            SetSpecularMap(L"");
            break;
        case Material::NORMAL:
            SetNormalMap(L"");
            break;
        default:
            break;
        }
    }
}
