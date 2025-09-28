#include "pch.h"
#include "Projectile_Revolver.h"

#include "ResourceManager.h"
#include "Camera.h"

#include "Texture.h"
#include "Collider.h"
#include "Physics.h"
#include "Gun.h"

CProjectile_Revolver::CProjectile_Revolver()
{
	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CProjectile_Revolver::CProjectile_Revolver(CGun& pGun)
{
	SetSpeed(pGun.GetSpeed());
	SetKnock(pGun.GetKnock());
	SetDamage(pGun.GetDamage());
	SetDelay(pGun.GetDelay());
	SetRange(pGun.GetRange());
	SetScatter(pGun.GetScatter());

	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CProjectile_Revolver::~CProjectile_Revolver()
{
	Release();
}

void CProjectile_Revolver::Init()
{
	SetName(L"Projectile_Revolver");

	SetProjectileType(PROJECTILE_TYPE::REVOLVER);

	ChooseTexture();

	SetMass(1);
	SetFriction(0.f);
	SetMaxVelocity(3000.f);

	__super::Init();
}

void CProjectile_Revolver::Update()
{
	__super::Update();
}

void CProjectile_Revolver::LateUpdate()
{
	__super::LateUpdate();
}

void CProjectile_Revolver::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CProjectile_Revolver::Release()
{
}

void CProjectile_Revolver::ChooseTexture()
{
	switch (GetObjectType())
	{
	case OBJECT_TYPE::PROJECTILE_PLAYER :
		SetTexture(CResourceManager::Get()->FindTexture(L"Projectile_Revolver"));
		break;
	case OBJECT_TYPE::PROJECTILE_ENEMY :
		SetTexture(CResourceManager::Get()->FindTexture(L"Projectile_Enemy"));
		break;
	default :
		break;
	}
}

void CProjectile_Revolver::OnCollision(CCollider& _pOther)
{
}

void CProjectile_Revolver::OnCollisionEnter(CCollider& _pOther)
{
	__super::OnCollisionEnter(_pOther);
}

void CProjectile_Revolver::OnCollisionExit(CCollider& _pOther)
{
}