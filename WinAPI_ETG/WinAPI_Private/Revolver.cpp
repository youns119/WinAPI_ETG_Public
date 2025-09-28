#include "pch.h"
#include "Revolver.h"

#include "ResourceManager.h"

int CRevolver::m_iSoundCount = 0;

CRevolver::CRevolver()
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CRevolver::~CRevolver()
{
	Release();
}

void CRevolver::Init()
{
	SetName(L"Revolver");
	
	SetVolume(0.1f);

	SetGunType(GUN_TYPE::REVOLVER);
	SetTriggerType(TRIGGER_TYPE::SEMIAUTO);
	//SetTriggerType(TRIGGER_TYPE::AUTO);
	SetMagType(MAG_TYPE::LIMITLESS);
	//SetMagType(MAG_TYPE::LIMITED);

	SetMag(10);
	SetCurrMag(GetMag());
	SetMax(30);
	SetCurrMax(GetMax());

	SetReload(1.2f);
	SetSpeed(16.f);
	SetKnock(10.f);
	SetDamage(8.f);
	SetDelay(0.2f);
	SetRange(16.f);
	SetScatter(7.f);

	__super::Init();
}

void CRevolver::Update()
{
	__super::Update();
}

void CRevolver::LateUpdate()
{
	__super::LateUpdate();
}

void CRevolver::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CRevolver::Release()
{
}

void CRevolver::PreRender()
{
	SetTextureR(CResourceManager::Get()->FindTexture(L"Revolver_R"));
	SetTextureL(CResourceManager::Get()->FindTexture(L"Revolver_L"));
	SetTexturePlg(CResourceManager::Get()->FindTexture(L"Revolver_Plg"));
	SetTextureReset(CResourceManager::Get()->FindTexture(L"Revolver_Reset"));

	SetTexture(CResourceManager::Get()->FindTexture(L"Revolver_R"));
}