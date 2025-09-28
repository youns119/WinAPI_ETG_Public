#include "pch.h"
#include "Barrel.h"

#include "ResourceManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "SoundManager.h"

#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Physics.h"
#include "Player.h"
#include "Enemy.h"
#include "Func.h"
#include "BlowEffect.h"
#include "SmokeEffect.h"
#include "Blow.h"

CBarrel::CBarrel()
	: m_eBarrelState(BARREL_STATE::END)
{
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
	SetInteractType(INTERACT_TYPE::BARREL);
}

CBarrel::~CBarrel()
{
	Release();
}

void CBarrel::Init()
{
	SetName(L"Barrel");
	SetScale({ 40.f, 40.f });
	SetRenderScale({ 80.f, 80.f });

	SetVolume(0.2);

	m_eBarrelState = BARREL_STATE::IDLE;

	SetHP(20.f);
	__super::Init();

	GetCollider()->SetOffsetPos(Vec2(0.f, -10.f));

	CreateAnimation();
}

void CBarrel::Update()
{
}

void CBarrel::LateUpdate()
{
	__super::LateUpdate();

	if (GetHP() <= 0)
	{
		if (m_eBarrelState == BARREL_STATE::IDLE)
		{
			m_eBarrelState = BARREL_STATE::BLOW;

			CBlow* pBlow = new CBlow();
			pBlow->Init();
			pBlow->SetPos(GetPos());

			CCamera::Get()->Shake(3.f, 50.f);

			CSoundManager::Get()->PlaySound(L"Barrel_Blow.wav", CHANNELID::SOUND_EFFECT, GetVolume());

			CreateObjectEvent(pBlow, OBJECT_TYPE::BLOW);
			CreateEffect();
		}
	}

	if (m_eBarrelState == BARREL_STATE::BLOW)
		if (GetAnimator()->GetCurrAnim()->GetFinish())
			DeleteObjectEvent(this);

	Motion();
}

void CBarrel::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CBarrel::Release()
{
}

void CBarrel::Motion()
{
	if (m_eBarrelState == BARREL_STATE::IDLE)
		GetAnimator()->PlayAnimation(L"Barrel", true);
	else if (m_eBarrelState == BARREL_STATE::BLOW)
		GetAnimator()->PlayAnimation(L"Barrel_Blow", false);
}

void CBarrel::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"Barrel", CResourceManager::Get()->FindTexture(L"Barrel"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 1);
	GetAnimator()->CreateAnimation(L"Barrel_Blow", CResourceManager::Get()->FindTexture(L"Barrel_Blow"), Vec2(0, 0), Vec2(80, 80), Vec2(80, 0), .1f, 2);
}

void CBarrel::CreateEffect()
{
	CBlowEffect* pBlowEffect = new CBlowEffect;
	CSmokeEffect* pSmokeEffect = new CSmokeEffect;

	pBlowEffect->Init();
	pSmokeEffect->Init();

	pBlowEffect->SetPos({ GetPos().fX, GetPos().fY });
	pSmokeEffect->SetPos({ GetPos().fX, GetPos().fY });

	CreateObjectEvent(pBlowEffect, OBJECT_TYPE::EFFECT);
	CreateObjectEvent(pSmokeEffect, OBJECT_TYPE::EFFECT);
}

void CBarrel::OnCollision(CCollider& _pOther)
{
	CObject* pOwner = _pOther.GetOwner();

	if (pOwner->GetObjectType() == OBJECT_TYPE::PLAYER || pOwner->GetObjectType() == OBJECT_TYPE::ENEMY)
	{
		float fWidth = fabsf(GetCollider()->GetFinalPos().fX - _pOther.GetFinalPos().fX);
		float fHeight = fabsf(GetCollider()->GetFinalPos().fY - _pOther.GetFinalPos().fY);

		float fRadiusX = (GetCollider()->GetScale().fX + _pOther.GetScale().fX) * 0.5f;
		float fRadiusY = (GetCollider()->GetScale().fY + _pOther.GetScale().fY) * 0.5f;

		fWidth = fRadiusX - fWidth;
		fHeight = fRadiusY - fHeight;

		if (m_eBarrelState == BARREL_STATE::IDLE)
		{
			if (fWidth > fHeight)
			{
				if (GetCollider()->GetFinalPos().fY < _pOther.GetFinalPos().fY)
					pOwner->SetPos(Vec2(pOwner->GetPos().fX, pOwner->GetPos().fY + fHeight + 1.f));
				else
					pOwner->SetPos(Vec2(pOwner->GetPos().fX, pOwner->GetPos().fY - fHeight - 1.f));
			}
			else
			{
				if (GetCollider()->GetFinalPos().fX < _pOther.GetFinalPos().fX)
					pOwner->SetPos(Vec2(pOwner->GetPos().fX + fWidth + 1.f, pOwner->GetPos().fY));
				else
					pOwner->SetPos(Vec2(pOwner->GetPos().fX - fWidth - 1.f, pOwner->GetPos().fY));
			}
		}
	}
}

void CBarrel::OnCollisionEnter(CCollider& _pOther)
{
}

void CBarrel::OnCollisionExit(CCollider& _pOther)
{
}