#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_START_X 100
#define WIN_START_Y 100

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

#define CENTER_X (WIN_WIDTH * 0.5f)
#define CENTER_Y (WIN_HEIGHT * 0.5f)

// PI ratio (with misspelling)
#define PI 3.141592f
#define PHI 3.141592f // 이쪽은 오자인데, 사람들이 자주 써서 같이 매크로로....

// 색깔 매크로 : 투명값 등을 지정하고 싶을 때 여기 매크로 참조하면 편리
#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0) // *
#define BLUE RGB(0, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define CYAN RGB(0, 255, 255)
#define MAGENTA RGB(255, 0, 255) // ***
#define BLACK RGB(0, 0, 0)
#define WHITE RGB(255, 255, 255) // *
// 초록색, 흰색, 양홍색(마젠타) : 투명값으로 자주 선택되는 색상 3종 (특히 마젠타)
// -> 흰색은 편해서, 초록색과 마젠타는 현실에서 이 정도로 극단적인 색상을 잘 쓰지 않아서 (외우기도 쉽고)

#define DELTA Timer::Get()->GetElapsedTime()

#define KEY_DOWN(k) Keyboard::Get()->Down(k)
#define KEY_UP(k) Keyboard::Get()->Up(k)
#define KEY_PRESS(k) Keyboard::Get()->Press(k)

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map> // 비정렬 맵 : 정렬을 자동으로 수행하지 않는 맵 (수동으로 맵의 순서를 지정하기 편리)
#include <fstream>
#include <functional>

using namespace std;

//Framework Header
#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Keyboard.h"

using namespace Utility;

#include "Framework/Math/Vector2.h"
#include "Framework/Math/GameMath.h"

using namespace GameMath;

//Renderer Header
#include "Framework/Render/Texture.h"
#include "Framework/Render/Animation.h"

// Basic Object Header
#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Rect.h"
#include "Objects/Basic/Circle.h"
#include "Objects/Basic/Line.h"
#include "Objects/Basic/ImageRect.h"

// Objects Manager Header
#include "Manager/PoolingManager.h"

// Objects FX Header
#include "Objects/FX/Effect.h"
#include "Objects/FX/EffectManager.h"

// Inherited Object Header

#include "Objects/Angle/Cannon.h"

#include "Objects/Shooting/Bullet.h"
#include "Objects/Shooting/BulletManager.h"
#include "Objects/Shooting/Plane.h"
#include "Objects/Shooting/Enemy.h"
#include "Objects/Shooting/EnemyManager.h"

//Scene and Scene Specifics Header
#include "Scenes/Scene.h"

#include "Scenes/_SampleScene/Landscape.h"
#include "Scenes/_SampleScene/StageManager.h"
#include "Objects/_SampleCharacter/SampleCharacter.h"

#include "Objects/_PixelCharacter/PixelCharacter.h"

//Game Manager Header
#include "Manager/GameManager.h"

extern Vector2 mousePos;
extern HINSTANCE hInst;
extern HWND hWnd;