#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define WIN_START_X 100
#define WIN_START_Y 100

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#define DELTA Timer::Get()->GetElapsedTime()

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>

#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//DirectXTex
#include <DirectXTex.h>
#pragma comment(lib, "DirectXTex.lib")

// FMOD : 음악 재생 라이브러리 중 하나.
// 내부코드가 어렵고, 메모리를 필수로 많이 잡아먹는 대신 외부 인터페이스가 편하고, 실행이 빠르다
// 그래서 이 FMOD 기능을 이용하면 앱에서 쉽게 소리를 재생하게 할 수 있다
#include "Libraries/inc/fmod.hpp"
#pragma comment(lib, "Libraries/lib/fmod_vc.lib")

//ImGui
#include <ImGui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#pragma comment(lib, "ImGui.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;

//std::function<void()> 자료형에 이름 새로 주기
typedef std::function<void()> Event;
typedef std::function<void(void*)> ParamEvent;

//Framework Header

#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Keyboard.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Observer.h"
#include "Framework/Utilities/tinyxml2.h"

#include "Framework/Utilities/Audio.h"

#include "Framework/Math/Vector2.h"
#include "Framework/Math/GameMath.h"
#include "Framework/Math/Transform.h"

using namespace GameMath;

#include "Framework/System/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/GlobalBuffer.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/Frame.h" // 프레임 먼저
#include "Framework/Render/Clip.h"  // 클립 다음에

#include "Framework/Environment/Environment.h"

#include "Framework/Collision/Collider.h"
#include "Framework/Collision/CircleCollider.h"
#include "Framework/Collision/RectCollider.h"

//Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Quad.h"
#include "Objects/Basic/Action.h"

//Object (Shooter) Header
#include "Objects/Shooting/Bullet.h"
#include "Objects/Shooting/BulletManager.h"

#include "Objects/Shooting/Enemy.h"
#include "Objects/Shooting/EnemyManager.h"

#include "Objects/Shooting/Plane.h"

//Object (Ninja) Header
#include "Objects/Character/Ninja/Ninja.h"
#include "Objects/Character/Ninja/NinjaAttack.h"
#include "Objects/Character/Ninja/NinjaJump.h"
#include "Objects/Character/Ninja/NinjaJumpAttack.h"
#include "Objects/Character/Ninja/NinjaMeleeAttack.h"
#include "Objects/Character/Ninja/NinjaRun.h"
#include "Objects/Character/Ninja/NinjaThrow.h"
#include "Objects/Character/Ninja/NinjaJumpThrow.h"

//Object (UI) Header
#include "Objects/UI/ProgressBar.h"
#include "Objects/UI/Button.h"

#include "GlobalEvent.h" // Global Event System

//Scene Header
#include "Scenes/Scene.h"
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"

extern HWND hWnd;
extern Vector2 mousePos;