#include "pch.h"
#include "Gun.h"

#include "ResourceManager.h"
#include "Camera.h"

#include "Texture.h"
#include "Player.h"
#include "Collider.h"

CGun::CGun()
	: m_eGunType(GUN_TYPE::END)
	, m_eTriggerType(TRIGGER_TYPE::END)
	, m_eMagType(MAG_TYPE::END)
	, m_iMag(0)
	, m_iCurrMag(0)
	, m_iMax(0)
	, m_iCurrMax(0)
	, m_fReload(0.f)
	, m_fSpeed(0.f)
	, m_fKnock(0.f)
	, m_fDamage(0.f)
	, m_fDelay(0.f)
	, m_fRange(0.f)
	, m_fScatter(0.f)
	, m_bShow(false)
	, m_tPoint{}
	, m_vEnd{}
	, m_pTarget(nullptr)
	, m_pTexture(nullptr)
	, m_pTextureR(nullptr)
	, m_pTextureL(nullptr)
	, m_pTexturePlg(nullptr)
	, m_pTextureReset(nullptr)
{
	SetObjectType(OBJECT_TYPE::GUN);
}

CGun::~CGun()
{
	Release();
}

void CGun::Init()
{
	CreateCollider();

	PreRender();

	SetScale({ (float)GetTexture()->GetWidth(), (float)GetTexture()->GetHeight() });
	SetRenderScale(GetScale());

	GetCollider()->SetScale(GetScale());
	GetCollider()->SetShow(false);
}

void CGun::Update()
{
	SetPos({ m_pTarget->GetPos().fX, m_pTarget->GetPos().fY + 10.f });

	float fDegree = m_pTarget->GetRadian() * 180 / PI;

	if (fDegree >= -90.f && fDegree <= 90.f)
	{
		m_pTexture = m_pTextureR;
		SetPos({ m_pTarget->GetPos().fX + 20.f, m_pTarget->GetPos().fY + 15.f });
		
		m_vEnd = GetPos();
	}
	else
	{
		m_pTexture = m_pTextureL;
		SetPos({ m_pTarget->GetPos().fX - 20.f, m_pTarget->GetPos().fY + 15.f });

		m_vEnd = GetPos();
	}

	float fDiagonal = sqrtf((GetScale().fX / 2.f) * (GetScale().fX / 2.f) + (GetScale().fY / 2.f) * (GetScale().fY / 2.f));

	if (m_pTexture == m_pTextureR)
	{
		m_tPoint[0].x = LONG((GetScale().fX / 2.f) + fDiagonal * cos((-fDegree + 135.f) * (PI / 180.f)));
		m_tPoint[0].y = LONG((GetScale().fY / 2.f) - fDiagonal * sin((-fDegree + 135.f) * (PI / 180.f)));

		m_tPoint[1].x = LONG((GetScale().fX / 2.f) + fDiagonal * cos((-fDegree + 45.f) * (PI / 180.f)));
		m_tPoint[1].y = LONG((GetScale().fY / 2.f) - fDiagonal * sin((-fDegree + 45.f) * (PI / 180.f)));

		m_tPoint[2].x = LONG((GetScale().fX / 2.f) + fDiagonal * cos((-fDegree + 225.f) * (PI / 180.f)));
		m_tPoint[2].y = LONG((GetScale().fY / 2.f) - fDiagonal * sin((-fDegree + 225.f) * (PI / 180.f)));

		m_vEnd = { GetPos().fX + m_pTexture->GetWidth() / 2.f * cosf(m_pTarget->GetRadian()), GetPos().fY + m_pTexture->GetWidth() / 2.f * sinf(m_pTarget->GetRadian()) };
	}
	else
	{
		m_tPoint[0].x = LONG((GetScale().fX / 2.f) + fDiagonal * -cos((-fDegree + 135.f) * (PI / 180.f)));
		m_tPoint[0].y = LONG((GetScale().fY / 2.f) - fDiagonal * -sin((-fDegree + 135.f) * (PI / 180.f)));

		m_tPoint[1].x = LONG((GetScale().fX / 2.f) + fDiagonal * -cos((-fDegree + 45.f) * (PI / 180.f)));
		m_tPoint[1].y = LONG((GetScale().fY / 2.f) - fDiagonal * -sin((-fDegree + 45.f) * (PI / 180.f)));

		m_tPoint[2].x = LONG((GetScale().fX / 2.f) + fDiagonal * -cos((-fDegree + 225.f) * (PI / 180.f)));
		m_tPoint[2].y = LONG((GetScale().fY / 2.f) - fDiagonal * -sin((-fDegree + 225.f) * (PI / 180.f)));

		m_vEnd = { GetPos().fX + m_pTexture->GetWidth() / 2.f * cosf(m_pTarget->GetRadian()), GetPos().fY + m_pTexture->GetWidth() / 2.f * sinf(m_pTarget->GetRadian()) };
	}

}

void CGun::LateUpdate()
{
	__super::LateUpdate();
}

void CGun::Render(HDC _hDC)
{
	if (m_bShow)
	{
		Vec2 vRenderPos = CCamera::Get()->GetRenderPos(GetPos());

		PlgBlt
		(
			m_pTexturePlg->GetHDC(),
			m_tPoint,
			m_pTexture->GetHDC(),
			(int)0.f, (int)0.f,
			(int)GetScale().fX,
			(int)GetScale().fY,
			NULL, NULL, NULL
		);

		GdiTransparentBlt
		(
			_hDC,
			int(vRenderPos.fX - GetScale().fX / 2.f),
			int(vRenderPos.fY - GetScale().fY / 2.f),
			(int)(m_pTexturePlg->GetWidth()),
			(int)(m_pTexturePlg->GetHeight()),
			m_pTexturePlg->GetHDC(),
			0, 0,
			(int)(m_pTexturePlg->GetWidth()),
			(int)(m_pTexturePlg->GetHeight()),
			RGB(255, 0, 255)
		);

		BitBlt
		(
			m_pTexturePlg->GetHDC(),
			0, 0,
			(int)(m_pTexturePlg->GetWidth()),
			(int)(m_pTexturePlg->GetHeight()),
			m_pTextureReset->GetHDC(),
			0, 0,
			SRCCOPY
		);

		__super::Render(_hDC);
	}
}

void CGun::Release()
{
}