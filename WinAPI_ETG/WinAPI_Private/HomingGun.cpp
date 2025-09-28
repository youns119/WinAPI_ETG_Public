#include "pch.h"
#include "HomingGun.h"

#include "ResourceManager.h"

CHomingGun::CHomingGun()
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CHomingGun::~CHomingGun()
{
	Release();
}

void CHomingGun::Init()
{
	SetName(L"ReflectGun");

	SetVolume(.2f);

	SetGunType(GUN_TYPE::HOMINGGUN);
	SetTriggerType(TRIGGER_TYPE::SEMIAUTO);
	//SetTriggerType(TRIGGER_TYPE::AUTO);
	//SetMagType(MAG_TYPE::LIMITLESS);
	SetMagType(MAG_TYPE::LIMITED);

	SetMag(5);
	SetCurrMag(GetMag());
	SetMax(80);
	SetCurrMax(GetMax());

	SetReload(2.f);
	SetSpeed(15.f);
	SetKnock(10.f);
	SetDamage(20.f);
	SetDelay(1.5f);
	SetRange(40.f);
	SetScatter(1.f);

	__super::Init();
}

void CHomingGun::Update()
{
	__super::Update();
}

void CHomingGun::LateUpdate()
{
	__super::LateUpdate();
}

void CHomingGun::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CHomingGun::Release()
{
}

void CHomingGun::PreRender()
{
	SetTextureR(CResourceManager::Get()->FindTexture(L"HomingGun_R"));
	SetTextureL(CResourceManager::Get()->FindTexture(L"HomingGun_L"));
	SetTexturePlg(CResourceManager::Get()->FindTexture(L"HomingGun_Plg"));
	SetTextureReset(CResourceManager::Get()->FindTexture(L"HomingGun_Reset"));

	SetTexture(CResourceManager::Get()->FindTexture(L"HomingGun_R"));
}