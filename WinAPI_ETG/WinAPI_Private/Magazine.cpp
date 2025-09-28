#include "pch.h"
#include "Magazine.h"

#include "Main.h"
#include "ResourceManager.h"

#include "Texture.h"
#include "Player.h"
#include "Gun.h"

CMagazine::CMagazine()
	: m_iCurrMax(0)
	, m_pCurrGun(nullptr)
	, m_eMagType(MAG_TYPE::END)
{
	SetRenderType(RENDER_TYPE::RENDER_UI);

	m_vecMax.reserve(4);
	m_vecCurrMax.reserve(4);
}

CMagazine::~CMagazine()
{
	Release();
}

void CMagazine::Init()
{
	SetPos({ CMain::Get()->GetResolution().x - 120.f, CMain::Get()->GetResolution().y - 100.f });

	float fWidth = (float)CResourceManager::Get()->FindTexture(L"Font_Smaller")->GetHeight();
	float fHeight = (float)CResourceManager::Get()->FindTexture(L"Font_Smaller")->GetHeight();

	SetScale({ fWidth, fHeight });

	SetUIType(UI_TYPE::MAGAZINE);
}

void CMagazine::Update()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetTarget());

	if (pPlayer->GetCurrGun())
	{
		CGun* pGun = pPlayer->GetCurrGun();

		m_eMagType = pGun->GetMagType();

		if (m_eMagType == MAG_TYPE::LIMITED)
		{
			if (pGun != m_pCurrGun)
			{
				m_pCurrGun = pGun;
				MaxUpdate();

				SetPos({ CMain::Get()->GetResolution().x - 70.f, CMain::Get()->GetResolution().y - 140.f });

				float fWidth = (float)CResourceManager::Get()->FindTexture(L"Font_Smaller")->GetHeight();
				float fHeight = (float)CResourceManager::Get()->FindTexture(L"Font_Smaller")->GetHeight();

				SetScale({ fWidth, fHeight });
			}

			if (m_iCurrMax != pGun->GetCurrMax())
				CurrMaxUpdate();
		}
		else if (m_eMagType == MAG_TYPE::LIMITLESS)
		{
			if (pGun != m_pCurrGun)
			{
				m_pCurrGun = pGun;

				SetPos({ CMain::Get()->GetResolution().x - 90.f, CMain::Get()->GetResolution().y - 140.f });

				float fWidth = (float)CResourceManager::Get()->FindTexture(L"Font_Infinite")->GetWidth();
				float fHeight = (float)CResourceManager::Get()->FindTexture(L"Font_Infinite")->GetHeight();

				SetScale({ fWidth, fHeight});
			}
		}
	}
}

void CMagazine::LateUpdate()
{
	__super::LateUpdate();
}

void CMagazine::Render(HDC _hDC)
{
	if (!GetShow()) return;

	if (m_pCurrGun)
	{
		if (m_eMagType == MAG_TYPE::LIMITLESS)
		{
			CTexture* pTexture = CResourceManager::Get()->FindTexture(L"Font_Infinite");

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
				RGB(0, 0, 0)
			);
		}
		else if (m_eMagType == MAG_TYPE::LIMITED)
		{
			int iCount = 0;

			CTexture* pTexture = CResourceManager::Get()->FindTexture(L"Font_Smaller");
			for(int i = m_vecMax.size() - 1; i >= 0; i--)
			{
				GdiTransparentBlt
				(
					_hDC,
					(int)(GetPos().fX - GetScale().fY / 2.f - iCount * (GetScale().fY - 3.f)),
					(int)(GetPos().fY - GetScale().fY / 2.f),
					(int)(GetScale().fY),
					(int)(GetScale().fY),
					pTexture->GetHDC(),
					(int)(GetScale().fY * (9 - m_vecMax[i])),
					0,
					(int)(GetScale().fY),
					(int)(GetScale().fY),
					RGB(0, 0, 0)
				);

				iCount++;
			}

			pTexture = CResourceManager::Get()->FindTexture(L"Font_Slash");

			float fWidth = (float)CResourceManager::Get()->FindTexture(L"Font_Slash")->GetWidth();
			float fHeight = (float)CResourceManager::Get()->FindTexture(L"Font_Slash")->GetHeight();

			GdiTransparentBlt
			(
				_hDC,
				(int)(GetPos().fX - fWidth / 2.f - iCount * (GetScale().fY - 3.f)),
				(int)(GetPos().fY - fHeight / 2.f),
				(int)fWidth,
				(int)fHeight,
				pTexture->GetHDC(),
				0, 0,
				(int)fWidth,
				(int)fHeight,
				RGB(0, 0, 0)
			);

			iCount++;

			pTexture = CResourceManager::Get()->FindTexture(L"Font_Smaller");
			for(int i = m_vecCurrMax.size() - 1; i >= 0; i--)
			{
				GdiTransparentBlt
				(
					_hDC,
					(int)(GetPos().fX - GetScale().fY / 2.f - iCount * (GetScale().fY - 3.f)),
					(int)(GetPos().fY - GetScale().fY / 2.f),
					(int)(GetScale().fY),
					(int)(GetScale().fY),
					pTexture->GetHDC(),
					(int)(GetScale().fY * (9 - m_vecCurrMax[i])),
					0,
					(int)(GetScale().fY),
					(int)(GetScale().fY),
					RGB(0, 0, 0)
				);

				iCount++;
			}
		}
	}

	__super::Render(_hDC);
}

void CMagazine::Release()
{
}

void CMagazine::MaxUpdate()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetTarget());

	CGun* pGun = pPlayer->GetCurrGun();

	int iMax = pGun->GetMax();
	int iDigit = 0;

	m_vecMax.clear();

	iDigit = iMax / 1000;
	if (iDigit != 0) m_vecMax.push_back(iDigit);

	iDigit = (iMax % 1000) / 100;
	if (iDigit != 0 || (iDigit == 0 && !m_vecMax.empty())) m_vecMax.push_back(iDigit);

	iDigit = (iMax % 100) / 10;
	if (iDigit != 0 || (iDigit == 0 && !m_vecMax.empty())) m_vecMax.push_back(iDigit);

	iDigit = iMax % 10;

	m_vecMax.push_back(iDigit);
}

void CMagazine::CurrMaxUpdate()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetTarget());

	CGun* pGun = pPlayer->GetCurrGun();

	m_iCurrMax = pGun->GetCurrMax();
	int iDigit = 0;

	m_vecCurrMax.clear();

	iDigit = m_iCurrMax / 1000;
	if (iDigit != 0) m_vecCurrMax.push_back(iDigit);

	iDigit = (m_iCurrMax % 1000) / 100;
	if (iDigit != 0 || (iDigit == 0 && !m_vecCurrMax.empty())) m_vecCurrMax.push_back(iDigit);

	iDigit = (m_iCurrMax % 100) / 10;
	if (iDigit != 0 || (iDigit == 0 && !m_vecCurrMax.empty())) m_vecCurrMax.push_back(iDigit);

	iDigit = m_iCurrMax % 10;

	m_vecCurrMax.push_back(iDigit);
}