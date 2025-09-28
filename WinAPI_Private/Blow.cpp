#include "pch.h"
#include "Blow.h"

#include "Collider.h"
#include "Character.h"
#include "Interact.h"
#include "Func.h"
#include "Player.h"

CBlow::CBlow()
	: m_fDamage(0.f)
	, m_fLifeTime(0.f)
	, m_iTick(0)
{
	SetObjectType(OBJECT_TYPE::BLOW);
	SetRenderType(RENDER_TYPE::RENDER_EFFECT);
}

CBlow::~CBlow()
{
	Release();
}

void CBlow::Init()
{
	SetScale({ 250.f, 250.f });

	m_fDamage = 50.f;
	m_fLifeTime = 1.f;
	m_iTick = GetTickCount64();

	CreateCollider();
	GetCollider()->SetScale(GetScale());
	GetCollider()->SetShow(false);
}

void CBlow::Update()
{
}

void CBlow::LateUpdate()
{
	__super::LateUpdate();

	if(m_fLifeTime < GetTickCount64() - m_iTick)
		DeleteObjectEvent(this);
}

void CBlow::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CBlow::Release()
{
}

void CBlow::OnCollision(CCollider& _pOther)
{
}

void CBlow::OnCollisionEnter(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::INTERACT)
	{
		CInteract* pInteract = dynamic_cast<CInteract*>(pOwner);

		pInteract->SetHP(pInteract->GetHP() - m_fDamage);
	}
}

void CBlow::OnCollisionExit(CCollider& _pOther)
{
}