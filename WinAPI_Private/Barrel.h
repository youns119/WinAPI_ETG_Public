#pragma once

#include "Interact.h"

#include "BarrelState.h"

class CBarrel : public CInteract
{
public :
	CBarrel();
	virtual ~CBarrel();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public:
	BARREL_STATE GetBarrelState() const { return m_eBarrelState; }

	void SetChestState(const BARREL_STATE _eBarrelState) { m_eBarrelState = _eBarrelState; }

public :
	virtual void Motion() override;
	virtual void CreateAnimation() override;
	virtual void CreateEffect() override;

public :
	virtual void OnCollision(CCollider& _pOther);
	virtual void OnCollisionEnter(CCollider& _pOther);
	virtual void OnCollisionExit(CCollider& _pOther);

private :
	BARREL_STATE m_eBarrelState;
};