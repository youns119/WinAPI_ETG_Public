#include "pch.h"
#include "ReflectGun.h"

#include "ResourceManager.h"

int CReflectGun::m_iSoundCount = 0;

CReflectGun::CReflectGun()
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CReflectGun::~CReflectGun()
{
	Release();
}

void CReflectGun::Init()
{
	SetName(L"ReflectGun");

	SetVolume(.1f);

	SetGunType(GUN_TYPE::REFLECTGUN);
	//SetTriggerType(TRIGGER_TYPE::SEMIAUTO);
	SetTriggerType(TRIGGER_TYPE::AUTO);
	//SetMagType(MAG_TYPE::LIMITLESS);
	SetMagType(MAG_TYPE::LIMITED);

	SetMag(30);
	SetCurrMag(GetMag());
	SetMax(600);
	SetCurrMax(GetMax());

	SetReload(1.f);
	SetSpeed(30.f);
	SetKnock(5.f);
	SetDamage(4.f);
	SetDelay(0.1f);
	SetRange(20.f);
	SetScatter(6.f);

	__super::Init();
}

void CReflectGun::Update()
{
	__super::Update();
}

void CReflectGun::LateUpdate()
{
	__super::LateUpdate();
}

void CReflectGun::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CReflectGun::Release()
{
}

void CReflectGun::PreRender()
{
	SetTextureR(CResourceManager::Get()->FindTexture(L"ReflectGun_R"));
	SetTextureL(CResourceManager::Get()->FindTexture(L"ReflectGun_L"));
	SetTexturePlg(CResourceManager::Get()->FindTexture(L"ReflectGun_Plg"));
	SetTextureReset(CResourceManager::Get()->FindTexture(L"ReflectGun_Reset"));

	SetTexture(CResourceManager::Get()->FindTexture(L"ReflectGun_R"));
}