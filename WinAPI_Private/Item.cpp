#include "pch.h"
#include "Item.h"

#include "ResourceManager.h"
#include "Camera.h"

#include "Collider.h"
#include "Physics.h"
#include "Texture.h"

CItem::CItem()
	: m_iPrice(0)
	, m_bShowPrice(false)
	, m_vColOffset{}
	, m_pTexture(nullptr)
	, m_eItemType(ITEM_TYPE::END)
{
	SetObjectType(OBJECT_TYPE::ITEM);
}

CItem::~CItem()
{
	Release();
}

void CItem::Init()
{
	CreateCollider();
	CreatePhysics();

	GetCollider()->SetScale(GetScale());
	GetCollider()->SetOffsetPos(m_vColOffset);
	GetCollider()->SetShow(false);

	GetPhysics()->SetMass(GetMass());
	GetPhysics()->SetFriction(GetFriction());
	GetPhysics()->SetMaxVelocity(GetMaxVelocity());

	SetRenderScale(GetScale());

	PriceUpdate();
}

void CItem::Update()
{
}

void CItem::LateUpdate()
{
	__super::LateUpdate();
}

void CItem::Render(HDC _hDC)
{
	Vec2 vRenderPos = CCamera::Get()->GetRenderPos(GetPos());

	GdiTransparentBlt
	(
		_hDC,
		(int)(vRenderPos.fX - GetScale().fX / 2.f),
		(int)(vRenderPos.fY - GetScale().fY / 2.f),
		(int)(GetScale().fX),
		(int)(GetScale().fY),
		m_pTexture->GetHDC(),
		0, 0,
		(int)(GetScale().fX),
		(int)(GetScale().fY),
		RGB(255, 0, 255)
	);

	if (m_iPrice > 0 && m_bShowPrice)
	{
		Vec2 vPos{};

		CTexture* pTexture = CResourceManager::Get()->FindTexture(L"Item_Coin");

		int iWidth = pTexture->GetWidth();
		int iHeight = pTexture->GetHeight();

		vPos = { vRenderPos.fX - 20.f, vRenderPos.fY - 40.f};

		GdiTransparentBlt
		(
			_hDC,
			(int)(vPos.fX - iWidth / 2.f),
			(int)(vPos.fY - iHeight / 2.f),
			(int)(iWidth),
			(int)(iHeight),
			pTexture->GetHDC(),
			0, 0,
			(int)(iWidth),
			(int)(iHeight),
			RGB(255, 0, 255)
		);

		pTexture = CResourceManager::Get()->FindTexture(L"Font_Smaller");

		iWidth = pTexture->GetWidth();
		iHeight = pTexture->GetHeight();

		for (int i = 0; i < m_vecCount.size(); i++)
		{
			GdiTransparentBlt
			(
				_hDC,
				(int)(vPos.fX - iHeight / 2.f + 20.f + 15.f * i),
				(int)(vPos.fY - iHeight / 2.f),
				(int)iHeight,
				(int)iHeight,
				pTexture->GetHDC(),
				(int)(iHeight * (9 - m_vecCount[i])),
				0,
				(int)iHeight,
				(int)iHeight,
				RGB(0, 0, 0)
			);
		}
	}

	__super::Render(_hDC);
}

void CItem::Release()
{
}

void CItem::PriceUpdate()
{
	int iDigit = 0;

	m_vecCount.clear();

	iDigit = m_iPrice / 1000;
	if (iDigit != 0) m_vecCount.push_back(iDigit);

	iDigit = (m_iPrice % 1000) / 100;
	if (iDigit != 0 || (iDigit == 0 && !m_vecCount.empty())) m_vecCount.push_back(iDigit);

	iDigit = (m_iPrice % 100) / 10;
	if (iDigit != 0 || (iDigit == 0 && !m_vecCount.empty())) m_vecCount.push_back(iDigit);

	iDigit = m_iPrice % 10;

	m_vecCount.push_back(iDigit);
}

void CItem::OnCollision(CCollider& _pOther)
{
}

void CItem::OnCollisionEnter(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		m_bShowPrice = true;
	}
}

void CItem::OnCollisionExit(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER)
	{
		m_bShowPrice = false;
	}
}