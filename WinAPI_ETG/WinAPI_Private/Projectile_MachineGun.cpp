#include "pch.h"
#include "Projectile_MachineGun.h"

#include "ResourceManager.h"
#include "Camera.h"

#include "Texture.h"
#include "Collider.h"
#include "Physics.h"
#include "Gun.h"

CProjectile_MachineGun::CProjectile_MachineGun()
{
	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CProjectile_MachineGun::CProjectile_MachineGun(CGun& pGun)
{
	SetSpeed(pGun.GetSpeed());
	SetKnock(pGun.GetKnock());
	SetDamage(pGun.GetDamage());
	SetDelay(pGun.GetDelay());
	SetRange(pGun.GetRange());
	SetScatter(pGun.GetScatter());

	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CProjectile_MachineGun::~CProjectile_MachineGun()
{
	Release();
}

void CProjectile_MachineGun::Init()
{
	SetName(L"Projectile_MachineGun");

	SetProjectileType(PROJECTILE_TYPE::MACHINEGUN);

	ChooseTexture();

	SetMass(1);
	SetFriction(0.f);
	SetMaxVelocity(3000.f);

	__super::Init();
}

void CProjectile_MachineGun::Update()
{
	__super::Update();
}

void CProjectile_MachineGun::LateUpdate()
{
	__super::LateUpdate();
}

void CProjectile_MachineGun::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CProjectile_MachineGun::Release()
{
}

void CProjectile_MachineGun::ChooseTexture()
{
	switch (GetObjectType())
	{
	case OBJECT_TYPE::PROJECTILE_PLAYER:
		SetTexture(CResourceManager::Get()->FindTexture(L"Projectile_MachineGun"));
		break;
	case OBJECT_TYPE::PROJECTILE_ENEMY:
		SetTexture(CResourceManager::Get()->FindTexture(L"Projectile_Enemy"));
		break;
	default:
		break;
	}

	SetTexturePlg(CResourceManager::Get()->FindTexture(L"Projectile_MachineGun_Plg"));
	SetTextureReset(CResourceManager::Get()->FindTexture(L"Projectile_MachineGun_Reset"));
}

void CProjectile_MachineGun::OnCollision(CCollider& _pOther)
{
}

void CProjectile_MachineGun::OnCollisionEnter(CCollider& _pOther)
{
	__super::OnCollisionEnter(_pOther);
}

void CProjectile_MachineGun::OnCollisionExit(CCollider& _pOther)
{
}