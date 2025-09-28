#include "pch.h"
#include "Object.h"

#include "Keyboard.h"
#include "Camera.h"

#include "Collider.h"
#include "Animator.h"
#include "Physics.h"

CObject::CObject()
	: m_strName{}
	, m_vPos{}
	, m_vScale{}
	, m_vRenderScale{}
	, m_fMass(0.f)
	, m_fFriction(0.f)
	, m_fMaxVelocity(0.f)
	, m_fRadian(0.f)
	, m_fVolume(0.f)
	, m_bDead(false)
	, m_eObjectType(OBJECT_TYPE::END)
	, m_eRenderType(RENDER_TYPE::END)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pPhysics(nullptr)
{
}

CObject::CObject(const CObject& _Object)
	: m_strName(_Object.m_strName)
	, m_vScale(_Object.m_vScale)
	, m_vRenderScale(_Object.m_vRenderScale)
	, m_fMass(_Object.m_fMass)
	, m_fFriction(_Object.m_fFriction)
	, m_fMaxVelocity(_Object.m_fMaxVelocity)
	, m_fRadian(_Object.m_fRadian)
	, m_fVolume(_Object.m_fVolume)
	, m_bDead(false)
	, m_eObjectType(_Object.m_eObjectType)
	, m_eRenderType(_Object.m_eRenderType)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pPhysics(nullptr)
{
	if (_Object.m_pCollider)
	{
		m_pCollider = new CCollider(*_Object.m_pCollider);
		m_pCollider->SetOwner(*this);
	}

	if (_Object.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_Object.m_pAnimator);
		m_pAnimator->SetOwner(*this);
	}

	if (_Object.m_pPhysics)
	{
		m_pPhysics = new CPhysics(*_Object.m_pPhysics);
		m_pPhysics->SetOwner(*this);
	}
}

CObject::~CObject()
{
	Release();
}

void CObject::Init()
{
}

void CObject::Update()
{
}

void CObject::LateUpdate()
{
	if (m_pAnimator)
		m_pAnimator->LateUpdate();

	if (m_pPhysics)
		m_pPhysics->LateUpdate();

	if (m_pCollider)
		m_pCollider->LateUpdate();
}

void CObject::Render(HDC _hDC)
{
	AnimationRender(_hDC);
}

void CObject::Release()
{
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pAnimator);
	Safe_Delete(m_pPhysics);
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	m_pCollider->SetOwner(*this);
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->SetOwner(*this);
}

void CObject::CreatePhysics()
{
	m_pPhysics = new CPhysics;
	m_pPhysics->SetOwner(*this);
}

void CObject::AnimationRender(HDC _hDC)
{
	if (m_pAnimator)
		m_pAnimator->Render(_hDC);
}

void CObject::ColliderRender(HDC _hDC)
{
	if (m_pCollider)
		m_pCollider->Render(_hDC);
}

void CObject::OnCollision(CCollider& _pOther)
{
	CObject* pOther = _pOther.GetOwner();

	if (pOther->GetObjectType() == OBJECT_TYPE::WALL)
	{
		float fWidth = fabsf(GetCollider()->GetFinalPos().fX - _pOther.GetFinalPos().fX);
		float fHeight = fabsf(GetCollider()->GetFinalPos().fY - _pOther.GetFinalPos().fY);

		float fRadiusX = (GetCollider()->GetScale().fX + _pOther.GetScale().fX) * 0.5f;
		float fRadiusY = (GetCollider()->GetScale().fY + _pOther.GetScale().fY) * 0.5f;

		fWidth = fRadiusX - fWidth;
		fHeight = fRadiusY - fHeight;

		if (fWidth > fHeight)
		{
			if (GetCollider()->GetFinalPos().fY < _pOther.GetFinalPos().fY)
				SetPos(Vec2(GetPos().fX, GetPos().fY - fHeight - 1.f));
			else
				SetPos(Vec2(GetPos().fX, GetPos().fY + fHeight + 1.f));
		}
		else
		{
			if (GetCollider()->GetFinalPos().fX < _pOther.GetFinalPos().fX)
				SetPos(Vec2(GetPos().fX - fWidth - 1.f, GetPos().fY));
			else
				SetPos(Vec2(GetPos().fX + fWidth + 1.f, GetPos().fY));
		}
	}
}

void CObject::OnCollisionEnter(CCollider& _pOther)
{
}

void CObject::OnCollisionExit(CCollider& _pOther)
{
}