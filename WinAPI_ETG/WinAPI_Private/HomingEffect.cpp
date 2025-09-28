#include "pch.h"
#include "HomingEffect.h"

#include "ResourceManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CHomingEffect::CHomingEffect()
{
}

CHomingEffect::~CHomingEffect()
{
	Release();
}

void CHomingEffect::Init()
{
	SetScale({ 32.f, 32.f });
	SetRenderScale(GetScale());

	SetEffectType(EFFECT_TYPE::BULLET_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"HomingEffect", false);
}

void CHomingEffect::Update()
{
	if (GetAnimator()->GetCurrAnim()->GetFinish())
		DeleteObjectEvent(this);
}

void CHomingEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CHomingEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CHomingEffect::Release()
{
}

void CHomingEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"HomingEffect", CResourceManager::Get()->FindTexture(L"HomingEffect"), Vec2(0, 0), Vec2(32, 32), Vec2(32, 0), .07f, 8);
}