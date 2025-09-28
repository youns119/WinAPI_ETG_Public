#include "pch.h"
#include "BossHP.h"

#include "ResourceManager.h"
#include "Main.h"

#include "Texture.h"
#include "BulletKing.h"

CBossHP::CBossHP()
	: m_fMaxHP(0.f)
	, m_fCurrHP(0.f)
	, m_fRatio(1.f)
{
	SetRenderType(RENDER_TYPE::RENDER_UI);
	SetUIType(UI_TYPE::BOSSHP);
}

CBossHP::~CBossHP()
{
	Release();
}

void CBossHP::Init()
{
	SetPos({ CMain::Get()->GetResolution().x / 2.f, CMain::Get()->GetResolution().y - 70.f });

	m_fMaxHP = dynamic_cast<CBulletKing*>(GetTarget())->GetMaxHP();

	SetUIType(UI_TYPE::HP);
}

void CBossHP::Update()
{
	BossHPUpdate();
}

void CBossHP::LateUpdate()
{
	__super::LateUpdate();
}

void CBossHP::Render(HDC _hDC)
{
	if (!GetShow())
		return;

	CTexture* pTexture = CResourceManager::Get()->FindTexture(L"BossHPBar");

	float fWidth = pTexture->GetWidth();
	float fHeight = pTexture->GetHeight();

	GdiTransparentBlt
	(
		_hDC,
		(int)(GetPos().fX - fWidth / 2.f),
		(int)(GetPos().fY - fHeight / 2.f),
		(int)fWidth,
		(int)fHeight,
		pTexture->GetHDC(),
		0, 0,
		(int)fWidth,
		(int)fHeight,
		RGB(0, 0, 0)
	);

	pTexture = CResourceManager::Get()->FindTexture(L"BossHP");

	fWidth = pTexture->GetWidth();
	fHeight = pTexture->GetHeight();

	StretchBlt
	(
		_hDC,
		(int)(GetPos().fX - fWidth / 2.f), 
		(int)(GetPos().fY - fHeight / 2.f),
		(int)(fWidth * m_fRatio),
		(int)fHeight,
		pTexture->GetHDC(),
		0, 0,
		(int)fWidth,
		(int)fHeight,
		SRCCOPY
	);

	__super::Render(_hDC);
}

void CBossHP::Release()
{
}

void CBossHP::BossHPUpdate()
{
	CBulletKing* pBulletKing = dynamic_cast<CBulletKing*>(GetTarget());

	m_fCurrHP = pBulletKing->GetCurrHP();

	m_fRatio = m_fCurrHP / m_fMaxHP;
}