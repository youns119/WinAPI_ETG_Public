#include "pch.h"
#include "Physics.h"

#include "Timer.h"

CPhysics::CPhysics()
	: m_fMass(0.f)
	, m_fFriction(0.f)
	, m_fMaxVelocity(0.f)
	, m_vForce{}
	, m_vAccel{}
	, m_vAccelAlpha{}
	, m_vVelocity{}
	, m_pOwner(nullptr)
{
	m_fMass = 1.f;
	m_fFriction= 700.f;
	m_fMaxVelocity = 300.f;
}

CPhysics::~CPhysics()
{
}

void CPhysics::Update()
{
}

void CPhysics::LateUpdate()
{
	if (!m_vVelocity.IsZero())
	{
		Vec2 vNorm = m_vVelocity.Normalize();
		Vec2 vFriction = (-vNorm) * m_fFriction * CTimer::Get()->GetDelta();

		if (m_vVelocity.Length() <= vFriction.Length())
			m_vVelocity = Vec2(0.f, 0.f);
		else
			m_vVelocity += vFriction;
	}

	float fForce = m_vForce.Length();

	if (fForce != 0.f)
	{
		Vec2 vNorm = m_vForce.Normalize();
		float fAccel = fForce / m_fMass;

		m_vAccel = vNorm * fAccel;
	}

	m_vAccel += m_vAccelAlpha;
	m_vVelocity += m_vAccel * CTimer::Get()->GetDelta();


	if (m_fMaxVelocity <= m_vVelocity.Length())
	{
		Vec2 vNorm = m_vVelocity.Normalize();

		m_vVelocity = vNorm * m_fMaxVelocity;
	}

	Move();

	m_vForce = Vec2(0.f, 0.f);
	m_vAccelAlpha = Vec2(0.f, 0.f);
	m_vAccel = Vec2(0.f, 0.f);
}

void CPhysics::Move()
{
	float fSpeed = m_vVelocity.Length();

	if (fSpeed != 0.f)
	{
		Vec2 vDir = m_vVelocity;
		Vec2 vNorm = vDir.Normalize();
		Vec2 vPos = m_pOwner->GetPos();

		vPos += vNorm * fSpeed * CTimer::Get()->GetDelta();
		m_pOwner->SetPos(vPos);
	}
}