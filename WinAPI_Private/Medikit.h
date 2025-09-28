#pragma once

#include "Item.h"

class CMedikit : public CItem
{
public :
	CMedikit();
	virtual ~CMedikit();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	bool GetUsed() const { return m_bUsed; }

	void SetTarget(CObject* _pObject) { m_pTarget = _pObject; }
	void SetUsed(const bool _bUsed) { m_bUsed = _bUsed; }

public :
	void Use();

public :
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	CObject* m_pTarget;

private :
	bool m_bUsed;
};