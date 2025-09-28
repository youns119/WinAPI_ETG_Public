#include "pch.h"
#include "Projectile_HomingGun.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SoundManager.h"

#include "Texture.h"
#include "Collider.h"
#include "Physics.h"
#include "Gun.h"
#include "Enemy.h"
#include "Func.h"
#include "Blow.h"
#include "Table.h"
#include "Barrel.h"
#include "Chest.h"
#include "HomingEffect.h"

CProjectile_HomingGun::CProjectile_HomingGun()
	: m_bHoming(false)
	, m_fHomingTime(0.f)
	, m_fEffectTime(0.f)
	, m_iHomingTick(0)
	, m_iEffectTick(0)
	, m_vTarget{}
{
	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CProjectile_HomingGun::CProjectile_HomingGun(CGun& pGun)
	: m_bHoming(false)
	, m_fHomingTime(0.f)
	, m_fEffectTime(0.f)
	, m_iHomingTick(0)
	, m_iEffectTick(0)
	, m_vTarget{}
{
	SetSpeed(pGun.GetSpeed());
	SetKnock(pGun.GetKnock());
	SetDamage(pGun.GetDamage());
	SetDelay(pGun.GetDelay());
	SetRange(pGun.GetRange());
	SetScatter(pGun.GetScatter());

	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CProjectile_HomingGun::~CProjectile_HomingGun()
{
	Release();
}

void CProjectile_HomingGun::Init()
{
	SetName(L"Projectile_HomingGun");

	SetProjectileType(PROJECTILE_TYPE::HOMINGGUN);

	ChooseTexture();

	SetMass(1);
	SetFriction(0.f);
	SetMaxVelocity(800.f);

	m_fHomingTime = 0.2f;
	m_fEffectTime = 0.05f;
	m_iHomingTick = GetTickCount64();

	__super::Init();
}

void CProjectile_HomingGun::Update()
{
	__super::Update();

	if (m_bHoming)
	{
		Vec2 vNorm{};
		float vDir = 0.f;

		vNorm = (m_vTarget - GetPos()).Normalize();

		GetPhysics()->AddVelocity(vNorm * 90.f);

		vDir = GetPhysics()->GetVelocity().DirToRadian();

		SetRadian(vDir);
	}
}

void CProjectile_HomingGun::LateUpdate()
{
	__super::LateUpdate();

	if (!m_bHoming && m_fHomingTime * 1000.f < GetTickCount64() - m_iHomingTick)
	{
		m_bHoming = true;

		float fDist = 9999.f;
		vector<CObject*>& vTarget = CSceneManager::Get()->GetGroupObjects(OBJECT_TYPE::ENEMY);

		for (int i = 0; i < vTarget.size(); i++)
			if ((vTarget[i]->GetPos() - GetPos()).Length() < fDist)
			{
				CEnemy* pEnemy = dynamic_cast<CEnemy*>(vTarget[i]);

				if (pEnemy->GetEnemyType() == ENEMY_TYPE::BULLETKIN ||
					pEnemy->GetEnemyType() == ENEMY_TYPE::SHOTGUNKIN)
				{
					if (pEnemy->GetCharState() != CHAR_STATE::DEATH &&
						pEnemy->GetCharState() != CHAR_STATE::DEAD)
						m_vTarget = vTarget[i]->GetPos();
				}
				else if(pEnemy->GetEnemyType() == ENEMY_TYPE::BULLETKING)
				{
					m_vTarget = vTarget[i]->GetPos();
				}
			}

	}

	if (m_bHoming)
	{
		if ((m_vTarget - GetPos()).Length() <= 10.f)
		{
			Detonate();

			DeleteObjectEvent(this);
		}
	}

	if (m_fEffectTime * 1000.f < GetTickCount64() - m_iEffectTick)
	{
		CObject* pEffect = new CHomingEffect();
		pEffect->Init();
		pEffect->SetPos(GetPos());

		m_iEffectTick = GetTickCount64();

		CreateObjectEvent(pEffect, pEffect->GetObjectType());
	}
}

void CProjectile_HomingGun::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CProjectile_HomingGun::Release()
{
}

void CProjectile_HomingGun::Detonate()
{
	CBlow* pBlow = new CBlow;

	pBlow->Init();
	pBlow->GetCollider()->SetScale({ 100.f, 100.f });
	pBlow->SetDamage(10.f);

	CSoundManager::Get()->PlaySound(L"HomingGun_Blast.wav", CHANNELID::SOUND_EFFECT, 1.f);

	CreateObjectEvent(pBlow, OBJECT_TYPE::BLOW);
}

void CProjectile_HomingGun::ChooseTexture()
{
	switch (GetObjectType())
	{
	case OBJECT_TYPE::PROJECTILE_PLAYER:
		SetTexture(CResourceManager::Get()->FindTexture(L"Projectile_HomingGun"));
		break;
	case OBJECT_TYPE::PROJECTILE_ENEMY:
		SetTexture(CResourceManager::Get()->FindTexture(L"Projectile_Enemy"));
		break;
	default:
		break;
	}

	SetTexturePlg(CResourceManager::Get()->FindTexture(L"Projectile_HomingGun_Plg"));
	SetTextureReset(CResourceManager::Get()->FindTexture(L"Projectile_HomingGun_Reset"));
}

void CProjectile_HomingGun::OnCollision(CCollider& _pOther)
{
}

void CProjectile_HomingGun::OnCollisionEnter(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::WALL)
	{
		Detonate();

		DeleteObjectEvent(this);
		CreateEffect();
	}

	if (pOwner->GetObjectType() == OBJECT_TYPE::INTERACT)
	{
		INTERACT_TYPE eInteractType = dynamic_cast<CInteract*>(pOwner)->GetInteractType();

		if (eInteractType == INTERACT_TYPE::TABLE)
		{
			CTable* pTable = dynamic_cast<CTable*>(pOwner);

			if (pTable->GetTableState() == TABLE_STATE::FLIPPED)
			{
				pTable->SetHP(pTable->GetHP() - (int)GetDamage());

				Detonate();

				DeleteObjectEvent(this);
				CreateEffect();
			}
		}
		else if (eInteractType == INTERACT_TYPE::CHEST)
		{
			CChest* pChest = dynamic_cast<CChest*>(pOwner);

			if (pChest->GetChestState() == CHEST_STATE::BREAK ||
				pChest->GetChestState() == CHEST_STATE::BROKEN)
				return;
			else
			{
				pChest->SetHP(pChest->GetHP() - (int)GetDamage());

				Detonate();

				DeleteObjectEvent(this);
				CreateEffect();
			}
		}
		else if (eInteractType == INTERACT_TYPE::BARREL)
		{
			CBarrel* pBarrel = dynamic_cast<CBarrel*>(pOwner);

			if (pBarrel->GetBarrelState() == BARREL_STATE::BLOW)
				return;
			else
			{
				pBarrel->SetHP(pBarrel->GetHP() - (int)GetDamage());

				Detonate();

				DeleteObjectEvent(this);
				CreateEffect();
			}
		}
	}
}

void CProjectile_HomingGun::OnCollisionExit(CCollider& _pOther)
{
}