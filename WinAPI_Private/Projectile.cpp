#include "pch.h"
#include "Projectile.h"

#include "Camera.h"

#include "Collider.h"
#include "Physics.h"
#include "Texture.h"
#include "Func.h"
#include "RevolverEffect.h"
#include "ShotGunEffect.h"
#include "MachineGunEffect.h"
#include "ReflectGunEffect.h"
#include "HomingGunEffect.h"
#include "Table.h"
#include "Chest.h"
#include "Barrel.h"

CProjectile::CProjectile()
	: m_fSpeed(0.f)
	, m_fKnock(0.f)
	, m_fDamage(0.f)
	, m_fDelay(0.f)
	, m_fRange(0.f)
	, m_fScatter(0.f)
	, m_iTick(0)
	, m_eProjectileType(PROJECTILE_TYPE::END)
	, m_tPoint{}
	, m_pTexture(nullptr)
	, m_pTexturePlg(nullptr)
	, m_pTextureReset(nullptr)
{
}

CProjectile::~CProjectile()
{
	Release();
}

void CProjectile::Init()
{
	CreateCollider();
	CreatePhysics();

	GetCollider()->SetScale(GetScale());
	GetCollider()->SetShow(false);

	float fWidth = (float)GetTexture()->GetWidth();
	float fHeight = (float)GetTexture()->GetHeight();

	SetScale({ fWidth, fHeight });
	SetRenderScale(GetScale());

	SetTick(GetTickCount64());

	RadianToScatter();

	GetPhysics()->SetMass(GetMass());
	GetPhysics()->SetFriction(GetFriction());
	GetPhysics()->SetMaxVelocity(GetMaxVelocity());

	Vec2 vVelocity;
	vVelocity.fX = GetSpeed() * 50.f * cosf(GetRadian());
	vVelocity.fY = GetSpeed() * 50.f * sinf(GetRadian());

	GetPhysics()->SetVelocity(vVelocity);
}

void CProjectile::Update()
{
	if (m_eProjectileType == PROJECTILE_TYPE::MACHINEGUN ||
		m_eProjectileType == PROJECTILE_TYPE::HOMINGGUN)
	{
		float fDegree = GetRadian() * 180 / PI;
		float fDiagonal = sqrtf((GetScale().fX / 2.f) * (GetScale().fX / 2.f) + (GetScale().fY / 2.f) * (GetScale().fY / 2.f));

		m_tPoint[0].x = LONG((GetScale().fX / 2.f) + fDiagonal * cos((-fDegree + 135.f) * (PI / 180.f)));
		m_tPoint[0].y = LONG((GetScale().fY / 2.f) - fDiagonal * sin((-fDegree + 135.f) * (PI / 180.f)));

		m_tPoint[1].x = LONG((GetScale().fX / 2.f) + fDiagonal * cos((-fDegree + 45.f) * (PI / 180.f)));
		m_tPoint[1].y = LONG((GetScale().fY / 2.f) - fDiagonal * sin((-fDegree + 45.f) * (PI / 180.f)));

		m_tPoint[2].x = LONG((GetScale().fX / 2.f) + fDiagonal * cos((-fDegree + 225.f) * (PI / 180.f)));
		m_tPoint[2].y = LONG((GetScale().fY / 2.f) - fDiagonal * sin((-fDegree + 225.f) * (PI / 180.f)));
	}
}

void CProjectile::LateUpdate()
{
	__super::LateUpdate();

	if (GetTickCount64() - m_iTick > m_fRange * 100.f)
	{
		DeleteObjectEvent(this);
		CreateEffect();
	}
}

void CProjectile::Render(HDC _hDC)
{
	Vec2 vRenderPos = CCamera::Get()->GetRenderPos(GetPos());

	if (m_eProjectileType == PROJECTILE_TYPE::MACHINEGUN ||
		m_eProjectileType == PROJECTILE_TYPE::HOMINGGUN)
	{
		PlgBlt
		(
			m_pTexturePlg->GetHDC(),
			m_tPoint,
			m_pTexture->GetHDC(),
			(int)0.f, (int)0.f,
			(int)GetScale().fX,
			(int)GetScale().fY,
			NULL, NULL, NULL
		);

		GdiTransparentBlt
		(
			_hDC,
			int(vRenderPos.fX - GetScale().fX / 2.f),
			int(vRenderPos.fY - GetScale().fY / 2.f),
			(int)(m_pTexturePlg->GetWidth()),
			(int)(m_pTexturePlg->GetHeight()),
			m_pTexturePlg->GetHDC(),
			0, 0,
			(int)(m_pTexturePlg->GetWidth()),
			(int)(m_pTexturePlg->GetHeight()),
			RGB(255, 0, 255)
		);

		BitBlt
		(
			m_pTexturePlg->GetHDC(),
			0, 0,
			(int)(m_pTexturePlg->GetWidth()),
			(int)(m_pTexturePlg->GetHeight()),
			m_pTextureReset->GetHDC(),
			0, 0,
			SRCCOPY
		);
	}
	else
	{
		GdiTransparentBlt
		(
			_hDC,
			int(vRenderPos.fX - GetScale().fX / 2.f),
			int(vRenderPos.fY - GetScale().fY / 2.f),
			(int)(m_pTexture->GetWidth()),
			(int)(m_pTexture->GetHeight()),
			m_pTexture->GetHDC(),
			0, 0,
			(int)(m_pTexture->GetWidth()),
			(int)(m_pTexture->GetHeight()),
			RGB(255, 0, 255)
		);
	}


	__super::Render(_hDC);
}

void CProjectile::Release()
{
}

void CProjectile::RadianToScatter()
{
	int fAlpha = rand() % (int)(m_fScatter + 1.f) - (int)(m_fScatter / 2.f);
	float fDegree = GetRadian() * 180.f / PI;

	float fFinal = fDegree + (float)fAlpha;

	if (fFinal < -180.f)
		fFinal = 180.f - abs(fFinal + 180.f);
	else if (fFinal > 180.f)
		fFinal = -180.f + abs(fFinal - 180.f);

	fFinal = fFinal * PI / 180.f;

	SetRadian(fFinal);
}

void CProjectile::ChooseTexture()
{
}

void CProjectile::CreateEffect()
{
	CEffect* pBulletEffect = nullptr;

	switch (m_eProjectileType)
	{
	case PROJECTILE_TYPE::REVOLVER:
		pBulletEffect = new CRevolverEffect();
		break;
	case PROJECTILE_TYPE::SHOTGUN:
		pBulletEffect = new CShotGunEffect();
		break;
	case PROJECTILE_TYPE::MACHINEGUN:
		pBulletEffect = new CMachineGunEffect();
		break;
	case PROJECTILE_TYPE::PIERCEGUN:
		pBulletEffect = new CShotGunEffect();
		break;
	case PROJECTILE_TYPE::REFLECTGUN:
		pBulletEffect = new CReflectGunEffect();
		break;
	case PROJECTILE_TYPE::HOMINGGUN:
		pBulletEffect = new CHomingGunEffect();
		break;
	}

	pBulletEffect->Init();
	pBulletEffect->SetPos(GetPos());
	CreateObjectEvent(pBulletEffect, OBJECT_TYPE::EFFECT);
}

void CProjectile::OnCollision(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::WALL)
	{
		DeleteObjectEvent(this);
		CreateEffect();
	}

	if (pOwner->GetObjectType() == OBJECT_TYPE::INTERACT)
	{
		INTERACT_TYPE eInteractType = dynamic_cast<CInteract*>(pOwner)->GetInteractType();

		if (eInteractType == INTERACT_TYPE::TABLE)
		{
			CTable* pTable = dynamic_cast<CTable*>(pOwner);

			if (pTable->GetTableState() == TABLE_STATE::FLIPPED || 
				pTable->GetTableState() == TABLE_STATE::FLIP)
			{
				pTable->SetHP(pTable->GetHP() - (int)GetDamage());

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

				DeleteObjectEvent(this);
				CreateEffect();
			}
		}
	}
}

void CProjectile::OnCollisionEnter(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::WALL)
	{
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

				DeleteObjectEvent(this);
				CreateEffect();
			}
		}
	}
}

void CProjectile::OnCollisionExit(CCollider& _pOther)
{
}