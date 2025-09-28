#pragma once

#include "Object.h"

class CBlow : public CObject
{
public :
	CBlow();
	virtual ~CBlow();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	float GetDamage() const { return m_fDamage; }
	float GetLifeTime() const { return m_fLifeTime; }

	void SetDamage(const float _fDamage) { m_fDamage = _fDamage; }
	void SetLifeTime(const float _fLifeTime) { m_fLifeTime = _fLifeTime; }

public :
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	float m_fDamage;
	float m_fLifeTime;

	ULONGLONG m_iTick;
};