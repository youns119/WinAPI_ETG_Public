#include "pch.h"
#include "Spawn.h"

#include "SceneManager.h"
#include "SoundManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"
#include "BulletKin.h"
#include "ShotGunKin.h"
#include "SpawnEffect.h"

CSpawn::CSpawn()
	: m_fStartTime(0.f)
	, m_fSpawnTime(0.f)
	, m_iTick(0)
	, m_bStarted(false)
	, m_bSpawned(false)
	, m_eEnemyType(ENEMY_TYPE::END)
{
	SetObjectType(OBJECT_TYPE::SPAWN);
	SetRenderType(RENDER_TYPE::RENDER_UI);
}

CSpawn::CSpawn(ENEMY_TYPE _eEnemyType, Vec2 _vPos)
	: m_fStartTime(0.f)
	, m_fSpawnTime(0.f)
	, m_iTick(0)
	, m_bStarted(false)
	, m_bSpawned(false)
	, m_eEnemyType(_eEnemyType)
{
	SetObjectType(OBJECT_TYPE::SPAWN);
	SetRenderType(RENDER_TYPE::RENDER_UI);

	SetPos(_vPos);
	SetVolume(.07f);

	m_fSpawnTime = 1.f;
	m_iTick = GetTickCount64();
}

CSpawn::~CSpawn()
{
	Release();
}

void CSpawn::Init()
{
}

void CSpawn::Update()
{
}

void CSpawn::LateUpdate()
{
	__super::LateUpdate();

	if (!m_bStarted && m_fStartTime * 1000.f < GetTickCount64() - m_iTick)
	{
		CreateEffect();

		m_iTick = GetTickCount64();
		m_bStarted = true;
	}

	if (m_bStarted && m_fSpawnTime * 1000.f < GetTickCount64() - m_iTick)
	{
		if (!m_bSpawned)
		{
			SpawnEnemy();

			m_bSpawned = true;
			DeleteObjectEvent(this);
		}
	}
}

void CSpawn::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CSpawn::Release()
{
}

void CSpawn::CreateEffect()
{
	CSpawnEffect* pSpawnEffect = new CSpawnEffect;
	pSpawnEffect->Init();
	pSpawnEffect->SetPos(GetPos());

	CreateObjectEvent(pSpawnEffect, OBJECT_TYPE::EFFECT);
}

void CSpawn::SpawnEnemy()
{
	CEnemy* pEnemy = nullptr;

	switch (m_eEnemyType)
	{
	case ENEMY_TYPE::BULLETKIN :
	{
		pEnemy = new CBulletKin;

		break;
	}
	case ENEMY_TYPE::SHOTGUNKIN:
	{
		pEnemy = new CShotGunKin;

		break;
	}
	default :
		break;
	}

	pEnemy->SetPos(GetPos());
	pEnemy->SetTarget(CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::PLAYER)[0]);
	pEnemy->Init();

	CSoundManager::Get()->PlaySound(L"Enemy_Spawn.wav", CHANNELID::SOUND_ENEMY, GetVolume());

	CreateObjectEvent(pEnemy, OBJECT_TYPE::ENEMY);
}