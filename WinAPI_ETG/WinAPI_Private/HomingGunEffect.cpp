#include "pch.h"
#include "HomingGunEffect.h"

#include "ResourceManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CHomingGunEffect::CHomingGunEffect()
{
}

CHomingGunEffect::~CHomingGunEffect()
{
	Release();
}

void CHomingGunEffect::Init()
{
	SetScale({ 100.f, 100.f });
	SetRenderScale(GetScale());

	SetEffectType(EFFECT_TYPE::BULLET_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"HomingGunEffect", false);
}

void CHomingGunEffect::Update()
{
	if (GetAnimator()->GetCurrAnim()->GetFinish())
		DeleteObjectEvent(this);
}

void CHomingGunEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CHomingGunEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CHomingGunEffect::Release()
{
}

void CHomingGunEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"HomingGunEffect", CResourceManager::Get()->FindTexture(L"HomingGunEffect"), Vec2(0, 0), Vec2(100, 100), Vec2(100, 0), .1f, 8);
}