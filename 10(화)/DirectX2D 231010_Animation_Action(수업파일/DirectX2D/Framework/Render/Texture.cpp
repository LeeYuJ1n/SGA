#include "Framework.h"

//그림을 받아와서 텍스처(DX에서 쓰기 위한 준비 자료)로 만드는 과정
//DX의 인터페이스가 많아서 단순 암기할 필요보다는 흐름을 봐두는 편이 좋다

unordered_map<wstring, Texture*> Texture::textures;

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image, wstring file)
    : srv(srv), image(move(image)), file(file)
{
}

Texture::~Texture()
{
    srv->Release();
}

void Texture::PSSet(UINT slot)
{
    DC->PSSetShaderResources(slot, 1, &srv);
}

//윈API에도 있었던 텍스처 추가 함수 : 코드의 모양과 철자가 바뀌었지 원리는 윈API와 거의 동일
Texture* Texture::Add(wstring file)
{
    if (textures.count(file) > 0)
        return textures[file];

    //중요한 건 여기서 세 줄 (그림의 정보를 파일에서 도출하고, 셰이더의 정보를 볼 수 있는 변수 생성)
    ScratchImage image;
    LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    ID3D11ShaderResourceView* srv;

    //셰이더의 리소스 정보 보기
    CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(),
        image.GetMetadata(), &srv);

    //텍스처 생성
    textures[file] = new Texture(srv, image, file);

    return textures[file];
}

void Texture::Delete()
{
    for (pair<wstring, Texture*> texture : textures)
        delete texture.second;
}
