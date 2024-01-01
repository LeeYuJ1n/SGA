﻿#pragma once

#define APP_TITLE L"DirectX 3D"

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define DELTA Timer::Get()->GetElapsedTime()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define CAM Environment::Get()->GetMainCamera()

#define DIALOG ImGuiFileDialog::Instance()

// 터레인 에디터 작성 중에 만든 매크로,
// 필요하면 이쪽은 주석으로, 데이터는 클래스 안에
// 여기 적으면 전역 매크로가 되는데, 클래스 안에 넣으면 그 클래스에서만 안전하게 쓸 수 있음
#define MAX_LIGHT 10
#define MAX_SIZE 300

#define BLOCKMANAGER BlockManager::Get()

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <assert.h>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <DirectXCollision.h> // 충돌 구현에 필요한 각종 수학 기능
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <ImGuiFileDialog.h>
#include <d2d1_2.h>
#include <dwrite.h>


#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "DirectXTex.lib")
#pragma comment(lib, "ImGui.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMVECTOR Vector4;
typedef XMMATRIX Matrix;
typedef XMFLOAT4X4 Float4x4;

typedef function<void()> Event;
typedef function<void(void*)> ParamEvent;
typedef function<void(int)> IntParamEvent;

//Framework Header
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/BinaryReader.h"
#include "Framework/Utilities/BinaryWriter.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/tinyxml2.h"
#include "Framework/Utilities/Observer.h"
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Font.h"

using namespace Utility;

#include "Framework/System/Device.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/GlobalBuffer.h"
#include "Framework/Buffer/RawBuffer.h"
#include "Framework/Buffer/StructuredBuffer.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"
#include "Framework/Shader/ComputeShader.h"

#include "Framework/State/RasterizerState.h"
#include "Framework/State/SamplerState.h"
#include "Framework/State/BlendState.h"

#include "Framework/Math/Vector2.h"
#include "Framework/Math/Vector3.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/GameMath.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/Material.h"
#include "Framework/Render/Mesh.h"

// 충돌체를 폴더 파일 중심으로 정리해서 하나씩 읽도록 할 때
#include "Framework/Collision/Collider.h"
#include "Framework/Collision/BoxCollider.h"
#include "Framework/Collision/SphereCollider.h"

using namespace GameMath;

#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Quad.h"
#include "Objects/Basic/Cube.h"
#include "Objects/Basic/Sphere.h"

#include "Objects/Manager/BlockManager.h"

#include "Objects/Landscape/Terrain.h"
#include "Objects/Landscape/TerrainPicker.h"
#include "Objects/Landscape/TerrainEditor.h"

// 충돌체를 게임오브젝트의 컴포넌트로 만들었음을 확실히 하려면 여기서 로딩
// #include "Framework/Collision/Collider.h"

#include "Objects/TestCharacter/TestActor.h"

//Scene Header
#include "Scenes/Scene.h"

#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"

extern HWND hWnd;
extern Vector3 mousePos; // 마우스 위치 (3차원)