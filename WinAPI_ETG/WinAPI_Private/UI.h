#pragma once

#include "Object.h"

#include "UIType.h"

class CObject;

class CUI : public CObject
{
public:
	CUI();
	virtual ~CUI();

public:
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	CObject* GetTarget() const { return m_pTarget; }
	bool GetShow() const { return m_bShow; }
	UI_TYPE GetUIType() const { return m_eUIType; }

	void SetTarget(CObject& _pTarget) { m_pTarget = &_pTarget; }
	void SetShow(const bool _bShow) { m_bShow = _bShow; }
	void SetUIType(const UI_TYPE _eUIType) { m_eUIType = _eUIType; }

private :
	CObject* m_pTarget;
	bool m_bShow;

	UI_TYPE m_eUIType;
};