#include "pch.h"
#include "Fear.h"

#include "ResourceManager.h"

#include "Player.h"
#include "Texture.h"

CFear::CFear()
	: m_iFear(0)
	, m_fDistance(0.f)
{
	SetRenderType(RENDER_TYPE::RENDER_UI);
}

CFear::~CFear()
{
	Release();
}

void CFear::Init()
{
	SetPos({ 50.f, 100.f });

	float fWidth = (float)CResourceManager::Get()->FindTexture(L"Fear")->GetWidth();
	float fHeight = (float)CResourceManager::Get()->FindTexture(L"Fear")->GetHeight();

	SetScale({ fWidth, fHeight });

	SetUIType(UI_TYPE::FEAR);

	m_fDistance = 50.f;
}

void CFear::Update()
{
	m_iFear = dynamic_cast<CPlayer*>(GetTarget())->GetFearCount();
}

void CFear::LateUpdate()
{
	__super::LateUpdate();
}

void CFear::Render(HDC _hDC)
{
	if (!GetShow()) return;

	CTexture* pTexture = CResourceManager::Get()->FindTexture(L"Fear");

	for (int i = 0; i < m_iFear; i++)
	{
		GdiTransparentBlt
		(
			_hDC,
			(int)(GetPos().fX - GetScale().fX / 2.f + m_fDistance * i),
			(int)(GetPos().fY - GetScale().fY / 2.f),
			(int)(GetScale().fX),
			(int)(GetScale().fY),
			pTexture->GetHDC(),
			0, 0,
			(int)(GetScale().fX),
			(int)(GetScale().fY),
			RGB(255, 255, 255)
		);
	}
}

void CFear::Release()
{
}