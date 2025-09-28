#pragma once

#include "Object.h"

#include "InteractType.h"

struct ColOffset
{
	Vec2 vPos;
	Vec2 vScale;
};

class CInteract : public CObject
{
public :
	CInteract();
	virtual ~CInteract();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	int GetHP() const { return m_iHP; }
	INTERACT_TYPE GetInteractType() const { return m_eInteractType; }
	ColOffset GetColOffset() const { return m_tColOffset; }

	void SetHP(const int _iHP) { m_iHP = _iHP; }
	void SetInteractType(const INTERACT_TYPE _eInteractType) { m_eInteractType = _eInteractType; }
	void SetColOffset(const Vec2 _vPos, const Vec2 _vScale)
	{
		m_tColOffset.vPos = _vPos;
		m_tColOffset.vScale = _vScale;
	}

public :
	virtual void Motion() {};
	virtual void CreateEffect() {};

public :
	virtual bool isOffsetCollision(CObject* _pOther);

public :
	virtual void OnCollision(CCollider& _pOther);
	virtual void OnCollisionEnter(CCollider& _pOther);
	virtual void OnCollisionExit(CCollider& _pOther);

private :
	int m_iHP;

	INTERACT_TYPE m_eInteractType;

private :
	ColOffset m_tColOffset;
};