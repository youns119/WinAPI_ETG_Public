#include "pch.h"
#include "PierceGun.h"

#include "ResourceManager.h"

CPierceGun::CPierceGun()
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CPierceGun::~CPierceGun()
{
	Release();
}

void CPierceGun::Init()
{
	SetName(L"MachineGun");

	SetGunType(GUN_TYPE::MACHINEGUN);
	//SetTriggerType(TRIGGER_TYPE::SEMIAUTO);
	SetTriggerType(TRIGGER_TYPE::AUTO);
	//SetMagType(MAG_TYPE::LIMITLESS);
	SetMagType(MAG_TYPE::LIMITED);

	SetMag(999);
	SetCurrMag(GetMag());
	SetMax(999);
	SetCurrMax(GetMax());

	SetReload(0.3f);
	SetSpeed(40.f);
	SetKnock(3.f);
	SetDamage(2.5f);
	SetDelay(0.05f);
	SetRange(14.f);
	SetScatter(8.f);

	__super::Init();
}

void CPierceGun::Update()
{
	__super::Update();
}

void CPierceGun::LateUpdate()
{
	__super::LateUpdate();
}

void CPierceGun::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CPierceGun::Release()
{
}

void CPierceGun::PreRender()
{
	SetTextureR(CResourceManager::Get()->FindTexture(L"Revolver_R"));
	SetTextureL(CResourceManager::Get()->FindTexture(L"Revolver_L"));
	SetTexturePlg(CResourceManager::Get()->FindTexture(L"Revolver_Plg"));
	SetTextureReset(CResourceManager::Get()->FindTexture(L"Revolver_Reset"));

	SetTexture(CResourceManager::Get()->FindTexture(L"Revolver_R"));
}