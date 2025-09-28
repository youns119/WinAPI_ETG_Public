#include "pch.h"
#include "Interact.h"

#include "Collider.h"
#include "Physics.h"

CInteract::CInteract()
	: m_iHP(0)
	, m_eInteractType(INTERACT_TYPE::END)
	, m_tColOffset{}
{
	SetObjectType(OBJECT_TYPE::INTERACT);
}

CInteract::~CInteract()
{
	Release();
}

void CInteract::Init()
{
	CreateCollider();
	CreateAnimator();
	CreatePhysics();

	GetCollider()->SetScale(GetScale());
	GetCollider()->SetShow(false);

	GetPhysics()->SetMass(GetMass());
	GetPhysics()->SetFriction(GetFriction());
	GetPhysics()->SetMaxVelocity(GetMaxVelocity());
}

void CInteract::Update()
{
}

void CInteract::LateUpdate()
{
	__super::LateUpdate();
}

void CInteract::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CInteract::Release()
{
}

bool CInteract::isOffsetCollision(CObject* _pOther)
{
	Vec2 vOtherPos = _pOther->GetPos();
	Vec2 vOtherScale = _pOther->GetScale();

	Vec2 vOffsetPos = m_tColOffset.vPos;
	Vec2 vOffsetScale = m_tColOffset.vScale;

	if (abs(vOtherPos.fX - vOffsetPos.fX) <= (vOtherScale.fX + vOffsetScale.fX) / 2.f
		&& abs(vOtherPos.fY - vOffsetPos.fY) <= (vOtherScale.fY + vOffsetScale.fY) / 2.f)
		return true;

	return false;
}

void CInteract::OnCollision(CCollider& _pOther)
{
}

void CInteract::OnCollisionEnter(CCollider& _pOther)
{
}

void CInteract::OnCollisionExit(CCollider& _pOther)
{
}