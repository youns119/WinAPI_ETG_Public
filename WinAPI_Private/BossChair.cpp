#include "pch.h"
#include "BossChair.h"

#include "ResourceManager.h"

#include "Animator.h"
#include "Animation.h"

CBossChair::CBossChair()
	: m_eChairState(CHAIR_STATE::END)
	, m_pTarget(nullptr)
{
	SetObjectType(OBJECT_TYPE::EFFECT);
	SetRenderType(RENDER_TYPE::RENDER_OBJECT);
}

CBossChair::~CBossChair()
{
	Release();
}

void CBossChair::Init()
{
	CreateAnimator();

	m_eChairState = CHAIR_STATE::IDLE;

	CreateAnimation();
}

void CBossChair::Update()
{
	if (m_pTarget)
	{
		SetPos({ m_pTarget->GetPos().fX, m_pTarget->GetPos().fY - 10.f });
	}
}

void CBossChair::LateUpdate()
{
	__super::LateUpdate();

	Motion();
}

void CBossChair::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CBossChair::Release()
{
}

void CBossChair::Motion()
{
	if (m_eChairState == CHAIR_STATE::IDLE)
		GetAnimator()->PlayAnimation(L"BulletKing_Chair_Idle", true);
	else if (m_eChairState == CHAIR_STATE::ROTATE)
		GetAnimator()->PlayAnimation(L"BulletKing_Chair_Rotate", false);
	else if (m_eChairState == CHAIR_STATE::DIE)
		GetAnimator()->PlayAnimation(L"Chair", true);
}

void CBossChair::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"BulletKing_Chair_Idle", CResourceManager::Get()->FindTexture(L"BulletKing_Chair_Idle"), Vec2(0, 0), Vec2(200, 200), Vec2(200, 0), .1f, 2);
	GetAnimator()->CreateAnimation(L"BulletKing_Chair_Rotate", CResourceManager::Get()->FindTexture(L"BulletKing_Chair_Rotate"), Vec2(0, 0), Vec2(200, 200), Vec2(200, 0), .06f, 3);
	GetAnimator()->CreateAnimation(L"Chair", CResourceManager::Get()->FindTexture(L"Chair"), Vec2(0, 0), Vec2(200, 200), Vec2(200, 0), .1f, 1);

}