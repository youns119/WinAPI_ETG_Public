#include "pch.h"
#include "EventTrigger.h"

#include "Collider.h"

CEventTrigger::CEventTrigger()
	: m_eEventTriggerType(EVENT_TRIGGER_TYPE::END)
{
	SetObjectType(OBJECT_TYPE::EVENT_TRIGGER);
	SetRenderType(RENDER_TYPE::RENDER_UI);
}

CEventTrigger::~CEventTrigger()
{
	Release();
}

void CEventTrigger::Init()
{
	CreateCollider();

	GetCollider()->SetScale(GetScale());
	GetCollider()->SetShow(false);
}

void CEventTrigger::Update()
{
}

void CEventTrigger::LateUpdate()
{
	__super::LateUpdate();
}

void CEventTrigger::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CEventTrigger::Release()
{
}

void CEventTrigger::OnCollision(CCollider& _pOther)
{
}

void CEventTrigger::OnCollisionEnter(CCollider& _pOther)
{
}

void CEventTrigger::OnCollisionExit(CCollider& _pOther)
{
}