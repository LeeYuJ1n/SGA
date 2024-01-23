#pragma once

class Texture
{
private:
    Texture(ID3D11ShaderResourceView* srv, ScratchImage& image, wstring file);
    ~Texture();

public:
    void PSSet(UINT slot = 0);

    Vector2 GetSize()
    {
        return Vector2(image.GetMetadata().width, image.GetMetadata().height);
    }

public:
    static Texture* Add(wstring file);
    static void Delete();

private:
    wstring file;

    ScratchImage image; // 실제 그림 정보 : 자료형이 DX에서 주어진다
    ID3D11ShaderResourceView* srv;

    static unordered_map<wstring, Texture*> textures;
};