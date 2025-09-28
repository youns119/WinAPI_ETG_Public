#pragma once

#include "Item.h"

class CTexture;

class CItem_HP : public CItem
{
public :
	CItem_HP();
	CItem_HP(int _iType);
	virtual ~CItem_HP();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	int m_iType;
};