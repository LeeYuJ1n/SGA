#pragma once

class Device : public Singleton<Device>
{
private:
    friend class Singleton;

    Device();
    ~Device();

public:
    void Clear();
    void Present();

    ID3D11Device* GetDevice() { return device; }
    ID3D11DeviceContext* GetDeviceContext() { return deviceContext; }

    // 버퍼 호출하기(대기된 화면 정보에 간섭하기) = IDXGISwapChain
    IDXGISwapChain* GetSwapChain() { return swapChain; }

private:
    ID3D11Device* device;
    ID3D11DeviceContext* deviceContext;
    
    IDXGISwapChain* swapChain;
    ID3D11RenderTargetView* renderTargetView;
};