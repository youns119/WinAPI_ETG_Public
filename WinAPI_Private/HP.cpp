#include "pch.h"
#include "HP.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"

#include "Texture.h"
#include "Player.h"

CHP::CHP()
	: m_iHP(0)
	, m_iHPFull(0)
	, m_iHPHalf(0)
	, m_iHPEmpty(0)
	, m_fDistance(0.f)
{
	SetRenderType(RENDER_TYPE::RENDER_UI);
}

CHP::~CHP()
{
	Release();
}

void CHP::Init()
{
	SetPos({ 50.f, 50.f });

	float fWidth = (float)CResourceManager::Get()->FindTexture(L"HP_Full")->GetWidth();
	float fHeight = (float)CResourceManager::Get()->FindTexture(L"HP_Full")->GetHeight();

	SetScale({ fWidth, fHeight });
	
	SetUIType(UI_TYPE::HP);

	m_fDistance = 50.f;
}

void CHP::Update()
{
	if (m_iHP != dynamic_cast<CPlayer*>(GetTarget())->GetCurrHP()) 
		HPUpdate();
}

void CHP::LateUpdate()
{
	__super::LateUpdate();
}

void CHP::Render(HDC _hDC)
{
	if (!GetShow()) return;

	int iDraw = 0;
	int iCount = 0;
	CTexture* pTexture = nullptr;

	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			iDraw = m_iHPFull;
			pTexture = CResourceManager::Get()->FindTexture(L"HP_Full");
		}
		else if (i == 1)
		{
			iDraw = m_iHPHalf;
			pTexture = CResourceManager::Get()->FindTexture(L"HP_Half");
		}
		else
		{
			iDraw = m_iHPEmpty;
			pTexture = CResourceManager::Get()->FindTexture(L"HP_Empty");
		}

		for (int j = 0; j < iDraw; j++)
		{
			GdiTransparentBlt
			(
				_hDC,
				(int)(GetPos().fX - GetScale().fX / 2.f + m_fDistance * iCount),
				(int)(GetPos().fY - GetScale().fY / 2.f),
				(int)(GetScale().fX),
				(int)(GetScale().fY),
				pTexture->GetHDC(),
				0, 0,
				(int)(GetScale().fX),
				(int)(GetScale().fY),
				RGB(255, 255, 255)
			);

			iCount++;
		}
	}

	__super::Render(_hDC);
}

void CHP::Release()
{
}

void CHP::HPUpdate()
{
	int iMaxHP = dynamic_cast<CPlayer*>(GetTarget())->GetMaxHP();
	m_iHP = dynamic_cast<CPlayer*>(GetTarget())->GetCurrHP();

	m_iHPFull = m_iHP / 2;
	m_iHPHalf = m_iHP % 2;
	m_iHPEmpty = iMaxHP / 2 - m_iHPFull - m_iHPHalf;
}