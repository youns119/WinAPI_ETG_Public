#pragma once

#include "Object.h"

#include "EnemyType.h"

class CSpawn : public CObject
{
public :
	CSpawn();
	CSpawn(ENEMY_TYPE _eEnemyType, Vec2 _vPos);
	virtual ~CSpawn();

public :
	virtual void Init()				override;
	virtual void Update()			override;
	virtual void LateUpdate()		override;
	virtual void Render(HDC _hDC)	override;
	virtual void Release()			override;

public :
	void SetTimer(float _fTime) { m_fStartTime = _fTime; }


public :
	void CreateEffect();
	void SpawnEnemy();

private :
	float m_fStartTime;
	float m_fSpawnTime;
	ULONGLONG m_iTick;

	bool m_bStarted;
	bool m_bSpawned;

private :
	ENEMY_TYPE m_eEnemyType;
};