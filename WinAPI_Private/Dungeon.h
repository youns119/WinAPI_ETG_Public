#pragma once

#include "Scene.h"

class CTexture;

class CDungeon : public CScene
{
public :
	CDungeon();
	virtual ~CDungeon();

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
	void SetObjects();

	void RoomStart();
	void RoomShop();
	void RoomChest();
	void Room1();
	void Room2();
	void Room3();
	void Room4();

public :
	void SetShop(CObject* _pObject);

public :
	virtual void SetCollision() override;

private :
	int m_iShopCount;

private :
	float m_fChangeTime;
	float m_fFadeTime;

	ULONGLONG m_iTick;
	ULONGLONG m_iFadeTick;

	bool m_bSceneChange;
	bool m_bFade;
	bool m_bPrePos;

	Vec2 m_vPrePos;

	CTexture* m_pChangeTexture;
};