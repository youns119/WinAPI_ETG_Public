#include "pch.h"
#include "ShotGun.h"

#include "ResourceManager.h"

int CShotGun::m_iSoundCount = 0;

CShotGun::CShotGun()
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CShotGun::~CShotGun()
{
	Release();
}

void CShotGun::Init()
{
	SetName(L"ShotGun");

	SetVolume(0.1f);

	SetGunType(GUN_TYPE::SHOTGUN);
	SetTriggerType(TRIGGER_TYPE::SEMIAUTO);
	//SetTriggerType(TRIGGER_TYPE::AUTO);
	//SetMagType(MAG_TYPE::LIMITLESS);
	SetMagType(MAG_TYPE::LIMITED);

	SetMag(6);
	SetCurrMag(GetMag());
	SetMax(150);
	SetCurrMax(GetMax());

	SetReload(1.2f);
	SetSpeed(26.f);
	SetKnock(30.f);
	SetDamage(6.f);
	SetDelay(0.5f);
	SetRange(8.f);
	SetScatter(30.f);

	__super::Init();
}

void CShotGun::Update()
{
	__super::Update();
}

void CShotGun::LateUpdate()
{
	__super::LateUpdate();
}

void CShotGun::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CShotGun::Release()
{
}

void CShotGun::PreRender()
{
	SetTextureR(CResourceManager::Get()->FindTexture(L"ShotGun_R"));
	SetTextureL(CResourceManager::Get()->FindTexture(L"ShotGun_L"));
	SetTexturePlg(CResourceManager::Get()->FindTexture(L"ShotGun_Plg"));
	SetTextureReset(CResourceManager::Get()->FindTexture(L"ShotGun_Reset"));

	SetTexture(CResourceManager::Get()->FindTexture(L"Revolver_R"));
}