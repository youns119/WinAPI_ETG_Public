#include "pch.h"
#include "SmokeEffect.h"

#include "ResourceManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CSmokeEffect::CSmokeEffect()
{
}

CSmokeEffect::~CSmokeEffect()
{
	Release();
}

void CSmokeEffect::Init()
{
	SetScale({ 300.f, 300.f });
	SetRenderScale(GetScale());

	SetEffectType(EFFECT_TYPE::INTERACT_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"SmokeEffect", false);
}

void CSmokeEffect::Update()
{
}

void CSmokeEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CSmokeEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CSmokeEffect::Release()
{
}

void CSmokeEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"SmokeEffect", CResourceManager::Get()->FindTexture(L"SmokeEffect"), Vec2(0, 0), Vec2(300, 300), Vec2(300, 0), .2f, 4);
}