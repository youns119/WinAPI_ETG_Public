#include "pch.h"
#include "GunBox.h"

#include "Main.h"
#include "ResourceManager.h"

#include "Texture.h"
#include "Player.h"
#include "Gun.h"

#include "GunType.h"

CGunBox::CGunBox()
	: m_pGunTexture(nullptr)
{
	SetRenderType(RENDER_TYPE::RENDER_UI);
}

CGunBox::~CGunBox()
{
	Release();
}

void CGunBox::Init()
{
	SetPos({ CMain::Get()->GetResolution().x - 120.f, CMain::Get()->GetResolution().y - 80.f});

	float fWidth = (float)CResourceManager::Get()->FindTexture(L"GunBox")->GetWidth();
	float fHeight = (float)CResourceManager::Get()->FindTexture(L"GunBox")->GetHeight();

	SetScale({ fWidth, fHeight });

	SetUIType(UI_TYPE::GUNBOX);
}

void CGunBox::Update()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetTarget());

	if (pPlayer->GetCurrGun())
	{
		GUN_TYPE eGunType = dynamic_cast<CPlayer*>(GetTarget())->GetCurrGun()->GetGunType();

		switch (eGunType)
		{
		case GUN_TYPE::REVOLVER:
			m_pGunTexture = CResourceManager::Get()->FindTexture(L"Revolver_R");
			break;
		case GUN_TYPE::SHOTGUN:
			m_pGunTexture = CResourceManager::Get()->FindTexture(L"ShotGun_R");
			break;
		case GUN_TYPE::MACHINEGUN:
			m_pGunTexture = CResourceManager::Get()->FindTexture(L"MachineGun_R");
			break;
		case GUN_TYPE::PIERCEGUN:
			m_pGunTexture = CResourceManager::Get()->FindTexture(L"Revolver_R");
			break;
		case GUN_TYPE::REFLECTGUN:
			m_pGunTexture = CResourceManager::Get()->FindTexture(L"ReflectGun_R");
			break;
		case GUN_TYPE::HOMINGGUN:
			m_pGunTexture = CResourceManager::Get()->FindTexture(L"HomingGun_R");
			break;
		default:
			break;
		}
	}
}

void CGunBox::LateUpdate()
{
	__super::LateUpdate();
}

void CGunBox::Render(HDC _hDC)
{
	if (!GetShow()) return;

	CTexture* pTexture = CResourceManager::Get()->FindTexture(L"GunBox");

	GdiTransparentBlt
	(
		_hDC,
		(int)(GetPos().fX - GetScale().fX / 2.f),
		(int)(GetPos().fY - GetScale().fY / 2.f),
		(int)(GetScale().fX),
		(int)(GetScale().fY),
		pTexture->GetHDC(),
		0, 0,
		(int)(GetScale().fX),
		(int)(GetScale().fY),
		RGB(255, 255, 255)
	);

	if (m_pGunTexture)
	{
		GdiTransparentBlt
		(
			_hDC,
			(int)(GetPos().fX - m_pGunTexture->GetWidth() / 2.f),
			(int)(GetPos().fY - m_pGunTexture->GetHeight() / 2.f),
			(int)(m_pGunTexture->GetWidth()),
			(int)(m_pGunTexture->GetHeight()),
			m_pGunTexture->GetHDC(),
			0, 0,
			(int)(m_pGunTexture->GetWidth()),
			(int)(m_pGunTexture->GetHeight()),
			RGB(255, 0, 255)
		);
	}

	__super::Render(_hDC);
}

void CGunBox::Release()
{
}