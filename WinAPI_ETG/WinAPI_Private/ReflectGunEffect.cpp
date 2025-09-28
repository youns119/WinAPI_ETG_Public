#include "pch.h"
#include "ReflectGunEffect.h"

#include "ResourceManager.h"

#include "Animator.h"
#include "Animation.h"
#include "Func.h"

CReflectGunEffect::CReflectGunEffect()
{
}

CReflectGunEffect::~CReflectGunEffect()
{
	Release();
}

void CReflectGunEffect::Init()
{
	SetScale({ 30.f, 30.f });
	SetRenderScale(GetScale());

	SetEffectType(EFFECT_TYPE::BULLET_EFFECT);

	__super::Init();

	CreateAnimation();

	GetAnimator()->PlayAnimation(L"ReflectGunEffect", false);
}

void CReflectGunEffect::Update()
{
	if (GetAnimator()->GetCurrAnim()->GetFinish())
		DeleteObjectEvent(this);
}

void CReflectGunEffect::LateUpdate()
{
	__super::LateUpdate();
}

void CReflectGunEffect::Render(HDC _hDC)
{
	__super::Render(_hDC);
}

void CReflectGunEffect::Release()
{
}

void CReflectGunEffect::CreateAnimation()
{
	GetAnimator()->CreateAnimation(L"ReflectGunEffect", CResourceManager::Get()->FindTexture(L"ReflectGunEffect"), Vec2(0, 0), Vec2(30, 30), Vec2(30, 0), .1f, 4);
}