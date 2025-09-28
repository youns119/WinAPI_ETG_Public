#include "pch.h"
#include "ItemBox.h"

#include "Main.h"
#include "ResourceManager.h"

#include "Texture.h"
#include "Player.h"
#include "Item.h"

CItemBox::CItemBox()
	: m_pItemTexture(nullptr)
{
	SetRenderType(RENDER_TYPE::RENDER_UI);
}

CItemBox::~CItemBox()
{
	Release();
}

void CItemBox::Init()
{
	SetPos({ 120.f, CMain::Get()->GetResolution().y - 80.f });

	float fWidth = (float)CResourceManager::Get()->FindTexture(L"GunBox")->GetWidth();
	float fHeight = (float)CResourceManager::Get()->FindTexture(L"GunBox")->GetHeight();

	SetScale({ fWidth, fHeight });

	SetUIType(UI_TYPE::ITEMBOX);
}

void CItemBox::Update()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetTarget());

	if (pPlayer->GetCurrItem())
	{
		ITEM_TYPE eItemType = dynamic_cast<CPlayer*>(GetTarget())->GetCurrItem()->GetItemType();

		switch (eItemType)
		{
		case ITEM_TYPE::MEDIKIT :
			m_pItemTexture = dynamic_cast<CPlayer*>(GetTarget())->GetCurrItem()->GetTexture();
			break;
		default:
			break;
		}
	}
}

void CItemBox::LateUpdate()
{
	__super::LateUpdate();
}

void CItemBox::Render(HDC _hDC)
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

	if (m_pItemTexture)
	{
		GdiTransparentBlt
		(
			_hDC,
			(int)(GetPos().fX - m_pItemTexture->GetWidth() / 2.f),
			(int)(GetPos().fY - m_pItemTexture->GetHeight() / 2.f),
			(int)(m_pItemTexture->GetWidth()),
			(int)(m_pItemTexture->GetHeight()),
			m_pItemTexture->GetHDC(),
			0, 0,
			(int)(m_pItemTexture->GetWidth()),
			(int)(m_pItemTexture->GetHeight()),
			RGB(255, 0, 255)
		);
	}

	__super::Render(_hDC);
}

void CItemBox::Release()
{
}