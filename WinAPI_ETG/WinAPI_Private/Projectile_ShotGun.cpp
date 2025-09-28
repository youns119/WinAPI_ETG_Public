#include "pch.h"
#include "Projectile_ShotGun.h"

#include "ResourceManager.h"
#include "Camera.h"

#include "Texture.h"
#include "Collider.h"
#include "Physics.h"
#include "Gun.h"

CProjectile_ShotGun::CProjectile_ShotGun()
{
	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CProjectile_ShotGun::CProjectile_ShotGun(CGun& pGun)
{
	SetSpeed(pGun.GetSpeed());
	SetKnock(pGun.GetKnock());
	SetDamage(pGun.GetDamage());
	SetDelay(pGun.GetDelay());
	SetRange(pGun.GetRange());
	SetScatter(pGun.GetScatter());

	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CProjectile_ShotGun::~CProjectile_ShotGun()
{
	Release();
}

void CProjectile_ShotGun::Init()
{
	SetName(L"Projectile_ShotGun");

	SetProjectileType(PROJECTILE_TYPE::SHOTGUN);

	ChooseTexture();

	float fRange = GetRange();
	float fSpeed = GetSpeed();

	fRange = (float)(rand() % (int)(fRange * 4.f / 5.f) + fRange / 5.f);
	fSpeed = (float)(rand() % (int)(fSpeed * 2.f / 5.f) + fSpeed * 3.f / 5.f);

	SetRange(fRange);
	SetSpeed(fSpeed);

	SetMass(1);
	SetFriction(0.f);
	SetMaxVelocity(3000.f);

	__super::Init();
}

void CProjectile_ShotGun::Update()
{
	__super::Update();
}

void CProjectile_ShotGun::LateUpdate()
{
	__super::LateUpdate();
}

void CProjectile_ShotGun::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CProjectile_ShotGun::Release()
{
}

void CProjectile_ShotGun::ChooseTexture()
{
	switch (GetObjectType())
	{
	case OBJECT_TYPE::PROJECTILE_PLAYER:
		SetTexture(CResourceManager::Get()->FindTexture(L"Projectile_ShotGun"));
		break;
	case OBJECT_TYPE::PROJECTILE_ENEMY:
		SetTexture(CResourceManager::Get()->FindTexture(L"Projectile_Enemy"));
		break;
	default:
		break;
	}
}

void CProjectile_ShotGun::OnCollision(CCollider& _pOther)
{
}

void CProjectile_ShotGun::OnCollisionEnter(CCollider& _pOther)
{
	__super::OnCollisionEnter(_pOther);
}

void CProjectile_ShotGun::OnCollisionExit(CCollider& _pOther)
{
}