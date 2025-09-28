#include "pch.h"
#include "Item_Gun.h"

#include "ResourceManager.h"
#include "Camera.h"

#include "Texture.h"
#include "Collider.h"

CItem_Gun::CItem_Gun()
	: m_eGunType(GUN_TYPE::END)
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CItem_Gun::CItem_Gun(GUN_TYPE _eGunType)
	: m_eGunType(_eGunType)
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CItem_Gun::~CItem_Gun()
{
	Release();
}

void CItem_Gun::Init()
{
	SetItemType(ITEM_TYPE::GUN);

	SetVolume(0.15);

	switch (m_eGunType)
	{
	case GUN_TYPE::REVOLVER :
		SetTexture(CResourceManager::Get()->FindTexture(L"Revolver_R"));
		SetName(L"Item_Revolver");
		break;
	case GUN_TYPE::SHOTGUN:
		SetTexture(CResourceManager::Get()->FindTexture(L"ShotGun_R"));
		SetName(L"Item_ShotGun");
		break;
	case GUN_TYPE::MACHINEGUN:
		SetTexture(CResourceManager::Get()->FindTexture(L"MachineGun_R"));
		SetName(L"Item_MachineGun");
		break;
	case GUN_TYPE::PIERCEGUN:
		SetTexture(CResourceManager::Get()->FindTexture(L"Revolver_R"));
		SetName(L"Item_PierceGun");
		break;
	case GUN_TYPE::REFLECTGUN:
		SetTexture(CResourceManager::Get()->FindTexture(L"ReflectGun_R"));
		SetName(L"Item_ReflectGun");
		break;
	case GUN_TYPE::HOMINGGUN:
		SetTexture(CResourceManager::Get()->FindTexture(L"HomingGun_R"));
		SetName(L"Item_HomingGun");
		break;
	default :
		break;
	}

	int iWidth = GetTexture()->GetWidth();
	int iHeight = GetTexture()->GetHeight();

	SetScale({ iWidth, iHeight });

	SetMass(1.f);
	SetFriction(5000.f);
	SetMaxVelocity(1000.f);

	__super::Init();
}

void CItem_Gun::Update()
{
}

void CItem_Gun::LateUpdate()
{
	__super::LateUpdate();
}

void CItem_Gun::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CItem_Gun::Release()
{
}

void CItem_Gun::OnCollision(CCollider& _pOther)
{
}

void CItem_Gun::OnCollisionEnter(CCollider& _pOther)
{
	CItem::OnCollisionEnter(_pOther);

	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		switch (m_eGunType)
		{
		case GUN_TYPE::REVOLVER:
			SetTexture(CResourceManager::Get()->FindTexture(L"Revolver_R_Alt"));
			break;
		case GUN_TYPE::SHOTGUN:
			SetTexture(CResourceManager::Get()->FindTexture(L"ShotGun_R_Alt"));
			break;
		case GUN_TYPE::MACHINEGUN:
			SetTexture(CResourceManager::Get()->FindTexture(L"MachineGun_R_Alt"));
			break;
		case GUN_TYPE::PIERCEGUN:
			SetTexture(CResourceManager::Get()->FindTexture(L"Revolver_R_Alt"));
			break;
		case GUN_TYPE::REFLECTGUN:
			SetTexture(CResourceManager::Get()->FindTexture(L"ReflectGun_R_Alt"));
			break;
		case GUN_TYPE::HOMINGGUN:
			SetTexture(CResourceManager::Get()->FindTexture(L"HomingGun_R_Alt"));
			break;
		default:
			break;
		}

		int iWidth = GetTexture()->GetWidth();
		int iHeight = GetTexture()->GetHeight();

		SetScale({ iWidth, iHeight });

		GetCollider()->SetScale({ GetScale().fX, GetScale().fY });
	}
}

void CItem_Gun::OnCollisionExit(CCollider& _pOther)
{
	CItem::OnCollisionExit(_pOther);

	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		switch (m_eGunType)
		{
		case GUN_TYPE::REVOLVER:
			SetTexture(CResourceManager::Get()->FindTexture(L"Revolver_R"));
			break;
		case GUN_TYPE::SHOTGUN:
			SetTexture(CResourceManager::Get()->FindTexture(L"ShotGun_R"));
			break;
		case GUN_TYPE::MACHINEGUN:
			SetTexture(CResourceManager::Get()->FindTexture(L"MachineGun_R"));
			break;
		case GUN_TYPE::PIERCEGUN:
			SetTexture(CResourceManager::Get()->FindTexture(L"Revolver_R"));
			break;
		case GUN_TYPE::REFLECTGUN:
			SetTexture(CResourceManager::Get()->FindTexture(L"ReflectGun_R_Alt"));
			break;
		case GUN_TYPE::HOMINGGUN:
			SetTexture(CResourceManager::Get()->FindTexture(L"HomingGun_R"));
			break;
		default:
			break;
		}

		int iWidth = GetTexture()->GetWidth();
		int iHeight = GetTexture()->GetHeight();

		SetScale({ iWidth, iHeight });

		GetCollider()->SetScale({ GetScale().fX, GetScale().fY });
	}
}