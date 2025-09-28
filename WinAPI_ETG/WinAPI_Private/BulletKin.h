#pragma once

#include "Enemy.h"

class CBulletKin : public CEnemy
{
public :
	CBulletKin();
	virtual ~CBulletKin();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	virtual void PointDir() override;
	virtual void Attack() override;

public :
	virtual void Motion() override;
	virtual void CreateAnimation() override;

public :
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;
};