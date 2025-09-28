#include "pch.h"
#include "BlowEffect.h"

#include "ResourceManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CBlowEffect::CBlowEffect()
{
}

CBlowEffect::~CBlowEffect()
{
	Release();
}

void CBlowEffect::Init()
{
	SetScale({ 250.f, 250.f });
	SetRenderScale(GetScale());

	SetEffectType(EFFECT_TYPE::INTERACT_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"BlowEffect", false);
}

void CBlowEffect::Update()
{
}

void CBlowEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CBlowEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CBlowEffect::Release()
{
}

void CBlowEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"BlowEffect", CResourceManager::Get()->FindTexture(L"BlowEffect"), Vec2(0, 0), Vec2(250, 250), Vec2(250, 0), .06f, 13);
}