#pragma once

#include "Resources.h"

class CTexture : public CResources
{
public :
	CTexture();
	virtual ~CTexture();

public :
	HDC GetHDC() { return m_hDC; }
	UINT GetWidth() { return m_BitInfo.bmWidth; }
	UINT GetHeight() { return m_BitInfo.bmHeight; }
	BITMAP GetInfo() { return m_BitInfo; }

public :
	void Create(UINT _iWidth, UINT _iHeight);
	void Load(const wstring& _strFilePath);

private:
	HDC  m_hDC;
	HBITMAP m_hBit;
	BITMAP m_BitInfo;
};