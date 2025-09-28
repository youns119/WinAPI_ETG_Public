#pragma once

#include "EventTrigger.h"

#include "EnemyGenType.h"

class CSpawn;

class CEnemyGen : public CEventTrigger
{
public :
	CEnemyGen();
	CEnemyGen(ENEMY_GEN_TYPE _eEnemyGenType);
	virtual ~CEnemyGen();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	bool GetSafe() const { return m_bSafe; }

public :
	void CreateEnemy1();
	void CreateEnemy2();
	void CreateEnemy3();
	void CreateEnemy4();

public :
	bool EnemyCheck();

public:
	virtual void OnCollision(CCollider& _pOther)		override;
	virtual void OnCollisionEnter(CCollider& _pOther)	override;
	virtual void OnCollisionExit(CCollider& _pOther)	override;

private :
	int m_iCount;

	bool m_bCollided;
	bool m_bGenerated;
	bool m_bSafe;

private :
	queue<CSpawn*> m_qSpawn;

private :
	ENEMY_GEN_TYPE m_eEnemyGenType;
};