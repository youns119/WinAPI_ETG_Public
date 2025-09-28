#pragma once

#include "Scene.h"

class CTexture;

class CMenu : public CScene
{
public :
	CMenu();
	virtual ~CMenu();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	void SetSceneChange(bool _bSceneChange) { m_bSceneChange = _bSceneChange; }

public :
	void Enter(CObject* _pPlayer) override;
	void Exit(CObject* _pPlayer) override;

public :
	virtual void SetCollision() override;

private :
	CTexture* m_pTexture;

	bool m_bSceneChange;
};