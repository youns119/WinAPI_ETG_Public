#include "pch.h"
#include "Enemy.h"

#include "SceneManager.h"
#include "Timer.h"
#include "SoundManager.h"

#include "Func.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Physics.h"
#include "Gun.h"
#include "Projectile.h"
#include "Item_Coin.h"
#include "Item_Fear.h"
#include "Item_HP.h"
#include "Item_Key.h"
#include "Blow.h"
#include "Projectile_HomingGun.h"

CEnemy::CEnemy()
	: m_bItemCreated(false)
	, m_bDespawn(false)
	, m_fRange(0.f)
	, m_fSpeed(0.f)
	, m_fDespawnTime(0.f)
	, m_fHitTime(0.f)
	, m_iHitTick(0)
	, m_eEnemyType(ENEMY_TYPE::END)
	, m_pTarget(nullptr)
{
	SetObjectType(OBJECT_TYPE::ENEMY);
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CEnemy::~CEnemy()
{
	Release();
}

void CEnemy::Init()
{
	CreateCollider();
	CreateAnimator();
	CreatePhysics();

	GetCollider()->SetScale(GetScale());
	GetCollider()->SetShow(false);

	GetPhysics()->SetMass(GetMass());
	GetPhysics()->SetFriction(GetFriction());
	GetPhysics()->SetMaxVelocity(GetMaxVelocity());

	SetRenderScale(GetScale());

	m_fDespawnTime = 3.f;
	m_fHitTime = 1.f;
}

void CEnemy::Update()
{
	if (GetCharState() == CHAR_STATE::DEAD)
	{
		if (!m_bItemCreated)
		{
			int iRand = rand() % 20;

			CItem* pItem = nullptr;

			if (iRand >= 0 && iRand < 12)
				pItem = new CItem_Coin;
			else if (iRand >= 12 && iRand < 16)
				pItem = new CItem_Fear;
			else if (iRand >= 16 && iRand < 19)
				pItem = new CItem_HP(1);
			else
				pItem = new CItem_Key;

			pItem->SetPos(GetPos());
			pItem->Init();

			CreateObjectEvent(pItem, OBJECT_TYPE::ITEM);

			m_bItemCreated = true;
		}
		else return;
	}

	if (GetTarget())
	{
		Vec2 vDist = GetTarget()->GetPos() - GetPos();
		Vec2 vNorm = vDist.Normalize();
		float fDist = vDist.Length();
		float fRadian = vDist.DirToRadian();

		SetRadian(fRadian);

		if (GetCharState() == CHAR_STATE::HIT)
		{
			if (GetCurrHP() <= 0)
			{
				switch (GetEnemyType())
				{
				case ENEMY_TYPE::BULLETKIN :
					CSoundManager::Get()->PlaySound(L"BulletKin_Death.wav", CHANNELID::SOUND_ENEMY, GetVolume());
					break;
				case ENEMY_TYPE::SHOTGUNKIN:
					CSoundManager::Get()->PlaySound(L"BulletKin_Death.wav", CHANNELID::SOUND_ENEMY, GetVolume());
					break;
				}

				SetCharState(CHAR_STATE::DEATH);
				DeleteObjectEvent(GetCurrGun());
			}

			return;
		}
		else if (GetCharState() == CHAR_STATE::DEATH)
			return;
		else if (GetCharState() == CHAR_STATE::DEAD)
			return;

		if (fDist <= m_fRange)
		{
			SetCharState(CHAR_STATE::IDLE);
			Attack();
		}
		else
		{
			SetCharState(CHAR_STATE::WALK);
			SetPos(GetPos() + vNorm * m_fSpeed * CTimer::Get()->GetDelta());
		}
	}

	PointDir();
}

void CEnemy::LateUpdate()
{
	__super::LateUpdate();

	if (m_bDespawn && DelayCheck(m_fDespawnTime * 1000))
		DeleteObjectEvent(this);

	if (GetCharState() == CHAR_STATE::DEAD) return;

	if (GetCharState() == CHAR_STATE::HIT)
	{
		if (GetAnimator()->GetCurrAnim()->GetFinish())
			SetCharState(CHAR_STATE::IDLE);
	}

	if (GetCharState() == CHAR_STATE::DEATH)
	{
		if (GetAnimator()->GetCurrAnim()->GetFinish() && !m_bDespawn)
		{
			SetCharState(CHAR_STATE::DEAD);
			CSceneManager::Get()->ChangeRender(this, GetObjectType(), RENDER_TYPE::RENDER_TILE_PREV);

			SetTick(GetTickCount64());

			m_bDespawn = true;
		}
	}

	Motion();
}

void CEnemy::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CEnemy::Release()
{
}

void CEnemy::Attack()
{
}

bool CEnemy::HitTimeCheck(float _fTime)
{
	if (_fTime < GetTickCount64() - m_iHitTick)
	{
		m_iHitTick = GetTickCount64();

		return true;
	}

	return false;
}

void CEnemy::OnCollision(CCollider& _pOther)
{
	CObject::OnCollision(_pOther);

	CObject* pOther = _pOther.GetOwner();

	if (pOther->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		if (GetCharState() == CHAR_STATE::DEAD ||
			GetCharState() == CHAR_STATE::DEATH)
			return;

		Vec2 vDist = pOther->GetPos() - GetPos();

		GetPhysics()->AddVelocity(-vDist.Normalize() * GetMaxVelocity());
	}
}

void CEnemy::OnCollisionEnter(CCollider& _pOther)
{
	//CObject::OnCollisionEnter(_pOther);

	CObject* pOther = _pOther.GetOwner();

	if (pOther->GetObjectType() == OBJECT_TYPE::PROJECTILE_PLAYER)
	{
		if (GetCharState() == CHAR_STATE::DEAD ||
			GetCharState() == CHAR_STATE::DEATH) 
			return;

		CProjectile* pProjectile = dynamic_cast<CProjectile*>(pOther);

		if (pProjectile->GetProjectileType() == PROJECTILE_TYPE::HOMINGGUN)
			dynamic_cast<CProjectile_HomingGun*>(pProjectile)->Detonate();

		float fDamage = pProjectile->GetDamage();
		Vec2 vDist = pOther->GetPhysics()->GetVelocity().Normalize();

		SetCurrHP(GetCurrHP() - (int)fDamage);
		GetPhysics()->AddVelocity(vDist * pProjectile->GetKnock() * 25.f);

		if (GetCurrHP() > 0 && HitTimeCheck(m_fHitTime * 1000.f))
		{
			switch (GetEnemyType())
			{
			case ENEMY_TYPE::BULLETKIN :
				CSoundManager::Get()->PlaySound(L"BulletKin_Hit.wav", CHANNELID::SOUND_ENEMY, GetVolume());
				break;
			case ENEMY_TYPE::SHOTGUNKIN :
				CSoundManager::Get()->PlaySound(L"BulletKin_Hit.wav", CHANNELID::SOUND_ENEMY, GetVolume());
				break;
			}
		}

		SetCharState(CHAR_STATE::HIT);

		DeleteObjectEvent(pOther);
		pProjectile->CreateEffect();
	}
	else if (pOther->GetObjectType() == OBJECT_TYPE::BLOW)
	{
		if (GetCharState() == CHAR_STATE::DEAD ||
			GetCharState() == CHAR_STATE::DEATH)
			return;

		CBlow* pBlow = dynamic_cast<CBlow*>(pOther);
		float fDamage = pBlow->GetDamage();

		SetCurrHP(GetCurrHP() - (int)fDamage);
		SetCharState(CHAR_STATE::HIT);

		if (GetCurrHP() > 0 && HitTimeCheck(m_fHitTime * 1000.f))
		{
			switch (GetEnemyType())
			{
			case ENEMY_TYPE::BULLETKIN:
				CSoundManager::Get()->PlaySound(L"BulletKin_Hit.wav", CHANNELID::SOUND_ENEMY, GetVolume());
				break;
			case ENEMY_TYPE::SHOTGUNKIN:
				CSoundManager::Get()->PlaySound(L"BulletKin_Hit.wav", CHANNELID::SOUND_ENEMY, GetVolume());
				break;
			}
		}
	}
}

void CEnemy::OnCollisionExit(CCollider& _pOther)
{
}