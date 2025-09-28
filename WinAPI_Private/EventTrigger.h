#pragma once

#include "Object.h"

#include "EventTriggerType.h"

class CEventTrigger : public CObject
{
public :
	CEventTrigger();
	virtual ~CEventTrigger();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	EVENT_TRIGGER_TYPE GetEventTriggerType() const { return m_eEventTriggerType; }

	void SetEventTriggerType(const EVENT_TRIGGER_TYPE _eEventTriggerType) { m_eEventTriggerType = _eEventTriggerType; }

public :
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;
	
private :
	EVENT_TRIGGER_TYPE m_eEventTriggerType;
};