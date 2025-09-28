#include "pch.h"
#include "MachineGun.h"

#include "ResourceManager.h"

int CMachineGun::m_iSoundCount = 0;

CMachineGun::CMachineGun()
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CMachineGun::~CMachineGun()
{
	Release();
}

void CMachineGun::Init()
{
	SetName(L"MachineGun");

	SetVolume(.04f);

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
	SetDamage(1.f);
	SetDelay(0.02f);
	SetRange(14.f);
	SetScatter(8.f);

	__super::Init();
}

void CMachineGun::Update()
{
	__super::Update();
}

void CMachineGun::LateUpdate()
{
	__super::LateUpdate();
}

void CMachineGun::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CMachineGun::Release()
{
}

void CMachineGun::PreRender()
{
	SetTextureR(CResourceManager::Get()->FindTexture(L"MachineGun_R"));
	SetTextureL(CResourceManager::Get()->FindTexture(L"MachineGun_L"));
	SetTexturePlg(CResourceManager::Get()->FindTexture(L"MachineGun_Plg"));
	SetTextureReset(CResourceManager::Get()->FindTexture(L"MachineGun_Reset"));

	SetTexture(CResourceManager::Get()->FindTexture(L"MachineGun_R"));
}