#include "pch.h"
#include "ShotGunEffect.h"

#include "ResourceManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CShotGunEffect::CShotGunEffect()
{
}

CShotGunEffect::~CShotGunEffect()
{
	Release();
}

void CShotGunEffect::Init()
{
	SetScale({ 48.f, 48.f });
	SetRenderScale(GetScale());

	SetEffectType(EFFECT_TYPE::BULLET_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"ShotGunEffect", false);
}

void CShotGunEffect::Update()
{
	if (GetAnimator()->GetCurrAnim()->GetFinish())
		DeleteObjectEvent(this);
}

void CShotGunEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CShotGunEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CShotGunEffect::Release()
{
}

void CShotGunEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"ShotGunEffect", CResourceManager::Get()->FindTexture(L"ShotGunEffect"), Vec2(0, 0), Vec2(48, 48), Vec2(48, 0), .1f, 7);
}