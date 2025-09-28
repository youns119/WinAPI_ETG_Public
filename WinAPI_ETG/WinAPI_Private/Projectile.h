#pragma once

#include "Object.h"

#include "ProjectileType.h"

class CTexture;

class CProjectile : public CObject
{
public :
	CProjectile();
	virtual ~CProjectile();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	float GetSpeed() const { return m_fSpeed; }
	float GetKnock() const { return m_fKnock; }
	float GetDamage() const { return m_fDamage; }
	float GetDelay() const { return m_fDelay; }
	float GetRange() const { return m_fRange; }
	float GetScatter() const { return m_fScatter; }
	ULONGLONG GetTick() const { return m_iTick; }
	PROJECTILE_TYPE GetProjectileType() const { return m_eProjectileType; }
	CTexture* GetTexture() const { return m_pTexture; }

	void SetSpeed(const float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetKnock(const float _fKnock) { m_fKnock = _fKnock; }
	void SetDamage(const float _fDamage) { m_fDamage = _fDamage; }
	void SetDelay(const float _fDelay) { m_fDelay = _fDelay; }
	void SetRange(const float _fRange) { m_fRange = _fRange; }
	void SetScatter(const float _fScatter) { m_fScatter = _fScatter; }
	void SetTick(const ULONGLONG _iTick) { m_iTick = _iTick; }
	void SetProjectileType(const PROJECTILE_TYPE _eProjectileType) { m_eProjectileType = _eProjectileType; }
	void SetTexture(CTexture* _pTexture) { m_pTexture = _pTexture; }
	void SetTexturePlg(CTexture* _pTexturePlg) { m_pTexturePlg = _pTexturePlg; }
	void SetTextureReset(CTexture* _pTextureReset) { m_pTextureReset = _pTextureReset; }

public :
	void RadianToScatter();
	virtual void ChooseTexture();

public :
	void CreateEffect();

public :
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	float m_fSpeed;
	float m_fKnock;
	float m_fDamage;
	float m_fDelay;
	float m_fRange;
	float m_fScatter;

	ULONGLONG m_iTick;

	PROJECTILE_TYPE m_eProjectileType;

private :
	POINT m_tPoint[3];

private :
	CTexture* m_pTexture;
	CTexture* m_pTexturePlg;
	CTexture* m_pTextureReset;
};