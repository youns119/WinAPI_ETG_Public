#pragma once

#include "Item.h"

class CTexture;

class CItem_Coin : public CItem
{
public :
	CItem_Coin();
	virtual ~CItem_Coin();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	void SetFollow(bool _bFollow) { m_bFollow = _bFollow; }

public :
	bool FollowCheck();
	void Follow();

public:
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	bool m_bFollow;
	bool m_bCollide;
};