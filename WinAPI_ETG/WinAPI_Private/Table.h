#pragma once

#include "Interact.h"

#include "TableState.h"
#include "TableDir.h"

class CTable : public CInteract
{
public :
	CTable();
	virtual ~CTable();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	TABLE_STATE GetTableState() const { return m_eTableState; }
	TABLE_DIR GetTableDir() const { return m_eTableDir; }
	bool GetFly() const { return m_bFly; }
	float GetDamage() const { return m_fDamage; }

	void SetTableState(const TABLE_STATE _eTableState) { m_eTableState = _eTableState; }
	void SetTableDir(const TABLE_DIR _eTableDir) { m_eTableDir = _eTableDir; }
	void SetFly(const bool _bFly) { m_bFly = _bFly; }
	void SetDamage(const float _fDamage) { m_fDamage = _fDamage; }

public :
	virtual void Motion() override;
	virtual void CreateAnimation() override;
	virtual void CreateEffect() override;

public:
	virtual void OnCollision(CCollider& _pOther);
	virtual void OnCollisionEnter(CCollider& _pOther);
	virtual void OnCollisionExit(CCollider& _pOther);

private :
	TABLE_STATE m_eTableState;
	TABLE_DIR m_eTableDir;

private :
	bool m_bFly;
	
	float m_fDamage;
};