#include "Framework.h"

Font::Font()
{
	// 문자 정보 생성
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,           // 타 데이터와 교신 가능한 형태로
		__uuidof(IDWriteFactory), (IUnknown**)&writeFactory); // 정보를 생성할 때 자료형 크기와 정보에 맞춰서 생성하고 변수에 할당
	// * UUID : 하드웨어 / 소프트웨어에 부여되는 고유ID 값

	// 다이렉트X용으로 한번 더 만들기
	D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);

	IDXGIDevice* dxgiDevice; // 다이렉트X용 GUI 디바이스
	DEVICE->QueryInterface(&dxgiDevice);

	factory->CreateDevice(dxgiDevice, &device);

	// 여기까지 오면서 정리된 디바이스 정보를 통해 출력대상 도출
	device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
		&context); // 헤더에서 만든 DC에 반영

	IDXGISurface* dxgiSurface; // 버퍼 데이터 생성
	Device::Get()->GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&dxgiSurface);
	// 스왑체인 버퍼에 반영

	D2D1_BITMAP_PROPERTIES1 bp; // 비트맵 속성
	bp.pixelFormat.format    = DXGI_FORMAT_R8G8B8A8_UNORM; // RGB 8비트짜리 화소 데이터
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;     // 알파 적용 없음 (STRAIGHT는 입력이 있으면 반영을 하는 모드)
	bp.dpiX                  = 96; // dpi : dots per"inches" = "컴퓨터가 정한 단위 길이당 점 성분의 양"
	bp.dpiY                  = 96;
	bp.bitmapOptions         = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext          = nullptr;                    // 컬러 변경 출력 딱히 없음

	context->CreateBitmapFromDxgiSurface(dxgiSurface, &bp, &targetBitmap); // 버퍼에서 비트맵 생성(추출)

	context->SetTarget(targetBitmap); // 출력 대상 = 목표 비트맵

	// 다이렉트X의 방식으로 (레거시 2D와 Dwrite의 기능을 써서) "비트맵 화소"를 준비한다
	// 그리고 준비된 정보를 버퍼에 넣은 후 돌려받고 다음 출력 대상에 등록한다

	// -> 이렇게 그림을 그리는 방식으로 문자를 표현한다
}

Font::~Font()
{
	for (pair<string, ID2D1SolidColorBrush*> brush : brushes)
	{
		brush.second->Release();
	}

	for (pair<string, IDWriteTextFormat*> format : formats)
	{
		format.second->Release();
	}

	// 출력 데이터는 delete 대신 Release로 삭제
	factory->Release();
	writeFactory->Release();
	targetBitmap->Release();
	context->Release();
	device->Release();
}

void Font::AddColor(string key, float r, float g, float b, float a)
{
	if (brushes.count(key) > 0) return;

	ID2D1SolidColorBrush* brush = nullptr;
	
	D2D1::ColorF color(r, g, b, a);
	context->CreateSolidColorBrush(color, &brush);

	brushes[key] = brush;
}

void Font::AddStyle(string key, wstring font, float size,
	DWRITE_FONT_WEIGHT weight,    // 굵기
	DWRITE_FONT_STYLE style,      // 장평 자간
	DWRITE_FONT_STRETCH stretch)  // 늘림 정도
{
	if (formats.count(key) > 0) return;

	IDWriteTextFormat* format = nullptr;

	writeFactory->CreateTextFormat(font.c_str(), nullptr, // 폰트와 컬렉션 데이터로 DX용 문자정보 만들기
		weight, style, stretch, size, L"ko", &format);    // 매개변수를 모두 전달하고, 언어 코드를 ko(한국어)로 세팅한 후 정보 생성

	formats[key] = format;
}

void Font::SetColor(string key)
{
	if (brushes.count(key) == 0) return;

	curBrush = brushes[key];
}
	
void Font::SetStyle(string key)
{
	if (formats.count(key) == 0) return;

	curFormat = formats[key];
}

void Font::RenderText(string text, Float2 pos, Float2 size)
{
	// winAPI의 DrawText와 원리가 같다 = 사각형을 그리고, 문자를 넣고...

	// 크기가 지정되지 않았을 경우 기본값 적용
	if (size.x == 0.0f && size.y == 0.0f)
	{
		size.x = text.size() * curFormat->GetFontSize(); // 문자 길이 x 문자 하나당 크기
		size.y = curFormat->GetFontSize();
	}

	Float2 half = { size.x * 0.5f, size.y * 0.5f };

	// DX에 맞춰 쓰기 위해 위아래 바꾸기
	pos.y = WIN_HEIGHT - pos.y;

	// 사각형 그리기
	D2D1_RECT_F rect;
	rect.left   = pos.x - half.x;
	rect.right  = pos.x + half.x;
	rect.top    = pos.y - half.y;
	rect.bottom = pos.y + half.y;

	// 다이렉트X니까 wstring으로
	wstring outText = Utility::ToWString(text);
	
	// DC에 텍스트를 출력
	context->DrawTextW(outText.c_str(), outText.size(), curFormat, &rect, curBrush);
}

void Font::RenderText(wstring text, Float2 pos, Float2 size)
{
	// winAPI의 DrawText와 원리가 같다 = 사각형을 그리고, 문자를 넣고...

	// 크기가 지정되지 않았을 경우 기본값 적용
	if (size.x == 0.0f && size.y == 0.0f)
	{
		size.x = text.size() * curFormat->GetFontSize(); // 문자 길이 x 문자 하나당 크기
		size.y = curFormat->GetFontSize();
	}

	Float2 half = { size.x * 0.5f, size.y * 0.5f };

	// winAPI와 비슷하게 쓰기 위해 위 아래 바꾸기
	pos.y = WIN_HEIGHT - pos.y;

	// 사각형 그리기
	D2D1_RECT_F rect;
	rect.left   = pos.x - half.x;
	rect.right  = pos.x + half.x;
	rect.top    = pos.y - half.y;
	rect.bottom = pos.y + half.y;

	// DC에 텍스트를 출력
	context->DrawTextW(text.c_str(), text.size(), curFormat, &rect, curBrush);
}

