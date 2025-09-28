#include "pch.h"
#include "SceneChanger.h"

#include "Collider.h"

CSceneChanger::CSceneChanger()
{
	SetEventTriggerType(EVENT_TRIGGER_TYPE::SCENE_CHANGE);
}

CSceneChanger::~CSceneChanger()
{
	Release();
}

void CSceneChanger::Init()
{
	__super::Init();
}

void CSceneChanger::Update()
{
}

void CSceneChanger::LateUpdate()
{
	__super::LateUpdate();
}

void CSceneChanger::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CSceneChanger::Release()
{
}

void CSceneChanger::OnCollision(CCollider& _pOther)
{
}

void CSceneChanger::OnCollisionEnter(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER)
	{

	}
}

void CSceneChanger::OnCollisionExit(CCollider& _pOther)
{
}