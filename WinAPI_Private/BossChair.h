#pragma once

#include "Object.h"

#include "ChairState.h"

class CBossChair : public CObject
{
public :
	CBossChair();
	virtual ~CBossChair();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	CHAIR_STATE GetChairState() const { return m_eChairState; }
	CObject* GetTarget() const { return m_pTarget; }

	void SetChairState(const CHAIR_STATE _eChairState) { m_eChairState = _eChairState; }
	void SetTarget(CObject* _pTarget) { m_pTarget = _pTarget; }

public :
	virtual void Motion();
	virtual void CreateAnimation() override;

private :
	CHAIR_STATE m_eChairState;

private :
	CObject* m_pTarget;
};