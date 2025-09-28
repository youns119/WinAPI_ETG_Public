#include "pch.h"
#include "Texture.h"

#include "Main.h"

CTexture::CTexture()
	: m_hDC(0)
	, m_hBit(0)
	, m_BitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBit);
}

void CTexture::Create(UINT _iWidth, UINT _iHeight)
{
	HDC hDC = CMain::Get()->GetHDC();

	m_hBit = CreateCompatibleBitmap(hDC, _iWidth, _iHeight);
	m_hDC = CreateCompatibleDC(hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hOldBit);

	GetObject(m_hBit, sizeof(BITMAP), &m_BitInfo);
}

void CTexture::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	m_hDC = CreateCompatibleDC(CMain::Get()->GetHDC());

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBit);

	GetObject(m_hBit, sizeof(BITMAP), &m_BitInfo);
}