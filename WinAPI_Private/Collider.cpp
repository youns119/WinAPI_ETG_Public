#include "pch.h"
#include "Collider.h"

#include "Main.h"
#include "Camera.h"

#include "Object.h"
#include "Paint.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_vOffsetPos{}
	, m_vFinalPos{}
	, m_vScale{}
	, m_iID(g_iNextID++)
	, m_iCollided(0)
	, m_bActive(false)
	, m_bShow(false)
{
}

CCollider::CCollider(const CCollider& _Origin)
	:m_pOwner(nullptr)
	, m_vOffsetPos(_Origin.m_vOffsetPos)
	, m_vFinalPos(_Origin.m_vFinalPos)
	, m_vScale(_Origin.m_vScale)
	, m_iID(_Origin.m_iID)
	, m_iCollided(_Origin.m_iCollided)
	, m_bActive(_Origin.m_bActive)
	, m_bShow(_Origin.m_bShow)
{

}

CCollider::~CCollider()
{
}

void CCollider::LateUpdate()
{
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	assert(0 <= m_iCollided);
}

void CCollider::Render(HDC _hDC)
{
	if (m_bShow)
	{
		PEN_TYPE ePen;

		if (m_iCollided) ePen = PEN_TYPE::RED;
		else ePen = PEN_TYPE::GREEN;

		CPaint pen(_hDC, ePen);
		CPaint brush(_hDC, BRUSH_TYPE::HOLLOW);

		Vec2 vRenderPos = CCamera::Get()->GetRenderPos(m_vFinalPos);

		Rectangle
		(
			_hDC,
			(int)(vRenderPos.fX - m_vScale.fX / 2.f),
			(int)(vRenderPos.fY - m_vScale.fY / 2.f),
			(int)(vRenderPos.fX + m_vScale.fX / 2.f),
			(int)(vRenderPos.fY + m_vScale.fY / 2.f)
		);
	}
}

void CCollider::OnCollision(CCollider& _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void CCollider::OnCollisionEnter(CCollider& _pOther)
{
	m_iCollided++;
	m_pOwner->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionExit(CCollider& _pOther)
{
	m_iCollided--;
	m_pOwner->OnCollisionExit( _pOther);
}