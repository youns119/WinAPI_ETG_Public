#pragma once

class CUI;

class CUIManager : public Singleton<CUIManager>
{
public :
	CUIManager();
	virtual ~CUIManager();

public :
	void Init();
	void Update();
	void LateUpdate();
	void Render(HDC _hDC);
	void Release();

public :
	void MakeUI(CObject& _pTarget);
	void MakeBossUI(CObject& _pTarget);
	void DeleteBossUI();
	void DeleteMinimap();
};