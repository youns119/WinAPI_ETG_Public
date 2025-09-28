#include "pch.h"
#include "Projectile_ReflectGun.h"

#include "ResourceManager.h"
#include "Camera.h"

#include "Texture.h"
#include "Collider.h"
#include "Physics.h"
#include "Gun.h"
#include "Table.h"
#include "Chest.h"
#include "Barrel.h"
#include "Func.h"

CProjectile_ReflectGun::CProjectile_ReflectGun()
{
	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CProjectile_ReflectGun::CProjectile_ReflectGun(CGun& pGun)
{
	SetSpeed(pGun.GetSpeed());
	SetKnock(pGun.GetKnock());
	SetDamage(pGun.GetDamage());
	SetDelay(pGun.GetDelay());
	SetRange(pGun.GetRange());
	SetScatter(pGun.GetScatter());

	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CProjectile_ReflectGun::~CProjectile_ReflectGun()
{
	Release();
}

void CProjectile_ReflectGun::Init()
{
	SetName(L"Projectile_ReflectGun");

	SetProjectileType(PROJECTILE_TYPE::REFLECTGUN);

	ChooseTexture();

	SetMass(1);
	SetFriction(0.f);
	SetMaxVelocity(3000.f);

	__super::Init();
}

void CProjectile_ReflectGun::Update()
{
	__super::Update();
}

void CProjectile_ReflectGun::LateUpdate()
{
	__super::LateUpdate();
}

void CProjectile_ReflectGun::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CProjectile_ReflectGun::Release()
{
}

void CProjectile_ReflectGun::ChooseTexture()
{
	switch (GetObjectType())
	{
	case OBJECT_TYPE::PROJECTILE_PLAYER:
		SetTexture(CResourceManager::Get()->FindTexture(L"Projectile_ReflectGun"));
		break;
	case OBJECT_TYPE::PROJECTILE_ENEMY:
		SetTexture(CResourceManager::Get()->FindTexture(L"Projectile_Enemy"));
		break;
	default:
		break;
	}
}

void CProjectile_ReflectGun::OnCollision(CCollider& _pOther)
{
}

void CProjectile_ReflectGun::OnCollisionEnter(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::WALL)
	{
		float fWidth = fabsf(GetCollider()->GetFinalPos().fX - _pOther.GetFinalPos().fX);
		float fHeight = fabsf(GetCollider()->GetFinalPos().fY - _pOther.GetFinalPos().fY);

		float fRadiusX = (GetCollider()->GetScale().fX + _pOther.GetScale().fX) * 0.5f;
		float fRadiusY = (GetCollider()->GetScale().fY + _pOther.GetScale().fY) * 0.5f;

		fWidth = fRadiusX - fWidth;
		fHeight = fRadiusY - fHeight;

		if (fWidth > fHeight)
		{
			GetPhysics()->SetVelocity({ GetPhysics()->GetVelocity().fX, -GetPhysics()->GetVelocity().fY });
		}
		else
		{
			GetPhysics()->SetVelocity({ -GetPhysics()->GetVelocity().fX, GetPhysics()->GetVelocity().fY });
		}

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

void CProjectile_ReflectGun::OnCollisionExit(CCollider& _pOther)
{
}