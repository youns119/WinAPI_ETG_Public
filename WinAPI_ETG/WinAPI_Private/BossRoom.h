#pragma once

#include "Scene.h"

class CTexture;

class CBossRoom : public CScene
{
public :
	CBossRoom();
	virtual ~CBossRoom();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	void Enter(CObject* _pPlayer) override;
	void Exit(CObject* _pPlayer) override;

public :
	virtual void SetCollision() override;

private :
	CTexture* m_pTexture;
};