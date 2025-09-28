#pragma once

class CTexture;

class CMain : public Singleton<CMain>
{
public :
	CMain();
	virtual ~CMain();

public :
	int	Init(HWND _hWnd, POINT _tResolution);
	void Update();
	void LateUpdate();
	void Render();
	void Release();

public :
	void Run();

public :
	HWND GetHwnd() const { return m_hWnd; }
	POINT GetResolution() const { return m_tResolution; }
	HDC GetHDC() const { return m_hDC; }

public :
	void Clear();
	void TextureSetting();

private :
	HWND m_hWnd;
	POINT m_tResolution;
	HDC m_hDC;

private :
	CTexture* m_pBackBuffer;
};