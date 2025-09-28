#pragma once

#include "Object.h"

#include "GunType.h"
#include "TriggerType.h"
#include "MagType.h"

class CTexture;

class CGun : public CObject
{
public :
	CGun();
	virtual ~CGun();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	GUN_TYPE GetGunType() const { return m_eGunType; }
	TRIGGER_TYPE GetTriggerType() const { return m_eTriggerType; }
	MAG_TYPE GetMagType() const { return m_eMagType; }
	int GetMag() const { return m_iMag; }
	int GetCurrMag() const { return m_iCurrMag; }
	int GetMax() const { return m_iMax; }
	int GetCurrMax() const { return m_iCurrMax; }
	float GetReload() const { return m_fReload; }
	float GetSpeed() const { return m_fSpeed; }
	float GetKnock() const { return m_fKnock; }
	float GetDamage() const { return m_fDamage; }
	float GetDelay() const { return m_fDelay; }
	float GetRange() const { return m_fRange; }
	float GetScatter() const { return m_fScatter; }
	CObject* GetTarget() const { return m_pTarget; }
	CTexture* GetTexture() const { return m_pTexture; }
	Vec2 GetEnd() const { return m_vEnd; }

	void SetGunType(const GUN_TYPE _eGunType) { m_eGunType = _eGunType; }
	void SetTriggerType(const TRIGGER_TYPE _eTriggerType) { m_eTriggerType = _eTriggerType; }
	void SetMagType(const MAG_TYPE _eMagType) { m_eMagType = _eMagType; }
	void SetMag(const int _iMag) { m_iMag = _iMag; }
	void SetCurrMag(const int _iCurrMag) { m_iCurrMag = _iCurrMag; }
	void SetMax(const int _iMax) { m_iMax = _iMax; }
	void SetCurrMax(const int _iCurrMax) { m_iCurrMax = _iCurrMax; }
	void SetReload(const float _fReload) { m_fReload = _fReload; }
	void SetSpeed(const float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetKnock(const float _fKnock) { m_fKnock = _fKnock; }
	void SetDamage(const float _fDamage) { m_fDamage = _fDamage; }
	void SetDelay(const float _fDelay) { m_fDelay = _fDelay; }
	void SetRange(const float _fRange) { m_fRange = _fRange; }
	void SetScatter(const float _fScatter) { m_fScatter = _fScatter; }
	void SetShow(const bool _bShow) { m_bShow = _bShow; }
	void SetTarget(CObject& _pTarget) { m_pTarget = &_pTarget; }
	void SetTexture(CTexture* _pTexture) { m_pTexture = _pTexture; }
	void SetTextureR(CTexture* _pTextureR) { m_pTextureR = _pTextureR; }
	void SetTextureL(CTexture* _pTextureL) { m_pTextureL = _pTextureL; }
	void SetTexturePlg(CTexture* _pTexturePlg) { m_pTexturePlg = _pTexturePlg; }
	void SetTextureReset(CTexture* _pTextureReset) { m_pTextureReset = _pTextureReset; }

public :
	virtual void PreRender() {};

private :
	GUN_TYPE m_eGunType;
	TRIGGER_TYPE m_eTriggerType;
	MAG_TYPE m_eMagType;

	int m_iMag;
	int m_iCurrMag;
	int m_iMax;
	int m_iCurrMax;

	float m_fReload;
	float m_fSpeed;
	float m_fKnock;
	float m_fDamage;
	float m_fDelay;
	float m_fRange;
	float m_fScatter;

	bool m_bShow;

	POINT m_tPoint[3];
	Vec2 m_vEnd;

private :
	CObject* m_pTarget;

	CTexture* m_pTexture;
	CTexture* m_pTextureR;
	CTexture* m_pTextureL;
	CTexture* m_pTexturePlg;
	CTexture* m_pTextureReset;
};