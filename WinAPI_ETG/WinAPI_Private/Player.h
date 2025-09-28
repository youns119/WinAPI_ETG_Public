#pragma once

#include "Character.h"

class CGun;
class CInteract;
class CItem;

class CPlayer : public CCharacter
{
public :
	CPlayer();
	virtual ~CPlayer();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	bool GetInvincible() const { return m_bInvincible; }
	bool GetReload() const { return m_bReload; }
	Vec2 GetCursorDir() const { return m_vCursorDir; }
	int GetFearCount() const { return m_iFearCount; }
	int GetKeyCount() const { return m_iKeyCount; }
	int GetCoinCount() const { return m_iCoinCount; }
	int GetCurrGunIndex() const { return m_iCurrGunIndex; }
	CInteract* GetCurrInteract() const { return m_pCurrInteract; }
	CItem* GetCurrItem() const { return m_pCurrItem; }

	void SetInvincible(const bool _bInvincible) { m_bInvincible = _bInvincible; }
	void SetReload(const bool _bReload) { m_bReload = _bReload; }
	void SetCurrInteract(CInteract* _pCurrInteract) { m_pCurrInteract = _pCurrInteract; }
	void SetCoinCount(const int _iCoin) { m_iCoinCount = _iCoin; }
	void SetKeyCount(const int _iKey) { m_iKeyCount = _iKey; }
	void SetFearCount(const int _iFear) { m_iFearCount = _iFear; }

public :
	void Input();
	virtual void PointDir() override;
	void DodgeDir(Vec2 _vDir);

public :
	bool WalkTickCheck(float _fTime);

public :
	virtual void Motion() override;
	virtual void CreateAnimation() override;
	virtual CPlayer* Clone() override;

public:
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	bool m_bDodge;
	bool m_bInvincible;
	bool m_bReload;
	bool m_bHit;
	bool m_bShow;
	bool m_bFlicker;
	bool m_bFear;

	float m_fDodgeVelocity;
	float m_fHitTime;
	float m_fFlickerTime;
	float m_fWalkTime;
	float m_fFearTime;
	
	ULONGLONG m_iHitTick;
	ULONGLONG m_iFlickerTick;
	ULONGLONG m_iWalkTick;
	ULONGLONG m_iFearTick;

	Vec2 m_vCursorDir;

private :
	int m_iFearCount;
	int m_iKeyCount;
	int m_iCoinCount;
	int m_iWalkCount;

private :
	vector<CGun*> m_vecGuns;
	CItem* m_pCurrItem;

	int m_iCurrGunIndex;

private :
	CInteract* m_pCurrInteract;
};