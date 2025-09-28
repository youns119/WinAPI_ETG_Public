#include "pch.h"
#include "Bullet.h"

#include "Main.h"
#include "ResourceManager.h"

#include "Texture.h"
#include "Player.h"
#include "Gun.h"

#include "GunType.h"

CBullet::CBullet()
	: m_iMaxCount(0)
	, m_iCurrCount(0)
	, m_fDistance(0.f)
{
	SetRenderType(RENDER_TYPE::RENDER_UI);
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Init()
{
	SetPos({ CMain::Get()->GetResolution().x - 10.f, CMain::Get()->GetResolution().y - 50.f });

	float fWidth = (float)CResourceManager::Get()->FindTexture(L"Bullet_Shell")->GetWidth();
	float fHeight = (float)CResourceManager::Get()->FindTexture(L"Bullet_Shell")->GetHeight();

	SetScale({ fWidth, fHeight });

	SetUIType(UI_TYPE::BULLET);

	m_fDistance = GetScale().fY - 2.f;
}

void CBullet::Update()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetTarget());

	CGun* pGun = pPlayer->GetCurrGun();

	if (pGun)
	{
		m_iMaxCount = pGun->GetMag();
		m_iCurrCount = pGun->GetCurrMag();
	}
}

void CBullet::LateUpdate()
{
	__super::LateUpdate();
}

void CBullet::Render(HDC _hDC)
{
	if (!GetShow()) return;

	int iCount = 0;

	CTexture* pTexture = CResourceManager::Get()->FindTexture(L"Bullet_Shell");
	GdiTransparentBlt
	(
		_hDC,
		(int)(GetPos().fX - GetScale().fX / 2.f),
		(int)(GetPos().fY - GetScale().fY / 2.f),
		(int)(GetScale().fX / 2.f),
		(int)(GetScale().fY),
		pTexture->GetHDC(),
		0, 0,
		(int)(GetScale().fX / 2.f),
		(int)(GetScale().fY),
		RGB(255, 0, 255)
	);

	iCount++;

	if (dynamic_cast<CPlayer*>(GetTarget())->GetCurrGun())
	{
		pTexture = ChooseTexture();

		for (int i = 0; i < m_iCurrCount; i++)
		{
			if (GetPos().fY - GetScale().fY / 2.f - m_fDistance * iCount <= 0.f)
				break;

			GdiTransparentBlt
			(
				_hDC,
				(int)(GetPos().fX - GetScale().fX / 2.f),
				(int)(GetPos().fY - GetScale().fY / 2.f - m_fDistance * iCount),
				(int)(GetScale().fX / 2.f),
				(int)(GetScale().fY),
				pTexture->GetHDC(),
				(int)(GetScale().fX / 2.f), 0,
				(int)(GetScale().fX / 2.f),
				(int)(GetScale().fY),
				RGB(255, 0, 255)
			);

			iCount++;
		}

		for (int i = m_iCurrCount; i < m_iMaxCount; i++)
		{
			if (GetPos().fY - GetScale().fY / 2.f - m_fDistance * iCount <= 0.f)
				break;

			GdiTransparentBlt
			(
				_hDC,
				(int)(GetPos().fX - GetScale().fX / 2.f),
				(int)(GetPos().fY - GetScale().fY / 2.f - m_fDistance * iCount),
				(int)(GetScale().fX / 2.f),
				(int)(GetScale().fY),
				pTexture->GetHDC(),
				0, 0,
				(int)(GetScale().fX / 2.f),
				(int)(GetScale().fY),
				RGB(255, 0, 255)
			);

			iCount++;
		}
	}

	pTexture = CResourceManager::Get()->FindTexture(L"Bullet_Shell");

	if (GetPos().fY - GetScale().fY / 2.f - m_fDistance * iCount > 0.f)
	{
		GdiTransparentBlt
		(
			_hDC,
			(int)(GetPos().fX - GetScale().fX / 2.f),
			(int)(GetPos().fY - GetScale().fY / 2.f - m_fDistance * iCount),
			(int)(GetScale().fX / 2.f),
			(int)(GetScale().fY),
			pTexture->GetHDC(),
			(int)(GetScale().fX / 2.f), 0,
			(int)(GetScale().fX / 2.f),
			(int)(GetScale().fY),
			RGB(255, 0, 255)
		);
	}

	__super::Render(_hDC);
}

void CBullet::Release()
{
}

CTexture* CBullet::ChooseTexture()
{
	CTexture* pTexture = nullptr;
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetTarget());
	CGun* pGun = pPlayer->GetCurrGun();

	switch (pGun->GetGunType())
	{
	case GUN_TYPE::REVOLVER :
		pTexture = CResourceManager::Get()->FindTexture(L"Revolver_Bullet");
		break;
	case GUN_TYPE::SHOTGUN :
		pTexture = CResourceManager::Get()->FindTexture(L"ShotGun_Bullet");
		break;
	case GUN_TYPE::MACHINEGUN:
		pTexture = CResourceManager::Get()->FindTexture(L"MachineGun_Bullet");
		break;
	case GUN_TYPE::PIERCEGUN:
		pTexture = CResourceManager::Get()->FindTexture(L"MachineGun_Bullet");
		break;
	case GUN_TYPE::REFLECTGUN:
		pTexture = CResourceManager::Get()->FindTexture(L"ReflectGun_Bullet");
		break;
	case GUN_TYPE::HOMINGGUN:
		pTexture = CResourceManager::Get()->FindTexture(L"HomingGun_Bullet");
		break;
	}

	return pTexture;
}