#include "Framework.h"

Font::Font()
{
	// ���� ���� ����
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,           // Ÿ �����Ϳ� ���� ������ ���·�
		__uuidof(IDWriteFactory), (IUnknown**)&writeFactory); // ������ ������ �� �ڷ��� ũ��� ������ ���缭 �����ϰ� ������ �Ҵ�
	// * UUID : �ϵ���� / ����Ʈ��� �ο��Ǵ� ����ID ��

	// ���̷�ƮX������ �ѹ� �� �����
	D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &factory);

	IDXGIDevice* dxgiDevice; // ���̷�ƮX�� GUI ����̽�
	DEVICE->QueryInterface(&dxgiDevice);

	factory->CreateDevice(dxgiDevice, &device);

	// ������� ���鼭 ������ ����̽� ������ ���� ��´�� ����
	device->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS,
		&context); // ������� ���� DC�� �ݿ�

	IDXGISurface* dxgiSurface; // ���� ������ ����
	Device::Get()->GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&dxgiSurface);
	// ����ü�� ���ۿ� �ݿ�

	D2D1_BITMAP_PROPERTIES1 bp; // ��Ʈ�� �Ӽ�
	bp.pixelFormat.format    = DXGI_FORMAT_R8G8B8A8_UNORM; // RGB 8��Ʈ¥�� ȭ�� ������
	bp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;     // ���� ���� ���� (STRAIGHT�� �Է��� ������ �ݿ��� �ϴ� ���)
	bp.dpiX                  = 96; // dpi : dots per"inches" = "��ǻ�Ͱ� ���� ���� ���̴� �� ������ ��"
	bp.dpiY                  = 96;
	bp.bitmapOptions         = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext          = nullptr;                    // �÷� ���� ��� ���� ����

	context->CreateBitmapFromDxgiSurface(dxgiSurface, &bp, &targetBitmap); // ���ۿ��� ��Ʈ�� ����(����)

	context->SetTarget(targetBitmap); // ��� ��� = ��ǥ ��Ʈ��

	// ���̷�ƮX�� ������� (���Ž� 2D�� Dwrite�� ����� �Ἥ) "��Ʈ�� ȭ��"�� �غ��Ѵ�
	// �׸��� �غ�� ������ ���ۿ� ���� �� �����ް� ���� ��� ��� ����Ѵ�

	// -> �̷��� �׸��� �׸��� ������� ���ڸ� ǥ���Ѵ�
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

	// ��� �����ʹ� delete ��� Release�� ����
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
	DWRITE_FONT_WEIGHT weight,    // ����
	DWRITE_FONT_STYLE style,      // ���� �ڰ�
	DWRITE_FONT_STRETCH stretch)  // �ø� ����
{
	if (formats.count(key) > 0) return;

	IDWriteTextFormat* format = nullptr;

	writeFactory->CreateTextFormat(font.c_str(), nullptr, // ��Ʈ�� �÷��� �����ͷ� DX�� �������� �����
		weight, style, stretch, size, L"ko", &format);    // �Ű������� ��� �����ϰ�, ��� �ڵ带 ko(�ѱ���)�� ������ �� ���� ����

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
	// winAPI�� DrawText�� ������ ���� = �簢���� �׸���, ���ڸ� �ְ�...

	// ũ�Ⱑ �������� �ʾ��� ��� �⺻�� ����
	if (size.x == 0.0f && size.y == 0.0f)
	{
		size.x = text.size() * curFormat->GetFontSize(); // ���� ���� x ���� �ϳ��� ũ��
		size.y = curFormat->GetFontSize();
	}

	Float2 half = { size.x * 0.5f, size.y * 0.5f };

	// DX�� ���� ���� ���� ���Ʒ� �ٲٱ�
	pos.y = WIN_HEIGHT - pos.y;

	// �簢�� �׸���
	D2D1_RECT_F rect;
	rect.left   = pos.x - half.x;
	rect.right  = pos.x + half.x;
	rect.top    = pos.y - half.y;
	rect.bottom = pos.y + half.y;

	// ���̷�ƮX�ϱ� wstring����
	wstring outText = Utility::ToWString(text);
	
	// DC�� �ؽ�Ʈ�� ���
	context->DrawTextW(outText.c_str(), outText.size(), curFormat, &rect, curBrush);
}

void Font::RenderText(wstring text, Float2 pos, Float2 size)
{
	// winAPI�� DrawText�� ������ ���� = �簢���� �׸���, ���ڸ� �ְ�...

	// ũ�Ⱑ �������� �ʾ��� ��� �⺻�� ����
	if (size.x == 0.0f && size.y == 0.0f)
	{
		size.x = text.size() * curFormat->GetFontSize(); // ���� ���� x ���� �ϳ��� ũ��
		size.y = curFormat->GetFontSize();
	}

	Float2 half = { size.x * 0.5f, size.y * 0.5f };

	// winAPI�� ����ϰ� ���� ���� �� �Ʒ� �ٲٱ�
	pos.y = WIN_HEIGHT - pos.y;

	// �簢�� �׸���
	D2D1_RECT_F rect;
	rect.left   = pos.x - half.x;
	rect.right  = pos.x + half.x;
	rect.top    = pos.y - half.y;
	rect.bottom = pos.y + half.y;

	// DC�� �ؽ�Ʈ�� ���
	context->DrawTextW(text.c_str(), text.size(), curFormat, &rect, curBrush);
}

