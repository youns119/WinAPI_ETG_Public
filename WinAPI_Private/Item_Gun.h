#pragma once

#include "Item.h"

#include "GunType.h"

class CTexture;

class CItem_Gun : public CItem
{
public :
	CItem_Gun();
	CItem_Gun(GUN_TYPE _eGunType);
	virtual ~CItem_Gun();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	GUN_TYPE GetGunType() const { return m_eGunType; }

	void SetGunType(const GUN_TYPE _eGunType) { m_eGunType = _eGunType; }

public:
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	GUN_TYPE m_eGunType;
};